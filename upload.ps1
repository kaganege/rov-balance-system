Param (
  [string]$Path
)

if ($Path) {
  & .\build.ps1
  
  Copy-Item .\build\firmware.uf2 -Destination $Path

  Exit 0
}
else {
  Write-Host "Please specify the upload path"
  
  Exit 1
}
