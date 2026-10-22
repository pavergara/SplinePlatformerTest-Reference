# UE5 Core Systems — Source Reference

> **Scope: source-only reference.** This repository contains the C++ source, sanitized config, text exports of the Blueprint graphs and documentation for a personal Unreal Engine 5 project. It does **not** include `Content/` (`.uasset`/`.umap`, maps, art), binaries, or third-party plugins. Blueprint assets are not redistributed; their graphs are published as text and on blueprintUE. See [docs/SCOPE.md](docs/SCOPE.md).

**Engine:** Unreal Engine 5.7.4 · **Language:** C++ + Blueprints · **Status:** documentation in progress
**Portfolio:** https://pavergara.github.io

## What this project demonstrates

A single codebase with five engine-level systems:

| # | System | Main evidence |
|---|---|---|
| 01 | Modular Menu System (CommonUI + C++) | `CustomNavigationSubsystem` · `BP_FrontEnd_PlayerController_CommonUI` · `WBP_MainHUD` · `WBP_ButtonsScreen` · [blueprintUE: stack init](https://blueprintue.com/blueprint/ce246m0h/) · [blueprintUE: menu modules](https://blueprintue.com/blueprint/bku8ap6-/) |
| 02 | Additive Loading Subsystem | `LoadingSubsystem` (`UGameInstanceSubsystem`) · `WBP_LoadingScreen` |
| 03 | 2.5D Spline Navigation | `BP_SplineCharacter_Restruct` · `BP_SplineRoute` · `BP_JunctionTrigger` · `BPI_SetRouteAndPosition` |
| 04 | Decoupled Puzzle Architecture | `BPI_TriggerInteract` · `BPI_PuzzleResolutionReporter` · `BP_PressureSwitch` · `BP_DoorToOpen` |
| 05 | Event-Driven Communication | Event Dispatchers (emitter/listener graphs, see inventory) |

Detailed coverage and pending items: **[docs/blueprints/README.md](docs/blueprints/README.md)**.

**Generated evidence:** 32 Blueprints · 101 graph text files · 32 inventories · 12 SVG diagrams (6 diagrams × EN/ES).

## Repository layout

```
Source/                     C++ source (runtime module)
Config/                     Sanitized project configuration
SplinePlatformerTest.uproject
Controls.txt                Keyboard and gamepad mappings
docs/
  SCOPE.md                  What is included and what is not
  blueprints/
    README.md               Coverage matrix and status
    text/                   Blueprint graph text exports (blueprintUE format)
    inventory/              Per-Blueprint API inventory (Markdown)
  screenshots/              Editor and gameplay evidence
  diagrams/                 Mermaid sources and SVG diagrams (EN/ES)
tools/
  BlueprintTextExporter/    Editor commandlet used to export Blueprint text
  run-export.ps1            One-command build + export helper
```

## How to read the C++

- `Source/SplinePlatformerTest/Public/LoadingSubsystem.h` and `Private/LoadingSubsystem.cpp`
  The async loading flow: `StreamableManager` request, GameViewport widget (Z 999), progress timer (0.01 s), `PostLoadMapWithWorld`, configurable delay and fade-out.
- `Source/SplinePlatformerTest/Public/CustomNavigationSubsystem.h` and `Private/CustomNavigationSubsystem.cpp`
  Injects custom key-to-navigation rules (WASD) into Slate's `FNavigationConfig` from a `UCustomNavigationDataAsset`.

## Blueprint text exports

Blueprint `.uasset` files are binary and are not included. The readable representation is the graph text that Unreal copies to the clipboard (the same format used by blueprintUE), stored under `docs/blueprints/text/`.

To regenerate the exports:

```powershell
.\tools\run-export.ps1
```

The script links `tools/BlueprintTextExporter` into the UE project temporarily, builds the editor target, runs `UnrealEditor-Cmd.exe -run=BlueprintTextExporter`, and removes the link. It only reads assets; no asset is modified.

## Notes and limitations

- This is **not a runnable build**: maps, assets and third-party plugins are intentionally excluded.
- Some Blueprint graphs depend on assets that are not public; the text exports document the logic, not the full asset graph.
- Third-party Marketplace content is not redistributed.
- See [LICENSE](LICENSE). Portfolio review only.
