@echo off
git init
git submodule add "https://github.com/Heroes-Hacking-Central/Heroes.SDK"
git submodule update --init --recursive
echo Done!
pause