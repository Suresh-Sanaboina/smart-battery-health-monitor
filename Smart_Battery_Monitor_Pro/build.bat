@echo off
setlocal
gcc -Wall -Wextra -Wpedantic -std=c11 -Isrc src/main.c src/battery_monitor.c -o battery.exe
if errorlevel 1 (
  echo Build failed.
  exit /b 1
)
echo Build successful: battery.exe
