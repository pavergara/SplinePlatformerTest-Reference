# Scope of this reference repository

This repository is a **source-only reference** for portfolio review. It is not a distributable game and it is not a runnable project.

## Included

| Item | Path | Size (approx.) | Why |
|---|---|---|---|
| C++ source | `Source/` | 13 KB | The actual implementation, readable and diffable |
| Sanitized config | `Config/DefaultEngine.ini`, `DefaultGame.ini`, `DefaultInput.ini`, `DefaultGameplayTags.ini` | 45 KB | Shows CommonUI viewport setup, input mappings and packaging settings |
| Project descriptor | `SplinePlatformerTest.uproject` | < 1 KB | Engine version and module/plugin dependencies |
| Controls | `Controls.txt` | < 1 KB | Keyboard/gamepad mapping of the demo |
| Blueprint graph text | `docs/blueprints/text/*.txt` | 4.4 MB (101 files) | Text exports of the graphs (blueprintUE-compatible) |
| Blueprint inventory | `docs/blueprints/inventory/*.md` | 30 KB (32 files) | Parent class, interfaces, variables, functions, dispatchers and components |
| Diagrams | `docs/diagrams/` | 12 SVG + 12 MMD | Architecture diagrams in English and Spanish |
| Screenshots | `docs/screenshots/` | varies | Editor and gameplay evidence |
| Export tooling | `tools/BlueprintTextExporter/`, `tools/run-export.ps1` | small | Reproducible Blueprint text extraction |

## Not included

| Item | Size | Reason |
|---|---:|---|
| `Content/` (2,092 `.uasset`/`.umap` files) | 3.73 GB | Binary assets; not reviewable on GitHub; includes third-party content that cannot be redistributed |
| `Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/`, `Build/` | ~11.6 GB | Generated build artifacts |
| `Plugins/One Click Control Rig_5.6` | 3.4 MB | Marketplace plugin, not authored in this project |
| `Config/DefaultEditor.ini` | 55 KB | Local editor preferences, not project logic |
| `.vs/`, `.vscode/`, `*.code-workspace` | small | Local IDE configuration |
| `SecurityToken` line in `DefaultEngine.ini` | — | Removed before publication |
| Employer/client code | — | Not owned by the author (NDA) |

## Blueprint assets

The original Blueprint assets are **not redistributed**. Their logic is documented through:

1. Text exports of the graph (`docs/blueprints/text/`), which are the same format blueprintUE consumes.
2. A metadata inventory (`docs/blueprints/inventory/`).
3. External blueprintUE links (`docs/blueprints/README.md`).
4. Editor screenshots (`docs/screenshots/`).

This keeps the reference readable without shipping binary assets or third-party content.

## Legal notes

- Unreal Engine and Unreal are trademarks of Epic Games, Inc. This repository is not affiliated with or endorsed by Epic Games.
- Marketplace/Fab content referenced by the project is not redistributed.
- The code and documentation are shared for portfolio review only. See `LICENSE`.

## Maintenance

When a new Blueprint is added to the public evidence, update:

1. `docs/blueprints/README.md` (coverage matrix and status).
2. The generated `text/` and `inventory/` files, running `tools/run-export.ps1`.
3. The portfolio entry, if the new evidence is published there.
