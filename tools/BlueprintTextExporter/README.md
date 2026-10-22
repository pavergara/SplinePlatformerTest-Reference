# Blueprint Text Exporter (editor plugin)

Small Unreal Engine editor plugin that exports every Blueprint graph to the text format used by blueprintUE, plus a per-asset inventory.

## Why a plugin is required

`FEdGraphUtilities::ExportNodesToText` — the function that produces the clipboard text — is C++-only. It is not exposed to Python or to `UnrealEditor-Cmd` commandlets by default, so a small editor module is the only reliable way to automate the extraction without opening and copying each graph by hand.

## Usage

From the repository root:

```powershell
.\tools\run-export.ps1
```

The script:

1. Creates a directory junction `SplinePlatformerTest/Plugins/BlueprintTextExporter` pointing to this folder.
2. Builds the editor target with `Build.bat`.
3. Runs `UnrealEditor-Cmd.exe -run=BlueprintTextExporter`.
4. Removes the junction and the plugin build artifacts.

No asset is modified. The editor must be closed while the script runs.

### Manual invocation

```powershell
UnrealEditor-Cmd.exe "<Project>.uproject" -run=BlueprintTextExporter `
  -out="<Repo>\docs\blueprints" `
  -include="/Game/_Core,/Game/UI/CommonUI,/Game/Interfaces" `
  -exclude="/Game/Village,/Game/Cinematic,/Game/Fab" `
  -names="BP_FrontEnd_PlayerController_CommonUI,WBP_MainHUD,WBP_ButtonsScreen" `
  -unattended -nop4 -nosplash -stdout
```

`-names` is an optional allowlist of asset short names. Omit it to export every Blueprint under the included folders (this may include animation blueprints and old versions).

## Output

| Path | Content |
|---|---|
| `text/<Asset>__<Graph>.txt` | Graph text, pasteable into blueprintUE |
| `inventory/<Asset>.md` | Parent class, interfaces, variables, functions, event dispatchers, components, graph list |
| `manifest.csv` | Asset, graph, file and status for every processed graph |
| `export-build.log` / `export-run.log` | Build and commandlet logs |

## Notes

- Only Blueprints are read; materials, meshes and maps are ignored.
- `Content` is never written to.
- If the build or the commandlet fails, the junction is removed anyway (the cleanup runs in a `finally` block).
- Plugin binaries are deleted after the run; the project module may be rebuilt by `Build.bat`, which is normal.
