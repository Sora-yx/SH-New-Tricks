# Set Working Directory
Split-Path $MyInvocation.MyCommand.Path | Push-Location
[Environment]::CurrentDirectory = $PWD

Remove-Item "$env:RELOADEDIIMODS/New_Tricks/*" -Force -Recurse
dotnet publish "./New_Tricks.csproj" -c Release -o "$env:RELOADEDIIMODS/New_Tricks" /p:OutputPath="./bin/Release" /p:ReloadedILLink="true"

# Restore Working Directory
Pop-Location