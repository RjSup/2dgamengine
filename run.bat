@echo off
cd /d "%~dp0"
cmake --build build
if %errorlevel% equ 0 (
    start cmd /k build\Debug\my_program.exe
) else (
    echo Build failed!
    pause
)
