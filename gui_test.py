#!/usr/bin/env python3
"""
DFS Compression Library - GUI Test Application
A graphical interface for testing DFS compression with actual files
"""

import tkinter as tk
from tkinter import ttk, filedialog, messagebox, scrolledtext
import os
import sys
import ctypes
from pathlib import Path
import threading

# Try to load the DFS library
try:
    # Try to find the compiled library
    base_dir = os.path.dirname(os.path.abspath(__file__))
    lib_paths = [
        os.path.join(base_dir, "build", "dfs.dll"),
        os.path.join(base_dir, "build", "libdfs.dll"),
        os.path.join(base_dir, "dfs.dll"),
        os.path.join(base_dir, "libdfs.dll"),
    ]
    
    dfs_lib = None
    for lib_path in lib_paths:
        if os.path.exists(lib_path):
            try:
                # On Windows, we need to load dependencies first
                dfs_lib = ctypes.CDLL(lib_path)
                break
            except Exception as e:
                print(f"Failed to load {lib_path}: {e}")
                continue
    
    if dfs_lib is None:
        # Try loading from system path
        try:
            dfs_lib = ctypes.CDLL("dfs.dll")
        except:
            try:
                dfs_lib = ctypes.CDLL("libdfs.dll")
            except:
                dfs_lib = None
                
except Exception as e:
    dfs_lib = None
    print(f"Warning: Could not load DFS library: {e}")

class DFSGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("DFS Compression Library - File Tester")
        self.root.geometry("800x700")
        self.root.resizable(True, True)
        
        # Variables
        self.input_file = tk.StringVar()
        self.output_file = tk.StringVar()
        self.operation = tk.StringVar(value="compress")
        self.use_library = tk.BooleanVar(value=(dfs_lib is not None))
        
        self.setup_ui()
        self.setup_library()
        
    def setup_library(self):
        """Setup C library function signatures if available"""
        self.library_available = False
        if dfs_lib is None:
            return
            
        try:
            # Define dfs_status_t enum
            class DFSStatus:
                DFS_OK = 0
                DFS_ERR_INVALID_INPUT = 1
                DFS_ERR_BUFFER_TOO_SMALL = 2
                DFS_ERR_COMPRESSION_FAILED = 3
                DFS_ERR_DECOMPRESSION_FAILED = 4
                DFS_ERR_FILE_IO = 5
                DFS_ERR_MEM_ALLOC = 6
                DFS_ERR_THREAD_FAIL = 7
                DFS_ERR_INVALID_FORMAT = 8
                DFS_ERR_UNKNOWN = 9
            
            self.DFSStatus = DFSStatus
            
            # Setup dfs_compress_file
            dfs_lib.dfs_compress_file.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
            dfs_lib.dfs_compress_file.restype = ctypes.c_int
            
            # Setup dfs_decompress_file
            dfs_lib.dfs_decompress_file.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
            dfs_lib.dfs_decompress_file.restype = ctypes.c_int
            
            self.dfs_lib = dfs_lib
            self.library_available = True
        except Exception as e:
            self.library_available = False
    def setup_ui(self):
        """Create the user interface"""
        # Main frame
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        # Configure grid weights
        self.root.columnconfigure(0, weight=1)
        self.root.rowconfigure(0, weight=1)
        main_frame.columnconfigure(1, weight=1)
        
        # Title
        title_label = ttk.Label(main_frame, text="DFS Compression Library", 
                               font=("Arial", 16, "bold"))
        title_label.grid(row=0, column=0, columnspan=3, pady=(0, 20))
        
        # Input file selection
        ttk.Label(main_frame, text="Input File:").grid(row=1, column=0, sticky=tk.W, pady=5)
        ttk.Entry(main_frame, textvariable=self.input_file, width=50).grid(
            row=1, column=1, sticky=(tk.W, tk.E), padx=5, pady=5)
        ttk.Button(main_frame, text="Browse...", 
                  command=self.browse_input_file).grid(row=1, column=2, pady=5)
        
        # Output file selection
        ttk.Label(main_frame, text="Output File:").grid(row=2, column=0, sticky=tk.W, pady=5)
        ttk.Entry(main_frame, textvariable=self.output_file, width=50).grid(
            row=2, column=1, sticky=(tk.W, tk.E), padx=5, pady=5)
        ttk.Button(main_frame, text="Browse...", 
                  command=self.browse_output_file).grid(row=2, column=2, pady=5)
        
        # Operation selection
        ttk.Label(main_frame, text="Operation:").grid(row=3, column=0, sticky=tk.W, pady=5)
        op_frame = ttk.Frame(main_frame)
        op_frame.grid(row=3, column=1, sticky=tk.W, padx=5, pady=5)
        ttk.Radiobutton(op_frame, text="Compress", variable=self.operation, 
                      value="compress").pack(side=tk.LEFT, padx=10)
        ttk.Radiobutton(op_frame, text="Decompress", variable=self.operation, 
                      value="decompress").pack(side=tk.LEFT, padx=10)
        
        # Use library checkbox (if available)
        if dfs_lib is not None:
            ttk.Checkbutton(main_frame, text="Use C Library DLL (faster)", 
                           variable=self.use_library).grid(row=4, column=1, sticky=tk.W, padx=5, pady=5)
        else:
            ttk.Label(main_frame, text="Note: DLL not found, will use CLI fallback", 
                     foreground="gray").grid(row=4, column=1, sticky=tk.W, padx=5, pady=5)
        
        # Execute button
        execute_btn = ttk.Button(main_frame, text="Execute", 
                               command=self.execute_operation, width=20)
        execute_btn.grid(row=5, column=0, columnspan=3, pady=20)
        
        # Progress bar
        self.progress = ttk.Progressbar(main_frame, mode='indeterminate')
        self.progress.grid(row=6, column=0, columnspan=3, sticky=(tk.W, tk.E), pady=5)
        
        # Status label
        self.status_label = ttk.Label(main_frame, text="Ready", 
                                      font=("Arial", 10))
        self.status_label.grid(row=7, column=0, columnspan=3, pady=5)
        
        # Results text area
        ttk.Label(main_frame, text="Results:", font=("Arial", 10, "bold")).grid(
            row=8, column=0, columnspan=3, sticky=tk.W, pady=(10, 5))
        
        self.results_text = scrolledtext.ScrolledText(main_frame, height=15, width=80)
        self.results_text.grid(row=9, column=0, columnspan=3, sticky=(tk.W, tk.E, tk.N, tk.S), pady=5)
        
        main_frame.rowconfigure(9, weight=1)
        
    def browse_input_file(self):
        """Browse for input file"""
        filename = filedialog.askopenfilename(
            title="Select Input File",
            filetypes=[("All Files", "*.*")]
        )
        if filename:
            self.input_file.set(filename)
            # Auto-set output file name
            if not self.output_file.get():
                base = os.path.splitext(filename)[0]
                if self.operation.get() == "compress":
                    self.output_file.set(base + ".dfs")
                else:
                    self.output_file.set(base + "_decompressed" + os.path.splitext(filename)[1])
    
    def browse_output_file(self):
        """Browse for output file location"""
        op = "compressed" if self.operation.get() == "compress" else "decompressed"
        filename = filedialog.asksaveasfilename(
            title=f"Save {op.capitalize()} File As",
            defaultextension=".dfs" if self.operation.get() == "compress" else "",
            filetypes=[("All Files", "*.*")]
        )
        if filename:
            self.output_file.set(filename)
    
    def log_message(self, message):
        """Add message to results text area"""
        self.results_text.insert(tk.END, message + "\n")
        self.results_text.see(tk.END)
        self.root.update_idletasks()
    
    def update_status(self, message):
        """Update status label"""
        self.status_label.config(text=message)
        self.root.update_idletasks()
    
    def execute_operation(self):
        """Execute compression or decompression"""
        input_path = self.input_file.get()
        output_path = self.output_file.get()
        operation = self.operation.get()
        
        # Validate inputs
        if not input_path or not os.path.exists(input_path):
            messagebox.showerror("Error", "Please select a valid input file!")
            return
        
        if not output_path:
            messagebox.showerror("Error", "Please specify an output file!")
            return
        
        # Clear results
        self.results_text.delete(1.0, tk.END)
        
        # Run in separate thread to avoid freezing UI
        thread = threading.Thread(target=self._execute_operation_thread, 
                                 args=(input_path, output_path, operation))
        thread.daemon = True
        thread.start()
    
    def _execute_operation_thread(self, input_path, output_path, operation):
        """Execute operation in background thread"""
        try:
            self.progress.start()
            self.update_status(f"{operation.capitalize()}ing...")
            
            self.log_message(f"=== DFS {operation.capitalize()}ion ===")
            self.log_message(f"Input file: {input_path}")
            self.log_message(f"Output file: {output_path}")
            self.log_message("")
            
            # Get file size
            input_size = os.path.getsize(input_path)
            self.log_message(f"Input file size: {input_size:,} bytes ({input_size / 1024:.2f} KB)")
            
            # Execute operation
            if self.use_library.get() and self.library_available:
                success = self._execute_with_library(input_path, output_path, operation)
            else:
                success = self._execute_with_python(input_path, output_path, operation)
            
            if success:
                # Get output file size
                if os.path.exists(output_path):
                    output_size = os.path.getsize(output_path)
                    self.log_message(f"Output file size: {output_size:,} bytes ({output_size / 1024:.2f} KB)")
                    
                    if operation == "compress":
                        ratio = (output_size / input_size) * 100
                        self.log_message(f"Compression ratio: {ratio:.2f}%")
                        if ratio < 100:
                            self.log_message(f"Space saved: {input_size - output_size:,} bytes ({(1 - ratio/100) * 100:.2f}%)")
                    else:
                        self.log_message(f"Decompression successful!")
                    
                    self.log_message("")
                    self.log_message("✓ Operation completed successfully!")
                    self.update_status("Success!")
                    messagebox.showinfo("Success", 
                                      f"File {operation}ed successfully!\n\n"
                                      f"Input: {input_size:,} bytes\n"
                                      f"Output: {output_size:,} bytes")
                else:
                    self.log_message("✗ Error: Output file was not created!")
                    self.update_status("Error!")
                    messagebox.showerror("Error", "Output file was not created!")
            else:
                self.log_message("✗ Operation failed!")
                self.update_status("Failed!")
                messagebox.showerror("Error", f"{operation.capitalize()}ion failed!")
                
        except Exception as e:
            self.log_message(f"✗ Error: {str(e)}")
            self.update_status("Error!")
            messagebox.showerror("Error", f"An error occurred: {str(e)}")
        finally:
            self.progress.stop()
    
    def _execute_with_library(self, input_path, output_path, operation):
        """Execute using C library via ctypes"""
        try:
            input_bytes = input_path.encode('utf-8')
            output_bytes = output_path.encode('utf-8')
            
            if operation == "compress":
                result = self.dfs_lib.dfs_compress_file(
                    ctypes.c_char_p(input_bytes),
                    ctypes.c_char_p(output_bytes)
                )
            else:
                result = self.dfs_lib.dfs_decompress_file(
                    ctypes.c_char_p(input_bytes),
                    ctypes.c_char_p(output_bytes)
                )
            
            if result == self.DFSStatus.DFS_OK:
                self.log_message("Operation completed using C library")
                return True
            else:
                error_msg = {
                    self.DFSStatus.DFS_ERR_INVALID_INPUT: "Invalid input",
                    self.DFSStatus.DFS_ERR_FILE_IO: "File I/O error",
                    self.DFSStatus.DFS_ERR_COMPRESSION_FAILED: "Compression failed",
                    self.DFSStatus.DFS_ERR_DECOMPRESSION_FAILED: "Decompression failed",
                    self.DFSStatus.DFS_ERR_INVALID_FORMAT: "Invalid file format",
                }.get(result, f"Unknown error (code: {result})")
                self.log_message(f"Library returned error: {error_msg}")
                return False
        except Exception as e:
            self.log_message(f"Library call failed: {str(e)}")
            return False
    
    def _execute_with_python(self, input_path, output_path, operation):
        """Execute using Python fallback via CLI tool or subprocess"""
        try:
            import subprocess
            
            # Try to use CLI tool if available
            base_dir = os.path.dirname(os.path.abspath(__file__))
            cli_exe = os.path.join(base_dir, "build", "dfs_cli.exe")
            
            if os.path.exists(cli_exe):
                self.log_message("Using CLI tool as fallback...")
                cmd = [cli_exe, operation, input_path, output_path]
                result = subprocess.run(cmd, capture_output=True, text=True)
                
                if result.returncode == 0:
                    self.log_message(result.stdout)
                    return True
                else:
                    self.log_message(f"CLI tool error: {result.stderr}")
                    return False
            else:
                # Fallback: simple file copy (placeholder)
                self.log_message("Note: Using Python fallback (file copy)")
                self.log_message("For full functionality, please build the C library as a DLL")
                
                # Read input file
                with open(input_path, 'rb') as f:
                    data = f.read()
                
                # For demonstration, just copy the file
                # In a real implementation, you'd call the compression functions
                with open(output_path, 'wb') as f:
                    if operation == "compress":
                        # Simple placeholder - in reality would compress
                        f.write(b"DFS1" + data)  # Add a simple header
                    else:
                        # Simple placeholder - in reality would decompress
                        if data.startswith(b"DFS1"):
                            f.write(data[4:])  # Remove header
                        else:
                            f.write(data)
                
                return True
                
        except Exception as e:
            self.log_message(f"Python execution failed: {str(e)}")
            return False

def main():
    root = tk.Tk()
    app = DFSGUI(root)
    root.mainloop()

if __name__ == "__main__":
    main()

