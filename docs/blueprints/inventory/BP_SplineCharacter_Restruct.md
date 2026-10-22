# BP_SplineCharacter_Restruct

- **Asset path:** `/Game/Characters/Player/BP_SplineCharacter_Restruct.BP_SplineCharacter_Restruct`
- **Parent class:** `Character`
- **Blueprint type:** BPTYPE_Normal
- **Interfaces:** None

## Variables

| Name | Type | Default |
|---|---|---|
| `SplinePath` | `object:BP_SplineRoute_C` | `` |
| `CurrentDistanceAlongSpline` | `real:double` | `` |
| `CollisionPercentage` | `real:double` | `` |
| `CollisionDeltaStartPosition` | `real:double` | `` |
| `CollisionDeltaEndPosition` | `real:double` | `` |
| `Z-Offset` | `real:double` | `` |
| `SmoothCameraAhead ` | `real:double` | `` |
| `LastDirectionInput` | `real:double` | `` |
| `OffSetCameraSpingArm` | `real:double` | `` |
| `TargetCameraZoom` | `real:double` | `` |
| `TargetCameraPitch` | `real:double` | `` |
| `TargetCameraYaw` | `real:double` | `` |
| `ActualJunctionRoute` | `object:BP_JunctionTrigger_C` | `` |
| `PreviousFramePosition` | `struct:Vector` | `` |
| `PossibleDistanceAlongSpline` | `real:double` | `` |
| `VirtualVelocity` | `real:double` | `` |
| `TargetVisualRotation` | `struct:Rotator` | `` |
| `DesiredVelocityFrame ` | `real:double` | `` |
| `FixedOffsetSpline` | `real:double` | `` |
| `OffsetCaptureRequested` | `bool` | `` |
| `FakeMovilCeiling` | `object:BP_FakeCeiling_C` | `` |
| `WantsToCrouch ` | `bool` | `` |
| `InteractiveRegionZone` | `interface:BPI_TriggerInteract_C` | `` |
| `ExtraCameraYaw` | `real:double` | `` |

## Functions

- `UserConstructionScript`
- `VelocityDeathZone`
- `ChangeSpline`
- `AuxGetDeltaDistanceCurrentAndPossible`
- `CalcCrouchDiff`

## Event Dispatchers

_None_

## Components

- `Cube` (StaticMeshComponent)
- `Cube1` (StaticMeshComponent)
- `SpringArm` (SpringArmComponent)
- `Camera` (CameraComponent)

## Graphs

| Graph | Nodes | Text export |
|---|---:|---|
| `EventGraph` | 277 | `text/BP_SplineCharacter_Restruct__EventGraph.txt` |
| `UserConstructionScript` | 1 | `text/BP_SplineCharacter_Restruct__UserConstructionScript.txt` |
| `VelocityDeathZone` | 9 | `text/BP_SplineCharacter_Restruct__VelocityDeathZone.txt` |
| `ChangeSpline` | 5 | `text/BP_SplineCharacter_Restruct__ChangeSpline.txt` |
| `AuxGetDeltaDistanceCurrentAndPossible` | 14 | `text/BP_SplineCharacter_Restruct__AuxGetDeltaDistanceCurrentAndPossible.txt` |
| `CalcCrouchDiff` | 7 | `text/BP_SplineCharacter_Restruct__CalcCrouchDiff.txt` |

