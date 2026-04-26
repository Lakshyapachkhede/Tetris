$debug = $true

# Define directories and file names
$sourceDir = ".\"  # Directory containing source files
$outputDir = "."  # Output directory for the compiled executable
$outputFile = "Tetris.exe"  # Output executable name





# Ensure output directory exists
if (!(Test-Path -Path $outputDir)) {
    New-Item -ItemType Directory -Path $outputDir
}

# Find all source files
$sourceFiles = Get-ChildItem -Path $sourceDir -Filter "*.c" -Recurse | ForEach-Object { $_.FullName }

if (-not $sourceFiles) {
    Write-Host "No source files found in $sourceDir" -ForegroundColor Red
    exit 1
}

# Set compiler and flags
$compiler = "gcc"
$compileFlags = "-I..\include -L..\lib -lraylib -lopengl32 -lgdi32 -lwinmm -std=c11 -Wall -Wextra -I$sourceDir"

if(!$debug){
    $compileFlags = $compileFlags + " -mwindows"
}

$compileCommand = "$compiler $($sourceFiles -join ' ') $compileFlags -o $outputDir\$outputFile"

# Compile the source files
Write-Host "Compiling source files..." -ForegroundColor Yellow
Write-Host "Running: $compileCommand" -ForegroundColor Cyan

Invoke-Expression -Command $compileCommand

if ($LASTEXITCODE -ne 0) {
    Write-Host "Compilation failed!" -ForegroundColor Red
    exit 1
}

Write-Host "Compilation successful. Output: $outputDir\$outputFile" -ForegroundColor Green

# Run the executable
Write-Host "Running the program..." -ForegroundColor Yellow
$executionCommand = ".\$outputFile"
Invoke-Expression -Command $executionCommand

