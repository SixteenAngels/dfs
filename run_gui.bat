@echo off
echo Starting DFS Compression GUI...
echo.
python gui_test.py
if %errorlevel% neq 0 (
    echo.
    echo Error: Python or tkinter not found!
    echo Please make sure Python 3 is installed and tkinter is available.
    pause
)

