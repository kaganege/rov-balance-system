if ($null -eq (Get-Command platformio -ErrorAction SilentlyContinue)) {
  $platformio = "$HOME\.platformio\penv\Scripts\platformio.exe"

  if (Test-Path -Path $platformio -PathType Leaf) {
    Set-Alias platformio $platformio
  }
  else {
    Write-Host "Platformio can not found!"
    Exit 1
  }
}

platformio run

if ($LASTEXITCODE -eq 0) {
  if (Test-Path .\build -PathType Container) {
    Remove-Item .\build\*
  }
  else {
    New-Item build -ItemType Directory
  }
  
  Get-Item .\.pio\build\rpipicow\firmware.* | Move-Item -Destination .\build\
}
else {
  Write-Host "Platformio exited with $LASTEXITCODE code"
  Exit $LASTEXITCODE
}