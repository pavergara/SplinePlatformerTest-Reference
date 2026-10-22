# BP_RotatorCylinder_Puzzle

- **Asset path:** `/Game/Environment/Interactives/RotatorCylinder/BP_RotatorCylinder_Puzzle.BP_RotatorCylinder_Puzzle`
- **Parent class:** `Actor`
- **Blueprint type:** BPTYPE_Normal
- **Interfaces:** BPI_TriggerInteract_C, BPI_PuzzleResolutionReporter_C

## Variables

| Name | Type | Default |
|---|---|---|
| `numOfFaces` | `int` | `` |
| `rotatorDistance` | `real:double` | `` |
| `IsRotating` | `bool` | `` |
| `CurrentFaceIndex` | `int` | `` |
| `TempYawValue` | `real:double` | `` |
| `DesiredIndex` | `int` | `` |
| `SwitchSum` | `object:BP_ValidatorRotatorsSum_C` | `` |
| `cutomOrderIndex` | `int` | `` |

## Functions

- `UserConstructionScript`

## Event Dispatchers

_None_

## Components

- `DefaultSceneRoot` (SceneComponent)
- `Cube` (StaticMeshComponent)
- `Box` (BoxComponent)
- `Cylinder` (StaticMeshComponent)
- `RotatorCenter_0` (SceneComponent)

## Graphs

| Graph | Nodes | Text export |
|---|---:|---|
| `EventGraph` | 63 | `text/BP_RotatorCylinder_Puzzle__EventGraph.txt` |
| `UserConstructionScript` | 18 | `text/BP_RotatorCylinder_Puzzle__UserConstructionScript.txt` |

