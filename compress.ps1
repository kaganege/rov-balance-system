if (Test-Path .\rov-balance-system.zip -PathType Leaf) {
  Remove-Item .\rov-balance-system.zip
}

if (Get-Command "7z.exe" -ErrorAction SilentlyContinue) {
  7z.exe a -tzip rov-balance-system.zip .\* -r -x@".gitignore"
}
else {
  Write-Host "You must download 7zip for compress!"
  Read-Host -Prompt "Press Enter to continue..."
}