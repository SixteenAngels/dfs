@echo off
echo ========================================
echo Building DFS Compression Library as DLL
echo ========================================
echo.

REM Check for compiler
set COMPILER=
where gcc >nul 2>&1
if %errorlevel% == 0 (
    set COMPILER=gcc
    goto found_compiler
)

if exist "C:\MinGW\bin\gcc.exe" (
    set PATH=C:\MinGW\bin;%PATH%
    set COMPILER=gcc
    goto found_compiler
)

echo ERROR: No C compiler found!
pause
exit /b 1

:found_compiler
echo Found compiler: %COMPILER%
echo.

REM Create build directory
if not exist build mkdir build
cd build

REM List of source files
set SOURCES=..\src\dfs.c ..\src\dfs_compress.c ..\src\dfs_decompress.c ..\src\dfs_dict.c ..\src\dfs_error.c ..\src\dfs_logger.c ..\src\dfs_utils.c ..\src\dfs_io.c ..\src\dfs_mem.c ..\src\dfs_stream.c ..\src\dfs_block.c ..\src\dfs_cache.c ..\src\dfs_format.c ..\src\dfs_analyze.c ..\src\dfs_entropy.c ..\src\dfs_perf.c ..\src\dfs_plugin.c ..\src\dfs_simd.c ..\src\dfs_stats.c ..\src\dfs_thread.c

echo Compiling source files...
%COMPILER% -I../include -c %SOURCES% -fPIC

if %errorlevel% neq 0 (
    echo Compilation failed!
    cd ..
    pause
    exit /b 1
)

echo.
echo Creating shared library (DLL)...
%COMPILER% -shared -o dfs.dll *.o -Wl,--out-implib,libdfs.a -static-libgcc -static-libstdc++

if %errorlevel% neq 0 (
    echo DLL creation failed!
    cd ..
    pause
    exit /b 1
)

echo.
echo ========================================
echo DLL build successful!
echo ========================================
echo.
echo DLL created: build\dfs.dll
echo.

cd ..
pause

