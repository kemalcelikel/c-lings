#!/usr/bin/env python3
import os
import subprocess
import sys

def main():
    # Find all C files starting with a number
    files = sorted([f for f in os.listdir('.') if f.endswith('.c') and f[0].isdigit()])
    
    if not files:
        print("No exercises found!")
        return

    print(f"Found {len(files)} exercises.")

    for i, f in enumerate(files):
        print(f"[{i+1}/{len(files)}] Checking {f}...")
        exe = f"./{f[:-2]}.out"
        
        # Compile
        # We use -Wall -Wextra -Werror -pedantic to ensure strictness.
        # -lpthread is needed for threading, -lm for math.
        # -std=c11 for atomics and static_assert.
        cmd = ['gcc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-pedantic', f, '-o', exe, '-lpthread', '-lm']
        res = subprocess.run(cmd, capture_output=True, text=True)
        
        if res.returncode != 0:
            print(f"\nCOMPILATION ERROR in {f}:")
            print("---------------------------------------------------")
            print(res.stderr)
            print("---------------------------------------------------")
            print("Please fix the error in the file and try again.")
            sys.exit(1)
            
        # Run
        res = subprocess.run([exe], capture_output=True, text=True)
        
        # Clean up executable immediately
        if os.path.exists(exe):
            os.remove(exe)

        if res.returncode != 0:
            print(f"\nRUNTIME ERROR in {f}:")
            print("---------------------------------------------------")
            print(res.stderr)
            print(res.stdout) 
            print("---------------------------------------------------")
            sys.exit(1)
            
        # Check output against expectations
        output = res.stdout.strip()
        print(f"OUTPUT:\n{output}")
        
        with open(f, 'r') as source_file:
            checks = [line.split('CHECK:', 1)[1].strip() for line in source_file if '// CHECK:' in line]
            
        if checks:
            for check in checks:
                if check not in output:
                    print(f"\nOUTPUT MISMATCH in {f}:")
                    print("---------------------------------------------------")
                    print(f"Expected to find: '{check}'")
                    print(f"But got:\n{output}")
                    print("---------------------------------------------------")
                    sys.exit(1)
            print("PASSED!\n")
        else:
            # Fallback for exercises with no checks yet
            print("PASSED! (No output check)\n")
        
    print("Congratulations! You have completed all the C exercises!")

if __name__ == '__main__':
    main()
