[CmdletBinding()]
param(
    [string]$ProjectPath = 'D:\crtic_project_anim_vg_26\UE_Project\SplinePlatformerTest\SplinePlatformerTest.uproject',
    [string]$RepoRoot = '',
    [string]$EngineDir = 'D:\Program Files\Epic Games\UE_5.7',
    [string]$Include = '/Game/_Core,/Game/UI/CommonUI,/Game/Interfaces,/Game/Characters/Player,/Game/Environment/Interactives',
    [string]$Exclude = '/Game/Village,/Game/Cinematic,/Game/Fab,/Game/FreeParticle_SoftTofu,/Game/Developers',
    [string]$Names = 'BP_FrontEnd_PlayerController_CommonUI,BP_PlayerController,BP_HUD,BP_GameMode,BP_FrontEnd_GameMode_CommonUI,WBP_MainHUD,WBP_MenuContainer,WBP_ButtonsScreen,WBP_ButtonsMainScreen,WBP_ButtonsPlayScreen,WBP_ConfirmScreen,WBP_PressAnyKeyScreen,WBP_CleanScreen,WBP_CB_MenuButton,WBP_OptionsSliderMenu,WBP_SliderItem,WBP_PauseMainMenu,WBP_LoadingScreen,BP_SplineCharacter_Restruct,BP_SplineRoute,BP_JunctionTrigger,BP_CameraTrigger,BPI_SetRouteAndPosition,BPI_TriggerInteract,BPI_PuzzleResolutionReporter,BPI_TurnOn,BP_PressureSwitch,BP_DoorToOpen,BP_RotatorCylinder_Puzzle,BP_SumarizerPuzzlesFeedBack,BP_ValidatorRotatorsSum,BP_SwitchDispatcher'
)

$ErrorActionPreference = 'Stop'

if ([string]::IsNullOrWhiteSpace($RepoRoot)) {
    $RepoRoot = Split-Path -Parent $PSScriptRoot
}
if ([string]::IsNullOrWhiteSpace($RepoRoot)) {
    throw 'RepoRoot could not be resolved; pass -RepoRoot explicitly.'
}

if (-not (Test-Path -LiteralPath $ProjectPath)) { throw "Project not found: $ProjectPath" }
if (-not (Test-Path -LiteralPath $EngineDir)) { throw "Engine not found: $EngineDir" }

$projectDir  = Split-Path -Parent $ProjectPath
$projectName = [System.IO.Path]::GetFileNameWithoutExtension($ProjectPath)
$buildBat    = Join-Path $EngineDir 'Engine\Build\BatchFiles\Build.bat'
$editorCmd   = Join-Path $EngineDir 'Engine\Binaries\Win64\UnrealEditor-Cmd.exe'
$pluginSrc   = Join-Path $RepoRoot 'tools\BlueprintTextExporter'
$pluginLink  = Join-Path $projectDir 'Plugins\BlueprintTextExporter'
$outDir      = Join-Path $RepoRoot 'docs\blueprints'
$buildLog    = Join-Path $outDir 'export-build.log'
$runLog      = Join-Path $outDir 'export-run.log'

foreach ($required in @($buildBat, $editorCmd, $pluginSrc)) {
    if (-not (Test-Path -LiteralPath $required)) { throw "Missing required path: $required" }
}
if (Test-Path -LiteralPath $pluginLink) { throw "Plugin link already exists: $pluginLink" }

New-Item -ItemType Directory -Path $outDir -Force | Out-Null

try {
    cmd /c mklink /J "$pluginLink" "$pluginSrc" | Out-Null
    Write-Host "Linked plugin: $pluginLink"

    Write-Host "Building $projectName`Editor (Win64, Development)..."
    & $buildBat "$($projectName)Editor" Win64 Development -Project="$ProjectPath" -WaitMutex 2>&1 |
        Out-File -FilePath $buildLog -Encoding utf8
    if ($LASTEXITCODE -ne 0) {
        Get-Content $buildLog -Tail 60
        throw "Build failed with exit code $LASTEXITCODE (see $buildLog)"
    }

    Write-Host "Cleaning previous exports..."
    Remove-Item (Join-Path $outDir 'text\*') -Force -ErrorAction SilentlyContinue
    Remove-Item (Join-Path $outDir 'inventory\*') -Force -ErrorAction SilentlyContinue
    Remove-Item (Join-Path $outDir 'manifest.csv') -Force -ErrorAction SilentlyContinue

    Write-Host "Running BlueprintTextExporter commandlet..."
    $editorArgs = @(
        "$ProjectPath",
        "-run=BlueprintTextExporter",
        "-out=$outDir",
        "-include=$Include",
        "-exclude=$Exclude",
        "-EnablePlugins=BlueprintTextExporter",
        "-unattended", "-nop4", "-nosplash", "-stdout", "-FullStdOutLogOutput"
    )
    if (-not [string]::IsNullOrWhiteSpace($Names)) { $editorArgs += "-names=$Names" }
    & $editorCmd @editorArgs 2>&1 | Out-File -FilePath $runLog -Encoding utf8
    if ($LASTEXITCODE -ne 0) {
        Get-Content $runLog -Tail 80
        throw "Commandlet failed with exit code $LASTEXITCODE (see $runLog)"
    }

    Get-Content $runLog -Tail 25
    Write-Host "Export completed. Output: $outDir"
}
finally {
    if (Test-Path -LiteralPath $pluginLink) {
        cmd /c rmdir "$pluginLink" | Out-Null
        Write-Host "Removed plugin junction."
    }

    Get-ChildItem (Join-Path $projectDir 'Binaries\Win64') -Filter '*BlueprintTextExporter*' -ErrorAction SilentlyContinue |
        Remove-Item -Force -ErrorAction SilentlyContinue
    Get-ChildItem (Join-Path $projectDir 'Intermediate\Build') -Recurse -Directory -Filter '*BlueprintTextExporter*' -ErrorAction SilentlyContinue |
        Remove-Item -Recurse -Force -ErrorAction SilentlyContinue

    # The junction makes UnrealBuildTool write into the plugin source folder.
    foreach ($artifact in @('Binaries', 'Intermediate', 'Saved')) {
        $artifactPath = Join-Path $pluginSrc $artifact
        if (Test-Path -LiteralPath $artifactPath) {
            Remove-Item $artifactPath -Recurse -Force -ErrorAction SilentlyContinue
        }
    }
}
