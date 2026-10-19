$ErrorActionPreference = 'Stop'
$root = $PSScriptRoot
$cmake = Get-Command cmake -ErrorAction SilentlyContinue
if (-not $cmake) {
    throw 'CMake is required to build and compare TTL8 and TTL4. Install CMake and a C++17 compiler, then run this script again.'
}

function Build-Project([string]$source, [string]$build) {
    & $cmake.Source -S $source -B $build
    if ($LASTEXITCODE -ne 0) { throw "CMake configure failed for $source" }
    & $cmake.Source --build $build --config Release
    if ($LASTEXITCODE -ne 0) { throw "Build failed for $source" }
}

function Find-Executable([string]$build, [string]$name) {
    $item = Get-ChildItem -LiteralPath $build -Filter $name -File -Recurse | Select-Object -First 1
    if (-not $item) { throw "Could not find $name under $build" }
    return $item.FullName
}

$ttl8Build = Join-Path $root 'build-ttl8'
$ttl4Build = Join-Path $root 'ttl4\build'
Build-Project $root $ttl8Build
Build-Project (Join-Path $root 'ttl4') $ttl4Build

$ttl8Asm = Find-Executable $ttl8Build 'ttl8-as.exe'
$ttl8Run = Find-Executable $ttl8Build 'ttl8-run.exe'
$ttl4Asm = Find-Executable $ttl4Build 'ttl4-as.exe'
$ttl4Run = Find-Executable $ttl4Build 'ttl4-run.exe'
$ttl8Bin = Join-Path $ttl8Build 'compare_add.bin'
$ttl4Bin = Join-Path $ttl4Build 'compare_add.bin'

& $ttl8Asm (Join-Path $root 'programs\compare_add.asm') $ttl8Bin
if ($LASTEXITCODE -ne 0) { throw 'TTL8 assembly failed' }
& $ttl4Asm (Join-Path $root 'ttl4\programs\compare_add.asm') $ttl4Bin
if ($LASTEXITCODE -ne 0) { throw 'TTL4 assembly failed' }

$ttl8Output = (& $ttl8Run $ttl8Bin) -join ', '
if ($LASTEXITCODE -ne 0) { throw 'TTL8 execution failed' }
$ttl4Output = (& $ttl4Run $ttl4Bin) -join ', '
if ($LASTEXITCODE -ne 0) { throw 'TTL4 execution failed' }

[pscustomobject]@{
    Program = '3 + 5'
    TTL8_Output = $ttl8Output
    TTL4_Output = $ttl4Output
    Match = ($ttl8Output.Trim().PadLeft(2, '0') -eq $ttl4Output.Trim().PadLeft(2, '0'))
} | Format-Table -AutoSize
