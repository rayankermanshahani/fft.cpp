# C++ FFT Implementation and Benchmark

This program implements and compares different algorithms for computing the Discrete Fourier Transform (DFT) in C++.

The primary goal is to demonstrate and benchmark the performance difference between:
1.  A naive Discrete Fourier Transform (DFT). Runs in `O(N^2)` time.
2.  A recursive Fast Fourier Transform (FFT) based on the Cooley-Tukey algorithm. Runs in `O(N*log(N))` time
3.  An optimized, iterative, in-place FFT (Cooley-Tukey with bit-reversal). Runs in `O(N*log(N))` time.

The program generates a simple sine wave signal and runs each algorithm on it, measuring and printing the execution time.

## Requirements
*   C++ compiler supporting C++17 (e.g., `g++` or `clang++`)
*   the `<cmath>` library (usually standard)
*   the `make` command

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
./build/fft_benchmark 65536

# example output on an M1 MacBook Air
Naive DFT results (first ten elements):
-7.17762e-13 + 0i
-2.19882e-12 + -3.0922e-12i
-1.52158e-12 + 3.89323e-13i
2.56816e-12 + 4.47398e-11i
7.84172e-12 + 1.36476e-12i
6.65081e-13 + -32768i
7.91327e-12 + 1.51959e-13i
5.89326e-12 + 2.66458e-11i
5.82195e-13 + -2.06121e-12i
1.295e-12 + -6.14442e-12i
Elapsed time (naive DFT): 36.7188 seconds

Recursive FFT results (first ten elements):
7.69747e-14 + 0i
1.23905e-13 + -2.76435e-13i
-5.89271e-14 + 1.20855e-12i
-6.88563e-14 + 1.35021e-12i
-2.79572e-14 + 5.63832e-12i
-1.63625e-11 + -32768i
-4.56136e-14 + -6.94669e-12i
3.88261e-14 + -3.63391e-12i
4.71065e-14 + -2.6267e-12i
-1.09328e-13 + -1.21577e-12i
Elapsed time (recursive FFT): 0.0100835 seconds

Optimized FFT results (first ten elements):
7.69747e-14 + 0i
1.23905e-13 + -2.76435e-13i
-5.89271e-14 + 1.20855e-12i
5.95348e-13 + 2.93014e-12i
-2.79572e-14 + 5.63832e-12i
-1.94154e-11 + -32768i
-4.56136e-14 + -6.94669e-12i
4.2024e-14 + -4.18529e-12i
4.71065e-14 + -2.6267e-12i
-1.09328e-13 + -1.21577e-12i
Elapsed time (optimized FFT): 0.00196396 seconds
```
