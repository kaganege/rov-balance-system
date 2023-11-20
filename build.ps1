$platformio = "$HOME\.platformio\penv\Scripts\platformio.exe"

if (Test-Path -Path $platformio -PathType Leaf) {
  & $platformio run

  if (Test-Path .\build -PathType Container) {
    Remove-Item .\build\*
  }
  else {
    New-Item build -ItemType Directory
  }
  
  Get-Item .\.pio\build\rpipicow\firmware.* | Move-Item -Destination .\build\
}
else {
  Write-Host "Platformio can not found!"
  Read-Host -Prompt "Press Enter to continue..."
}