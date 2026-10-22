# Screenshots

Static evidence for things that graph text does not convey. **No screenshots are included yet**; this folder is ready for them.

## What to capture

| Type | Example | What it proves |
|---|---|---|
| Editor — Widget Designer | `WBP_MainHUD`, `WBP_ButtonsScreen` | The real CommonUI hierarchy (menu stack + popup stack) |
| Editor — Class Settings → Interfaces | `BP_DoorToOpen` | The resolver implements the puzzle interface |
| Editor — Reference Viewer | `BP_PressureSwitch` | The door does not appear in its dependencies (no hard references) |
| Editor — Find in Blueprints | Dispatcher name | All actors/UI bound to the same event |
| Editor — Details | `IMC_Menu`, `DA_UINavigationRules` | Custom WASD input mapping |
| Gameplay | Loading screen, spline path, puzzle solved | The system running in the demo |

## Naming

```
<module>_<asset>_<what>.<png>
```

Examples:

```
01_wbp_mainhud_widget-designer.png
01_da_uinavigationrules_details.png
02_loading-screen_gameplay.png
04_bp_door_interfaces.png
04_reference-viewer_pressure-switch.png
05_find-in-blueprints_dispatcher.png
```

## Guidelines

- Prefer PNG for UI/editor captures; WebP or JPG for gameplay stills.
- Keep each file under ~250 KB when possible.
- Crop to the relevant panel; avoid full-desktop captures.
- Do not include personal paths, usernames, tokens or unrelated editor tabs.
- Update the coverage matrix in `docs/blueprints/README.md` when a capture is added.
