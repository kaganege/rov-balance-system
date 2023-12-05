Param (
  [string]$Path
)

if (-not (Test-Path ".\platformio.ini" -PathType Leaf) -and (Test-Path "..\platformio.ini" -PathType Leaf)) {
  Set-Location ..
}
else {
  Write-Host "Project folder can not found!"
  Exit 1
}

if ($Path) {
  & .\build.ps1
  
  Copy-Item .\build\firmware.uf2 -Destination $Path

  Exit 0
}
else {
  Write-Host "Please specify the upload path"
  
  Exit 1
}
