#include "BlueprintTextExporterCommandlet.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraphUtilities.h"
#include "Engine/Blueprint.h"
#include "Engine/SCS_Node.h"
#include "Engine/SimpleConstructionScript.h"
#include "HAL/PlatformFileManager.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Misc/CommandLine.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"
#include "UObject/Class.h"
#include "UObject/UnrealType.h"

namespace
{
	FString SanitizeFileName(const FString& In)
	{
		FString Out = In;
		for (TCHAR& Character : Out)
		{
			if (!FChar::IsAlnum(Character) && Character != TEXT('_') && Character != TEXT('-'))
			{
				Character = TEXT('_');
			}
		}
		return Out;
	}

	FString PinTypeToString(const FEdGraphPinType& Type)
	{
		FString Result = Type.PinCategory.ToString();
		if (Type.PinSubCategory != NAME_None)
		{
			Result += TEXT(":") + Type.PinSubCategory.ToString();
		}
		if (Type.PinSubCategoryObject.IsValid())
		{
			Result += TEXT(":") + Type.PinSubCategoryObject->GetName();
		}

		if (Type.IsArray())
		{
			return FString::Printf(TEXT("Array<%s>"), *Result);
		}
		if (Type.IsSet())
		{
			return FString::Printf(TEXT("Set<%s>"), *Result);
		}
		if (Type.IsMap())
		{
			return FString::Printf(TEXT("Map<%s>"), *Result);
		}
		return Result;
	}
}

namespace
{
	void AppendInventory(const UBlueprint* Blueprint, const TMap<FString, int32>& GraphNodeCounts, const FString& OutFile)
	{
		TArray<FString> Lines;
		Lines.Add(FString::Printf(TEXT("# %s"), *Blueprint->GetName()));
		Lines.Add(TEXT(""));
		Lines.Add(FString::Printf(TEXT("- **Asset path:** `%s`"), *Blueprint->GetPathName()));
		Lines.Add(FString::Printf(TEXT("- **Parent class:** `%s`"), Blueprint->ParentClass ? *Blueprint->ParentClass->GetName() : TEXT("None")));
		Lines.Add(FString::Printf(TEXT("- **Blueprint type:** %s"), *StaticEnum<EBlueprintType>()->GetNameStringByValue(static_cast<int64>(Blueprint->BlueprintType))));

		TArray<FString> Interfaces;
		for (const FBPInterfaceDescription& Description : Blueprint->ImplementedInterfaces)
		{
			if (Description.Interface)
			{
				Interfaces.Add(Description.Interface->GetName());
			}
		}
		Lines.Add(FString::Printf(TEXT("- **Interfaces:** %s"), Interfaces.Num() > 0 ? *FString::Join(Interfaces, TEXT(", ")) : TEXT("None")));
		Lines.Add(TEXT(""));

		TArray<FBPVariableDescription> Variables = Blueprint->NewVariables;
		Lines.Add(TEXT("## Variables"));
		Lines.Add(TEXT(""));
		Lines.Add(TEXT("| Name | Type | Default |"));
		Lines.Add(TEXT("|---|---|---|"));
		for (const FBPVariableDescription& Variable : Variables)
		{
			Lines.Add(FString::Printf(TEXT("| `%s` | `%s` | `%s` |"),
				*Variable.VarName.ToString(),
				*PinTypeToString(Variable.VarType),
				*Variable.DefaultValue));
		}
		Lines.Add(TEXT(""));

		Lines.Add(TEXT("## Functions"));
		Lines.Add(TEXT(""));
		if (Blueprint->FunctionGraphs.Num() == 0)
		{
			Lines.Add(TEXT("_None_"));
		}
		else
		{
			for (UEdGraph* Graph : Blueprint->FunctionGraphs)
			{
				if (Graph)
				{
					Lines.Add(FString::Printf(TEXT("- `%s`"), *Graph->GetName()));
				}
			}
		}
		Lines.Add(TEXT(""));

		Lines.Add(TEXT("## Event Dispatchers"));
		Lines.Add(TEXT(""));
		if (Blueprint->DelegateSignatureGraphs.Num() == 0)
		{
			Lines.Add(TEXT("_None_"));
		}
		else
		{
			for (UEdGraph* Graph : Blueprint->DelegateSignatureGraphs)
			{
				if (Graph)
				{
					Lines.Add(FString::Printf(TEXT("- `%s`"), *Graph->GetName()));
				}
			}
		}
		Lines.Add(TEXT(""));

		Lines.Add(TEXT("## Components"));
		Lines.Add(TEXT(""));
		TArray<FString> Components;
		if (Blueprint->SimpleConstructionScript)
		{
			for (USCS_Node* Node : Blueprint->SimpleConstructionScript->GetAllNodes())
			{
				if (Node && Node->ComponentClass)
				{
					Components.Add(FString::Printf(TEXT("`%s` (%s)"),
						*Node->GetVariableName().ToString(),
						*Node->ComponentClass->GetName()));
				}
			}
		}
		if (Components.Num() == 0)
		{
			Lines.Add(TEXT("_None_"));
		}
		else
		{
			for (const FString& Component : Components)
			{
				Lines.Add(FString::Printf(TEXT("- %s"), *Component));
			}
		}
		Lines.Add(TEXT(""));

		Lines.Add(TEXT("## Graphs"));
		Lines.Add(TEXT(""));
		Lines.Add(TEXT("| Graph | Nodes | Text export |"));
		Lines.Add(TEXT("|---|---:|---|"));
		for (const TPair<FString, int32>& Pair : GraphNodeCounts)
		{
			Lines.Add(FString::Printf(TEXT("| `%s` | %d | `text/%s__%s.txt` |"),
				*Pair.Key,
				Pair.Value,
				*SanitizeFileName(Blueprint->GetName()),
				*SanitizeFileName(Pair.Key)));
		}
		Lines.Add(TEXT(""));

		FFileHelper::SaveStringArrayToFile(Lines, *OutFile, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
	}
}

UBlueprintTextExporterCommandlet::UBlueprintTextExporterCommandlet()
{
	IsClient = false;
	IsServer = false;
	IsEditor = true;
	LogToConsole = true;
}

int32 UBlueprintTextExporterCommandlet::Main(const FString& Params)
{
	TArray<FString> Tokens;
	TArray<FString> Switches;
	TMap<FString, FString> ParamsMap;
	ParseCommandLine(*Params, Tokens, Switches, ParamsMap);

	FString OutDir = ParamsMap.FindRef(TEXT("out"));
	if (OutDir.IsEmpty())
	{
		OutDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("BlueprintTextExport"));
	}
	OutDir = FPaths::ConvertRelativePathToFull(OutDir);

	TArray<FString> Includes;
	TArray<FString> Excludes;
	TArray<FString> Names;
	ParamsMap.FindRef(TEXT("include")).ParseIntoArray(Includes, TEXT(","), true);
	ParamsMap.FindRef(TEXT("exclude")).ParseIntoArray(Excludes, TEXT(","), true);
	ParamsMap.FindRef(TEXT("names")).ParseIntoArray(Names, TEXT(","), true);

	const FString TextDir = FPaths::Combine(OutDir, TEXT("text"));
	const FString InventoryDir = FPaths::Combine(OutDir, TEXT("inventory"));
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	PlatformFile.CreateDirectoryTree(*TextDir);
	PlatformFile.CreateDirectoryTree(*InventoryDir);

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	TArray<FAssetData> BlueprintAssets;
	AssetRegistryModule.Get().GetAssetsByClass(UBlueprint::StaticClass()->GetClassPathName(), BlueprintAssets, true);

	TArray<FString> Manifest;
	Manifest.Add(TEXT("asset,graph,file,status"));

	int32 ProcessedAssets = 0;
	int32 WrittenGraphs = 0;
	int32 AssetsWithoutGraphs = 0;
	int32 FailedAssets = 0;

	for (const FAssetData& AssetData : BlueprintAssets)
	{
		const FString PackageName = AssetData.PackageName.ToString();

		if (Includes.Num() > 0 && !Includes.ContainsByPredicate([&PackageName](const FString& Prefix)
		{
			return PackageName.StartsWith(Prefix, ESearchCase::IgnoreCase);
		}))
		{
			continue;
		}

		if (Excludes.ContainsByPredicate([&PackageName](const FString& Prefix)
		{
			return PackageName.StartsWith(Prefix, ESearchCase::IgnoreCase);
		}))
		{
			continue;
		}

		UBlueprint* Blueprint = Cast<UBlueprint>(AssetData.GetAsset());
		if (!Blueprint)
		{
			FailedAssets++;
			Manifest.Add(FString::Printf(TEXT("%s,,,failed-to-load"), *PackageName));
			continue;
		}

		if (Names.Num() > 0 && !Names.ContainsByPredicate([Blueprint](const FString& Candidate)
		{
			return Candidate.Equals(Blueprint->GetName(), ESearchCase::IgnoreCase);
		}))
		{
			continue;
		}

		const FString SafeAssetName = SanitizeFileName(Blueprint->GetName());

		TArray<UEdGraph*> Graphs;
		for (UEdGraph* Graph : Blueprint->UbergraphPages)
		{
			Graphs.Add(Graph);
		}
		for (UEdGraph* Graph : Blueprint->FunctionGraphs)
		{
			Graphs.Add(Graph);
		}
		for (UEdGraph* Graph : Blueprint->MacroGraphs)
		{
			Graphs.Add(Graph);
		}
		for (UEdGraph* Graph : Blueprint->DelegateSignatureGraphs)
		{
			Graphs.Add(Graph);
		}

		TMap<FString, int32> GraphNodeCounts;

		for (UEdGraph* Graph : Graphs)
		{
			if (!Graph || Graph->Nodes.Num() == 0)
			{
				continue;
			}

			TSet<UObject*> NodesToExport;
			for (UEdGraphNode* Node : Graph->Nodes)
			{
				if (Node)
				{
					NodesToExport.Add(Node);
				}
			}

			if (NodesToExport.Num() == 0)
			{
				continue;
			}

			FString ExportedText;
			FEdGraphUtilities::ExportNodesToText(NodesToExport, ExportedText);
			if (ExportedText.IsEmpty())
			{
				Manifest.Add(FString::Printf(TEXT("%s,%s,,empty"), *PackageName, *Graph->GetName()));
				continue;
			}

			const FString FileName = FString::Printf(TEXT("%s__%s.txt"), *SafeAssetName, *SanitizeFileName(Graph->GetName()));
			const FString FilePath = FPaths::Combine(TextDir, FileName);

			if (FFileHelper::SaveStringToFile(ExportedText, *FilePath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
			{
				GraphNodeCounts.Add(Graph->GetName(), Graph->Nodes.Num());
				Manifest.Add(FString::Printf(TEXT("%s,%s,%s,ok"), *PackageName, *Graph->GetName(), *FileName));
				WrittenGraphs++;
			}
			else
			{
				Manifest.Add(FString::Printf(TEXT("%s,%s,,write-failed"), *PackageName, *Graph->GetName()));
			}
		}

		const FString InventoryFile = FPaths::Combine(InventoryDir, SafeAssetName + TEXT(".md"));
		AppendInventory(Blueprint, GraphNodeCounts, InventoryFile);

		if (GraphNodeCounts.Num() > 0)
		{
			ProcessedAssets++;
		}
		else
		{
			AssetsWithoutGraphs++;
		}
	}

	FFileHelper::SaveStringArrayToFile(Manifest, *FPaths::Combine(OutDir, TEXT("manifest.csv")), FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);

	UE_LOG(LogTemp, Display, TEXT("BlueprintTextExporter: assets with graphs=%d, graphs written=%d, assets without graphs=%d, failed=%d"),
		ProcessedAssets, WrittenGraphs, AssetsWithoutGraphs, FailedAssets);
	UE_LOG(LogTemp, Display, TEXT("BlueprintTextExporter: output=%s"), *OutDir);

	return WrittenGraphs > 0 ? 0 : 1;
}


