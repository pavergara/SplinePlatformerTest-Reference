// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DataAsset.h"
#include "GenericPlatform/GenericApplication.h"

#include "CustomNavigationSubsystem.generated.h"


USTRUCT(BlueprintType)
struct FNavigationMappingRule
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Navigation")
    FKey Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Navigation")
    EUINavigation NavigationDirection = EUINavigation::Invalid;
};

UCLASS(BlueprintType)
class SPLINEPLATFORMERTEST_API UCustomNavigationDataAsset : public UDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Navigation")
    TArray<FNavigationMappingRule> NavigationRules;
};

/**
 * 
 */
UCLASS()
class SPLINEPLATFORMERTEST_API UCustomNavigationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    // Esta es la función que llamas desde el Game Instance en Blueprint
    UFUNCTION(BlueprintCallable, Category = "UI Navigation")
    void ApplyCustomNavigationRules(const UCustomNavigationDataAsset* DataAsset);
};
