#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/StreamableManager.h"
#include "Blueprint/UserWidget.h"
#include "UObject/WeakObjectPtr.h"
#include "LoadingSubsystem.generated.h"

UCLASS()
class SPLINEPLATFORMERTEST_API ULoadingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Funciones nativas de Unreal para enlazarnos a los eventos del motor al nacer y morir
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Inicia la carga asíncrona del mapa
	UFUNCTION(BlueprintCallable, Category = "Level Transition")
	void LoadLevelWithProgress(TSoftObjectPtr<UWorld> LevelToLoad, TSubclassOf<UUserWidget> LoadingWidgetClass, float ExtraDelayTime = 0.0f, float FadeDuration = 0.3f);

	UFUNCTION(BlueprintCallable, Category = "Level Transition")
	void HideLoadingScreen(bool bInstant = false, float FadeDuration = 0.3f);

	void ClearLoadingScreenData();

private:
	FStreamableManager StreamableManager;
	TSharedPtr<FStreamableHandle> LoadingHandle;
	
	TWeakObjectPtr<UUserWidget> LoadingWidgetInstance;
	TSharedPtr<class SWidget> LoadingSlateWidgetRef;

	FTimerHandle ProgressTimerHandle;
	FTimerHandle TransitionTimerHandle; // Un único Timer limpio para controlar la secuencia destino

	FString TargetMapName;
	float SavedExtraDelay;
	float TargetFadeDuration;
	float CurrentOpacity;

	void UpdateLoadingProgress();
	void UpdateLoadingProgressFull();
	void OnLevelAsyncLoadComplete();
	void ExecuteLevelChange(); 
	
	// Evento nativo oficial de Unreal que se despierta en cuanto entras al mapa nuevo
	void OnPostLoadMap(UWorld* LoadedWorld);

	void StartFadeOut();   
	void TickFadeOut();    
};
