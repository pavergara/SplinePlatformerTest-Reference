# Blueprint evidence — coverage matrix

This file tracks exactly what is published, what is only linked externally, and what is still pending. It is intentionally honest: a row marked ⏳ is not published yet.

**Generated:** 32 Blueprints · 101 graph text files · 32 inventories (see `manifest.csv`).

**Legend**

| Symbol | Meaning |
|---|---|
| ✅ | Included in this repository (text and/or inventory) |
| 🔗 | Available only through an external blueprintUE link |
| ⛔ | Not published (binary asset, third-party, or not owned) |
| ⏳ | Pending: not produced or not uploaded yet |

The graph text files live in `text/` and the per-asset API inventories in `inventory/`. Both are generated with `tools/run-export.ps1`.

## 01 — Modular Menu System

| Evidence | Asset path | In repo | blueprintUE | Screenshot | Status |
|---|---|---|---|---|---|
| PlayerController / widget stack initialization | `/Game/_Core/PlayerController/BP_FrontEnd_PlayerController_CommonUI` | `text/` + `inventory/` | [ce246m0h](https://blueprintue.com/blueprint/ce246m0h/) | ⏳ | ✅ text · 🔗 UE |
| Menu modules / back stack | `/Game/UI/CommonUI/MenuScene/ActivatableWidgets/WBP_ButtonsScreen` | `text/` + `inventory/` | [bku8ap6-](https://blueprintue.com/blueprint/bku8ap6-/) | ⏳ | ✅ text · 🔗 UE |
| Main HUD (menu + popup stacks) | `/Game/UI/CommonUI/MenuScene/WBP_MainHUD` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text · ⏳ UE |
| Menu container | `/Game/UI/CommonUI/MenuScene/WBP_MenuContainer` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text · ⏳ UE |
| Main screen | `/Game/UI/CommonUI/MenuScene/ActivatableWidgets/WBP_ButtonsMainScreen` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text · ⏳ UE |
| Play screen | `/Game/UI/CommonUI/MenuScene/ActivatableWidgets/WBP_ButtonsPlayScreen` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text · ⏳ UE |
| Quit confirmation popup | `/Game/UI/CommonUI/MenuScene/ActivatableWidgets/WBP_ConfirmScreen` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text · ⏳ UE |
| Navigation rules data asset + input mapping | `/Game/_Core/Input/Menu/DA_UINavigationRules`, `IMC_Menu`, `IA_Accept`, `IA_CancelBack`, `IA_Any` | ⛔ | — | ⏳ | ⛔ asset · ⏳ capture |
| Custom navigation C++ | `Source/.../CustomNavigationSubsystem.h/.cpp` | ✅ | — | — | ✅ |
| Menu architecture diagram | `docs/diagrams/u3_01_flow_{en,es}.svg` | ✅ | — | — | ✅ |
| Menu sequence diagram | `docs/diagrams/u3_01_sequence_{en,es}.svg` | ✅ | — | — | ✅ |

## 02 — Additive Loading Subsystem

| Evidence | Asset path | In repo | blueprintUE | Screenshot | Status |
|---|---|---|---|---|---|
| Loading subsystem (C++) | `Source/.../LoadingSubsystem.h/.cpp` | ✅ | — | — | ✅ |
| Loading sequence diagram | `docs/diagrams/u3_02_loading_{en,es}.svg` | ✅ | — | — | ✅ |
| Loading screen widget | `/Game/UI/CommonUI/WBP_LoadingScreen` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text · ⏳ UE |
| Front-end game mode | `/Game/_Core/GameMode/BP_FrontEnd_GameMode_CommonUI` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text · ⏳ UE |

> The loading implementation uses `StreamableManager`, a GameViewport widget (Z 999), progress timers and `PostLoadMapWithWorld`. It does **not** use the engine `MoviePlayer` API; the previous portfolio text was corrected.

## 03 — 2.5D Spline Navigation

| Evidence | Asset path | In repo | blueprintUE | Screenshot | Status |
|---|---|---|---|---|---|
| Spline character (movement pipeline) | `/Game/Characters/Player/BP_SplineCharacter_Restruct` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text · ⏳ UE |
| Spline route actor | `/Game/Environment/Interactives/SplineRoutes/BP_SplineRoute` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text · ⏳ UE |
| Junction / route switch trigger | `/Game/Environment/Interactives/SplineRoutes/BP_JunctionTrigger` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text · ⏳ UE |
| Route interface | `/Game/Interfaces/BPI_SetRouteAndPosition` | `inventory/` | ⏳ | ⏳ | ✅ API · ⏳ UE |
| Spline flow diagram | `docs/diagrams/u3_03_spline_{en,es}.svg` | ✅ | — | — | ✅ |

## 04 — Decoupled Puzzle Architecture

| Evidence | Asset path | In repo | blueprintUE | Screenshot | Status |
|---|---|---|---|---|---|
| Trigger interface | `/Game/Interfaces/BPI_TriggerInteract` | `inventory/` | ⏳ | ⏳ | ✅ API · ⏳ UE |
| Resolution reporter interface | `/Game/Interfaces/BPI_PuzzleResolutionReporter` | `inventory/` | ⏳ | ⏳ | ✅ API · ⏳ UE |
| Pressure plate | `/Game/Environment/Interactives/BP_PressureSwitch` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text · ⏳ UE |
| Resolver door | `/Game/Environment/Interactives/BP_DoorToOpen` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text · ⏳ UE |
| Rotator puzzle | `/Game/Environment/Interactives/RotatorCylinder/BP_RotatorCylinder_Puzzle` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text · ⏳ UE |
| Puzzle feedback | `/Game/Environment/Interactives/RotatorCylinder/BP_SumarizerPuzzlesFeedBack` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text · ⏳ UE |
| Reference Viewer proof (no hard references) | — | ⏳ | — | ⏳ | ⏳ |
| Puzzle flow diagram | `docs/diagrams/u3_04_puzzles_{en,es}.svg` | ✅ | — | — | ✅ |

## 05 — Event-Driven Communication

| Evidence | Asset path | In repo | blueprintUE | Screenshot | Status |
|---|---|---|---|---|---|
| Quit confirmation dispatchers | `WBP_ConfirmScreen` → `OnCancelConfirmTriggered`, `OnAcceptConfirmTriggered` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text |
| Main menu dispatchers | `WBP_ButtonsMainScreen` → `OnBackInputTriggered`, `OnQuitClickedTriggered` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text |
| Play screen dispatchers | `WBP_ButtonsPlayScreen` → `OnBackInputTriggered`, `OnPlayNewGame` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text |
| Module navigation | `WBP_ButtonsScreen` → `OnBackToAnyKeySCreen` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text |
| Any-key screens | `WBP_CleanScreen`, `WBP_PressAnyKeyScreen` → `OnAnyKeyPressed` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text |
| Player location event | `BP_PlayerController` → `SetPlayerLocationDispatcher` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text |
| Puzzle event | `BP_SwitchDispatcher` → `OnEndActivate` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text |
| Pause menu | `WBP_PauseMainMenu` → `CancelPauseDispatcher` | `text/` + `inventory/` | ⏳ | ⏳ | ✅ text |
| Event flow diagram | `docs/diagrams/u3_05_events_{en,es}.svg` | ✅ | — | — | ✅ |

## Not published (all modules)

| Item | Reason |
|---|---|
| Any `.uasset` / `.umap` (including the original Blueprint assets) | Binary, not reviewable, third-party content |
| `Content/` maps, art, characters, environment | 3.73 GB and licensing |
| Marketplace plugin `One Click Control Rig_5.6` | Third-party |
| Generated build artifacts | Not source |

## Pending checklist

- [x] Generate graph text and inventories (32 assets, 101 graphs).
- [x] Identify event-dispatcher names for module 05.
- [ ] Upload the remaining graphs to blueprintUE and replace ⏳ in the UE column.
- [ ] Add editor screenshots (Widget Designer, Class Settings → Interfaces, Reference Viewer, Find in Blueprints).
- [ ] Add gameplay image/video evidence per module.
