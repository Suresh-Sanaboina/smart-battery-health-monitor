@echo off
setlocal
gcc -Wall -Wextra -Wpedantic -std=c11 -Isrc tests/test_battery_monitor.c src/battery_monitor.c -o test_battery.exe
if errorlevel 1 (
  echo Test build failed.
  exit /b 1
)
test_battery.exe
exit /b %ERRORLEVEL%
