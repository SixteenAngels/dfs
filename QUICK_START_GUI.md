# Quick Start - GUI Testing

## Launch the GUI

Simply double-click `run_gui.bat` or run:
```bash
python gui_test.py
```

## Using the GUI

1. **Select Input File**: Click "Browse..." next to "Input File" and choose a file to compress or decompress
2. **Set Output File**: The output path is auto-suggested, or click "Browse..." to choose a different location
3. **Choose Operation**: Select either "Compress" or "Decompress"
4. **Execute**: Click the "Execute" button
5. **View Results**: Check the results panel for file sizes, compression ratios, and operation status

## Example Test

1. Create a test file (e.g., `test.txt` with some text)
2. Select it as input
3. Choose "Compress" operation
4. Execute
5. The compressed file will be saved (e.g., `test.dfs`)
6. To test decompression, select the `.dfs` file and choose "Decompress"

## Features

- ✅ Real-time progress indication
- ✅ Detailed operation results
- ✅ File size comparison
- ✅ Compression ratio calculation
- ✅ Automatic fallback to CLI tool if DLL unavailable
- ✅ Clean, user-friendly interface

## Troubleshooting

- If the GUI doesn't open, make sure Python 3 is installed
- If operations fail, check that the input file exists and output directory is writable
- The GUI will automatically use the CLI tool (`dfs_cli.exe`) if the DLL is not available

