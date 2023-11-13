Set-Alias pio "$HOME\.platformio\penv\Scripts\platformio.exe"

if (Test-Path -Path pio -PathType Leaf) {
  pio run

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