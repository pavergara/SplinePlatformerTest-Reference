# BP_DoorToOpen

- **Asset path:** `/Game/Environment/Interactives/BP_DoorToOpen.BP_DoorToOpen`
- **Parent class:** `Actor`
- **Blueprint type:** BPTYPE_Normal
- **Interfaces:** BPI_TurnOn_C

## Variables

| Name | Type | Default |
|---|---|---|
| `IsOpen` | `bool` | `` |
| `OpenUp` | `bool` | `` |
| `Return Value Z` | `real:double` | `` |
| `DisplacementToOpenZ` | `real:double` | `` |
| `Switch` | `object:BP_SwitchDispatcher_C` | `` |

## Functions

- `UserConstructionScript`

## Event Dispatchers

_None_

## Components

- `DefaultSceneRoot` (SceneComponent)
- `DoorBox` (StaticMeshComponent)
- `DoorBoxBlocking` (StaticMeshComponent)

## Graphs

| Graph | Nodes | Text export |
|---|---:|---|
| `EventGraph` | 24 | `text/BP_DoorToOpen__EventGraph.txt` |
| `UserConstructionScript` | 1 | `text/BP_DoorToOpen__UserConstructionScript.txt` |

