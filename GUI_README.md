# DFS Compression Library - GUI Test Application

A graphical user interface for testing the DFS compression library with actual files.

## Features

- **File Selection**: Browse and select input files for compression/decompression
- **Operation Selection**: Choose between compress or decompress operations
- **Real-time Results**: View file sizes, compression ratios, and operation status
- **Multiple Backends**: Uses C library DLL when available, falls back to CLI tool

## Requirements

- Python 3.6 or higher
- tkinter (usually included with Python)
- DFS compression library DLL (optional, will use CLI fallback if not available)

## Usage

### Running the GUI

```bash
python gui_test.py
```

### Building the DLL (for best performance)

```bash
build_dll.bat
```

This will create `build/dfs.dll` which the GUI will automatically use if available.

### Building the CLI Tool (fallback)

The CLI tool is automatically built when you run `compile_and_run.bat` or you can build it manually:

```bash
gcc -I./include dfs_cli.c build/*.o -o build/dfs_cli.exe
```

## GUI Components

1. **Input File**: Select the file you want to compress or decompress
2. **Output File**: Specify where to save the result
3. **Operation**: Choose "Compress" or "Decompress"
4. **Execute Button**: Run the selected operation
5. **Results Panel**: View detailed operation results and statistics

## How It Works

1. The GUI first tries to load the DFS library DLL (`build/dfs.dll`)
2. If the DLL is available, it uses direct function calls for maximum performance
3. If the DLL is not available, it falls back to using the CLI tool (`build/dfs_cli.exe`)
4. If neither is available, it uses a simple Python fallback (for demonstration only)

## Example Workflow

1. Click "Browse..." next to "Input File" and select a file
2. The output file path will be auto-suggested (you can change it)
3. Select "Compress" or "Decompress"
4. Click "Execute"
5. View the results in the results panel

## Troubleshooting

- **"DLL not found"**: Run `build_dll.bat` to create the DLL
- **"CLI tool not found"**: The CLI tool should be built automatically, or compile it manually
- **Operation fails**: Check that input file exists and output directory is writable

