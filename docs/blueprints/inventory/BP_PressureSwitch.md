# BP_PressureSwitch

- **Asset path:** `/Game/Environment/Interactives/BP_PressureSwitch.BP_PressureSwitch`
- **Parent class:** `BP_SwitchDispatcher_C`
- **Blueprint type:** BPTYPE_Normal
- **Interfaces:** BPI_TriggerInteract_C

## Variables

| Name | Type | Default |
|---|---|---|
| `IsActivated` | `bool` | `` |
| `Seq` | `struct:RigVMFunction_Sequence` | `` |
| `DeltaPressure` | `real:double` | `` |
| `Return Value Z` | `real:double` | `` |
| `ActivateOnce` | `bool` | `` |
| `ToActivates` | `Array<object:Actor>` | `` |
| `TimeToSwitch` | `real:double` | `` |

## Functions

- `UserConstructionScript`

## Event Dispatchers

_None_

## Components

- `Cube` (StaticMeshComponent)
- `Cube1` (StaticMeshComponent)
- `Box` (BoxComponent)

## Graphs

| Graph | Nodes | Text export |
|---|---:|---|
| `EventGraph` | 39 | `text/BP_PressureSwitch__EventGraph.txt` |
| `UserConstructionScript` | 1 | `text/BP_PressureSwitch__UserConstructionScript.txt` |

