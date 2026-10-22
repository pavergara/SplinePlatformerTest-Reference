# BP_ValidatorRotatorsSum

- **Asset path:** `/Game/Environment/Interactives/RotatorCylinder/BP_ValidatorRotatorsSum.BP_ValidatorRotatorsSum`
- **Parent class:** `BP_SwitchDispatcher_C`
- **Blueprint type:** BPTYPE_Normal
- **Interfaces:** None

## Variables

| Name | Type | Default |
|---|---|---|
| `PuzzlesToValidate` | `Array<interface:BPI_PuzzleResolutionReporter_C>` | `` |
| `AllResolved` | `bool` | `` |

## Functions

- `UserConstructionScript`
- `AddRotatorToEvaluate`
- `SumarizeResolvedPuzzles`
- `ReorderByCustomIndex`
- `CustomOrderAvailable`

## Event Dispatchers

_None_

## Components

- `Sphere` (StaticMeshComponent)
- `BP_SumarizerPuzzlesFeedBack` (ChildActorComponent)

## Graphs

| Graph | Nodes | Text export |
|---|---:|---|
| `EventGraph` | 11 | `text/BP_ValidatorRotatorsSum__EventGraph.txt` |
| `UserConstructionScript` | 1 | `text/BP_ValidatorRotatorsSum__UserConstructionScript.txt` |
| `AddRotatorToEvaluate` | 11 | `text/BP_ValidatorRotatorsSum__AddRotatorToEvaluate.txt` |
| `SumarizeResolvedPuzzles` | 26 | `text/BP_ValidatorRotatorsSum__SumarizeResolvedPuzzles.txt` |
| `ReorderByCustomIndex` | 17 | `text/BP_ValidatorRotatorsSum__ReorderByCustomIndex.txt` |
| `CustomOrderAvailable` | 25 | `text/BP_ValidatorRotatorsSum__CustomOrderAvailable.txt` |

