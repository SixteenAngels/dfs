@echo off
echo Building DFS Compression Library...
echo.

REM Create build directory
if not exist build mkdir build
cd build

REM Configure with CMake
echo Configuring with CMake...
cmake .. 2>&1
if %errorlevel% neq 0 (
    echo CMake configuration failed. Trying to compile manually...
    cd ..
    goto manual_build
)

REM Build the project
echo Building project...
cmake --build . 2>&1
if %errorlevel% neq 0 (
    echo CMake build failed. Trying to compile manually...
    cd ..
    goto manual_build
)

REM Run test if available
if exist test_dfs.exe (
    echo.
    echo Running test...
    test_dfs.exe
)

cd ..
goto end

:manual_build
echo.
echo Attempting manual compilation...
echo Note: This requires a C compiler (gcc, clang, or cl) to be in PATH
echo.
goto end

:end
echo.
echo Build process completed.
pause

