// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomNavigationSubsystem.h"

#include "Framework/Application/NavigationConfig.h"
#include "Framework/Application/SlateApplication.h"

void UCustomNavigationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection); // Al arrancar, el motor carga su Gamepad por defecto solo.
}

void UCustomNavigationSubsystem::ApplyCustomNavigationRules(const UCustomNavigationDataAsset* DataAsset)
{
    if (!DataAsset) return;

    // 1. Leemos la configuración que el motor ya tiene activa (con su Gamepad y flechas)
    TSharedRef<FNavigationConfig> CurrentConfig = FSlateApplication::Get().GetNavigationConfig();

    // 2. Le inyectamos las filas de tu Dataset creado en el Editor
    for (const FNavigationMappingRule& Rule : DataAsset->NavigationRules)
    {
        if (Rule.Key.IsValid() && Rule.NavigationDirection != EUINavigation::Invalid)
        {
            CurrentConfig->KeyEventRules.Emplace(Rule.Key, Rule.NavigationDirection);
        }
    }
}