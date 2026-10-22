# Diagrams

Architecture diagrams for the five systems, in **English and Spanish**. Only descriptive text changes between languages; class, asset, node and dispatcher names are intentionally kept in English.

## Naming

```
src/u3_<module>_<diagram>.<lang>.mmd    Mermaid source
u3_<module>_<diagram>_<lang>.svg        Published SVG
```

Current files:

| Module | Diagram | Sources | Outputs |
|---|---|---|---|
| 01 | Menu architecture (flowchart) | `src/u3_01_flow.{en,es}.mmd` | `u3_01_flow_{en,es}.svg` |
| 01 | Menu runtime (sequence) | `src/u3_01_sequence.{en,es}.mmd` | `u3_01_sequence_{en,es}.svg` |
| 02 | Loading flow (sequence) | `src/u3_02_loading.{en,es}.mmd` | `u3_02_loading_{en,es}.svg` |
| 03 | Spline pipeline | `src/u3_03_spline.{en,es}.mmd` | `u3_03_spline_{en,es}.svg` |
| 04 | Decoupled puzzles | `src/u3_04_puzzles.{en,es}.mmd` | `u3_04_puzzles_{en,es}.svg` |
| 05 | Event dispatchers | `src/u3_05_events.{en,es}.mmd` | `u3_05_events_{en,es}.svg` |

## Regenerating

Requires Node 18+ and a local Chrome/Edge installation:

```powershell
$cfg = Join-Path $env:TEMP 'mmdc-puppeteer.json'
$json = @{ executablePath = 'C:\Program Files\Google\Chrome\Application\chrome.exe'; args = @('--no-sandbox','--disable-gpu') } | ConvertTo-Json -Compress
[System.IO.File]::WriteAllText($cfg, $json, (New-Object System.Text.UTF8Encoding($false)))
$env:PUPPETEER_SKIP_DOWNLOAD = '1'
npx --yes @mermaid-js/mermaid-cli@11 -p $cfg -i docs/diagrams/src/u3_02_loading.en.mmd -o docs/diagrams/u3_02_loading_en.svg -t dark -b '#1e1e1e' -w 1600
```

> The Puppeteer config must be written without a BOM; otherwise `mermaid-cli` fails to parse the JSON.
