@echo off
echo ========================================
echo DFS Compression Library - Build & Test
echo ========================================
echo.

REM Check for compilers
set COMPILER=
set COMPILER_NAME=

where gcc >nul 2>&1
if %errorlevel% == 0 (
    set COMPILER=gcc
    set COMPILER_NAME=GCC
    goto found_compiler
)

where clang >nul 2>&1
if %errorlevel% == 0 (
    set COMPILER=clang
    set COMPILER_NAME=Clang
    goto found_compiler
)

REM Try to find MSVC
if exist "C:\Program Files\Microsoft Visual Studio" (
    echo Found Visual Studio installation.
    echo Please run this from "Developer Command Prompt for VS" or "x64 Native Tools Command Prompt"
    echo.
    set COMPILER=cl
    set COMPILER_NAME=MSVC
    goto found_compiler
)

echo ERROR: No C compiler found!
echo.
echo Please install one of the following:
echo   1. MinGW-w64 (includes GCC): https://www.mingw-w64.org/downloads/
echo   2. Clang: https://releases.llvm.org/download.html
echo   3. Visual Studio Build Tools: https://visualstudio.microsoft.com/downloads/
echo.
echo Or use CMake if available.
echo.
pause
exit /b 1

:found_compiler
echo Found compiler: %COMPILER_NAME%
echo.

REM Create build directory
if not exist build mkdir build
cd build

REM List of source files needed
set SOURCES=..\src\dfs.c ..\src\dfs_compress.c ..\src\dfs_decompress.c ..\src\dfs_dict.c ..\src\dfs_error.c ..\src\dfs_logger.c ..\src\dfs_utils.c ..\src\dfs_io.c ..\src\dfs_mem.c ..\src\dfs_stream.c ..\src\dfs_block.c ..\src\dfs_cache.c ..\src\dfs_format.c ..\src\dfs_analyze.c ..\src\dfs_entropy.c ..\src\dfs_perf.c ..\src\dfs_plugin.c ..\src\dfs_simd.c ..\src\dfs_stats.c ..\src\dfs_thread.c

if "%COMPILER%"=="cl" (
    echo Compiling with MSVC...
    %COMPILER% /I..\include /c %SOURCES% /Fo: /Fe:dfs.lib
    if %errorlevel% neq 0 (
        echo Compilation failed!
        cd ..
        pause
        exit /b 1
    )
    echo Linking test program...
    %COMPILER% /I..\include ..\test\test_dfs.c dfs.lib /Fe:test_dfs.exe
) else (
    echo Compiling source files...
    %COMPILER% -I../include -c %SOURCES%
    if %errorlevel% neq 0 (
        echo Compilation failed!
        cd ..
        pause
        exit /b 1
    )
    echo Linking test program...
    %COMPILER% -I../include ../test/test_dfs.c *.o -o test_dfs.exe
)

if %errorlevel% neq 0 (
    echo Linking failed!
    cd ..
    pause
    exit /b 1
)

echo.
echo ========================================
echo Build successful! Running test...
echo ========================================
echo.

if exist test_dfs.exe (
    test_dfs.exe
) else if exist test_dfs (
    test_dfs
) else (
    echo ERROR: Test executable not found!
)

cd ..
echo.
echo Done!
pause

