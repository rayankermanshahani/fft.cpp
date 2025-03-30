# C++ FFT Implementation and Benchmark

This program implements and compares different algorithms for computing the Discrete Fourier Transform (DFT) in C++.

The primary goal is to demonstrate and benchmark the performance difference between:
1.  A naive O(N^2) Discrete Fourier Transform (DFT).
2.  A recursive O(N log N) Fast Fourier Transform (FFT) based on the Cooley-Tukey algorithm.
3.  An optimized, iterative, in-place O(N log N) FFT (Cooley-Tukey with bit-reversal).

The program generates a simple sine wave signal and runs each algorithm on it, measuring and printing the execution time.

## Requirements
*   C++ compiler supporting C++17 (e.g., `g++` or `clang++`).
*   The `<cmath>` library (usually standard).
*   `make` commandb

## Building

Run `make` to build the executable according to the included `Makefile`. Run `make clean` if you want to delete the build subdirectory and its contents that were created by the `make` command.

## Running

Execute the compiled program, providing the desired signal length as a command-line argument.

**Important:** The signal length *must* be a power of 2 (e.g., 1024, 4096, 8192, ...)

```bash
./build/fft_benchmark <signal_length>
```

Example: 
```bash
./build/fft_benchmark 16384

# example output on an M1 MacBook Air
Naive DFT results (first ten elements):
-4.06232e-13 + 0i
-3.81655e-13 + -7.24061e-12i
-9.61906e-14 + -4.98376e-13i
-6.14999e-13 + 3.66741e-12i
-1.1841e-12 + -1.53017e-14i
-7.03643e-14 + -8192i
-1.12276e-12 + -2.33766e-13i
6.30431e-13 + 4.95662e-12i
-1.15524e-12 + -2.23814e-13i
4.17961e-13 + -1.86969e-12i
Elapsed time (naive DFT): 2.28288 seconds

Recursive FFT results (first ten elements):
2.31404e-14 + 0i
4.33591e-14 + -6.40782e-14i
-1.36524e-14 + 3.00044e-13i
-1.24788e-14 + 3.23729e-13i
-1.03258e-14 + 1.40952e-12i
-4.11009e-12 + -8192i
-1.1063e-14 + -1.73521e-12i
8.17106e-15 + -9.0594e-13i
1.01561e-14 + -6.54224e-13i
-2.81532e-14 + -3.11273e-13i
Elapsed time (recursive FFT): 0.00251333 seconds

Optimized FFT results (first ten elements):
2.31404e-14 + 0i
4.33591e-14 + -6.40782e-14i
-1.36524e-14 + 3.00044e-13i
1.44709e-13 + 7.12383e-13i
-1.03258e-14 + 1.40952e-12i
-4.83151e-12 + -8192i
-1.1063e-14 + -1.73521e-12i
6.45946e-15 + -1.04824e-12i
1.01561e-14 + -6.54224e-13i
-2.81532e-14 + -3.11273e-13i
Elapsed time (optimized FFT): 0.0005345 seconds
```
