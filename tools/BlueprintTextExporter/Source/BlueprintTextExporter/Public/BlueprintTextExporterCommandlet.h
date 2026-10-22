#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "BlueprintTextExporterCommandlet.generated.h"

/**
 * Exports every Blueprint graph in the project to the text format used by
 * blueprintUE, plus a per-asset inventory (parent class, interfaces, variables,
 * functions, event dispatchers and components).
 *
 * Usage:
 *   UnrealEditor-Cmd.exe <Project.uproject> -run=BlueprintTextExporter
 *     -out=<OutputDirectory>
 *     [-include=/Game/_Core,/Game/UI]
 *     [-exclude=/Game/Village,/Game/Cinematic]
 */
UCLASS()
class UBlueprintTextExporterCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	UBlueprintTextExporterCommandlet();

	virtual int32 Main(const FString& Params) override;
};
