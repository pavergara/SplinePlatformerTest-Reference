#include "LoadingSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Engine/GameViewportClient.h"
#include "Engine/World.h"
#include "TimerManager.h"

void ULoadingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	// Vinculación nativa real de Unreal: "Avísame cuando el viaje del OpenLevel concluya"
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ULoadingSubsystem::OnPostLoadMap);
}

void ULoadingSubsystem::Deinitialize()
{
	FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);
	Super::Deinitialize();
}

void ULoadingSubsystem::LoadLevelWithProgress(TSoftObjectPtr<UWorld> LevelToLoad, TSubclassOf<UUserWidget> LoadingWidgetClass, float ExtraDelayTime, float FadeDuration)
{
	if (LevelToLoad.IsNull() || IsRunningDedicatedServer()) return;

	UWorld* World = GetWorld();
	if (!World) return;

	// Limpieza absoluta en frío de temporizadores previos
	World->GetTimerManager().ClearTimer(ProgressTimerHandle);
	World->GetTimerManager().ClearTimer(TransitionTimerHandle);

	// Guardamos los tiempos configurados en el nodo de Blueprint de origen
	SavedExtraDelay = ExtraDelayTime;
	TargetFadeDuration = FadeDuration;
	CurrentOpacity = 1.0f;

	if (LoadingWidgetClass && !LoadingSlateWidgetRef.IsValid())
	{
		UUserWidget* CreatedWidget = CreateWidget<UUserWidget>(World, LoadingWidgetClass);
		if (CreatedWidget && GEngine && GEngine->GameViewport)
		{
			LoadingWidgetInstance = CreatedWidget;
			LoadingSlateWidgetRef = CreatedWidget->TakeWidget();
			GEngine->GameViewport->AddViewportWidgetContent(LoadingSlateWidgetRef.ToSharedRef(), 999);
			
			CreatedWidget->SetRenderOpacity(CurrentOpacity);
			CreatedWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}

	TargetMapName = LevelToLoad.GetAssetName();

	LoadingHandle = StreamableManager.RequestAsyncLoad(
		LevelToLoad.ToSoftObjectPath(), 
		FStreamableDelegate::CreateUObject(this, &ULoadingSubsystem::OnLevelAsyncLoadComplete)
	);

	World->GetTimerManager().SetTimer(ProgressTimerHandle, this, &ULoadingSubsystem::UpdateLoadingProgress, 0.01f, true);
}

void ULoadingSubsystem::UpdateLoadingProgress()
{
	if (LoadingHandle.IsValid() && LoadingWidgetInstance.IsValid())
	{
		float Progress = LoadingHandle->GetProgress();
		UUserWidget* WidgetPtr = LoadingWidgetInstance.Get();
		
		if (WidgetPtr)
		{
			UFunction* UpdateFunc = WidgetPtr->FindFunction(FName("UpdateLoadingProgress"));
			if (UpdateFunc)
			{
				// Empaquetamos el parámetro en la estructura para alinearlo con el Blueprint
				struct FUpdateLoadingProgressParams
				{
					double NewProgress; 
				};

				FUpdateLoadingProgressParams Params;
				Params.NewProgress = static_cast<double>(Progress);

				// Pasamos el puntero a la estructura empaquetada
				WidgetPtr->ProcessEvent(UpdateFunc, &Params);
			}
		}
	}
}

void ULoadingSubsystem::UpdateLoadingProgressFull()
{
   if (LoadingWidgetInstance.IsValid())
	{
		float Progress = 1.f;
		UUserWidget* WidgetPtr = LoadingWidgetInstance.Get();
		
		if (WidgetPtr)
		{
			UFunction* UpdateFunc = WidgetPtr->FindFunction(FName("UpdateLoadingProgress"));
			if (UpdateFunc)
			{
				// Empaquetamos el parámetro en la estructura para alinearlo con el Blueprint
				struct FUpdateLoadingProgressParams
				{
					double NewProgress; 
				};

				FUpdateLoadingProgressParams Params;
				Params.NewProgress = static_cast<double>(Progress);

				// Pasamos el puntero a la estructura empaquetada
				WidgetPtr->ProcessEvent(UpdateFunc, &Params);
			}
		}
	}
}

void ULoadingSubsystem::OnLevelAsyncLoadComplete()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ProgressTimerHandle);
        UpdateLoadingProgressFull();
	}

	// Al llegar al 100%, viajamos inmediatamente. No esperamos nada en la escena vieja.
	ExecuteLevelChange();
}

void ULoadingSubsystem::ExecuteLevelChange()
{
	UGameplayStatics::OpenLevel(this, FName(*TargetMapName), true);
	LoadingHandle.Reset();
}

void ULoadingSubsystem::OnPostLoadMap(UWorld* LoadedWorld)
{
	// Ya estamos físicamente en el mapa nuevo. Tus widgets de CommonUI se están creando abajo.
	// Limpiamos el reloj y forzamos la espera solicitada para proteger la GPU en la escena de destino.
	LoadedWorld->GetTimerManager().ClearTimer(TransitionTimerHandle);

	if (SavedExtraDelay > 0.0f)
	{
		// El motor congela la pantalla en negro tus X segundos. Al terminar, arranca automáticamente el Fade Out
		LoadedWorld->GetTimerManager().SetTimer(TransitionTimerHandle, this, &ULoadingSubsystem::StartFadeOut, SavedExtraDelay, false);
	}
	else
	{
		// Si pusiste 0 segundos de delay, el Fade Out arranca de forma inmediata
		StartFadeOut();
	}
}

void ULoadingSubsystem::StartFadeOut()
{
	if (UWorld* World = GetWorld())
	{
		// Si la duración es 0 o menor, nos saltamos la animación y borramos de golpe
		if (TargetFadeDuration <= 0.0f)
		{
			ClearLoadingScreenData();
			return;
		}

		// Iniciamos el bucle repetitivo (true) a 60 FPS (0.016s) apuntando directamente a tu Tick de opacidad
		World->GetTimerManager().ClearTimer(TransitionTimerHandle);
		World->GetTimerManager().SetTimer(TransitionTimerHandle, this, &ULoadingSubsystem::TickFadeOut, 0.016f, true);
	}
}

void ULoadingSubsystem::TickFadeOut()
{
	float OpacityStep = 0.016f / TargetFadeDuration;
	CurrentOpacity -= OpacityStep;

	if (LoadingWidgetInstance.IsValid() && CurrentOpacity > 0.0f)
	{
		UUserWidget* WidgetPtr = LoadingWidgetInstance.Get();
		if (WidgetPtr)
		{
			WidgetPtr->SetRenderOpacity(CurrentOpacity);
		}
	}
	else
	{
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().ClearTimer(TransitionTimerHandle);
		}
		ClearLoadingScreenData();
	}
}

void ULoadingSubsystem::ClearLoadingScreenData()
{
	if (GEngine && GEngine->GameViewport && LoadingSlateWidgetRef.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(LoadingSlateWidgetRef.ToSharedRef());
	}

	LoadingSlateWidgetRef.Reset();
	LoadingWidgetInstance.Reset();
}


void ULoadingSubsystem::HideLoadingScreen(bool bInstant, float FadeDuration)
{
	// =========================================================================
	// CORTE DE EMERGENCIA (Tu nueva lógica):
	// En cuanto el destino invoca esta función, le ordenamos al administrador
	// de temporizadores que detenga e invalide el 'TransitionTimerHandle' que 
	// estaba esperando los segundos extras del 'OnPostLoadMap'.
	// Con esto cortamos la espera en duro inmediatamente.
	// =========================================================================
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(TransitionTimerHandle);
	}

	// Si el Blueprint pide que el corte sea seco e inmediato, borramos el Slate en este frame
	if (bInstant || FadeDuration <= 0.0f)
	{
		ClearLoadingScreenData();
		return;
	}

	// Si quieres un desvanecimiento suave después de cortar la espera:
	TargetFadeDuration = FadeDuration;
	CurrentOpacity = 1.0f; // Arrancamos la animación completamente opaco

	// Iniciamos el bucle repetitivo a 60 FPS (0.016s) para tu Tick de opacidad
	StartFadeOut();
}
