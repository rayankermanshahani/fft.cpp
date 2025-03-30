#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

using Complex = std::complex<double>;
const double PI = M_PI;

// helper function to check if integer is power of two
bool is_power_of_two(int n) { return (n > 0) && ((n & (n - 1)) == 0); }

// helper function to reverse an integer's bits
// eg., reverse_bits(1,3) -> reverse_bits(001, 3) -> 100 -> 4
// eg., reverse_bits(3,3) -> reverse_bits(110, 3) -> 011 -> 6
unsigned int reverse_bits(unsigned int index, int num_bits) {
  unsigned int reversed_index = 0;
  for (int i = 0; i < num_bits; ++i) {
    if ((index >> i) & 1) { // check if the i-th bit is 1
      reversed_index |=
          (1U << (num_bits - 1 - i)); // set the corresponding reversed
    }
  }
  return reversed_index;
}

// naive dft implementation with O(N^2) complexity
std::vector<Complex> naive_dft(const std::vector<Complex>& x) {
  size_t N = x.size();
  std::vector<Complex> X(N, Complex(0, 0));

  // for each output element (frequency bin)
  for (size_t k = 0; k < N; k++) {
    // compute kth frequency component
    for (size_t n = 0; n < N; n++) {
      // calculate twiddle factor: W_N^k = e^(-i2pi*k*n/N)
      double theta = -2.0 * PI * k * n / N;
      Complex twiddle_factor = std::polar(1.0, theta);

      // accumulate sum for this frequency component
      X[k] += x[n] * twiddle_factor;
    }
  }

  return X;
}

// recursive fft (not optimized)
std::vector<Complex> recursive_fft(const std::vector<Complex>& x) {
  size_t N = x.size();

  // base case
  if (N <= 1) {
    return x;
  }

  // split into even and odd indexed elements
  std::vector<Complex> even(N / 2), odd(N / 2);
  for (size_t i = 0; 2 * i < N; i++) {
    even[i] = x[2 * i];
    odd[i] = x[2 * i + 1];
  }

  // recursive fft on each half
  std::vector<Complex> x_even = recursive_fft(even);
  std::vector<Complex> x_odd = recursive_fft(odd);

  // combine step
  std::vector<Complex> result(N);
  for (size_t k = 0; k < N / 2; k++) {
    // twiddle factor (rotation in complex plane)
    double theta = -2.0 * PI * k / N;
    Complex twiddle = std::polar(1.0, theta) * x_odd[k];

    result[k] = x_even[k] + twiddle;
    result[k + N / 2] = x_even[k] - twiddle;
  }

  return result;
}

// optimized fft (iterative in-place radix-2 cooley-tukey fft)
void optimized_fft(std::vector<Complex>& x) {
  size_t N = x.size();
  if (N <= 1)
    return;

  // make sure signal length is power of two
  assert(is_power_of_two(N) && "FFT size must be power of 2");
  int num_bits = 0;
  while ((1 << num_bits) < N) {
    num_bits++;
  }

  // bit-reversal permutation
  for (size_t i = 0; i < N; ++i) {
    unsigned int rev_i = reverse_bits(i, num_bits);
    // only swap if i is less than its reversal to avoid double swaps
    if (i < rev_i) {
      std::swap(x[i], x[rev_i]);
    }
  }

  // iterative butterfly stages
  // outer loop iterates through stages (block sizes: 2, 4, 8, ..., N)
  for (size_t len = 2; len <= N;
       len <<= 1) { // len is current DFT size (block size)
    size_t half_len = len / 2;

    // principle twiddle factor for this stage: W_len^1 = exp(-2*ip*i/len)
    Complex w_len = std::polar(1.0, -2.0 * PI / len);

    // middle loop iterates through blocks of size `len`
    for (size_t i = 0; i < N; i += len) {
      Complex w = Complex(1.0, 0.0); // start with W_len^0 = 1

      // inner loop performs butterflies within current block
      for (size_t j = 0; j < half_len; ++j) {
        int idx1 = i + j;
        int idx2 = i + j + half_len;

        // get two elements
        Complex u = x[idx1];
        Complex v_twiddled = w * x[idx2];

        // in-place butterfly calculation
        x[idx1] = u + v_twiddled;
        x[idx2] = u - v_twiddled;

        // update twiddle factor for next iteration
        // (w_len^(k+1) = w_len^k * w_len^1)
        w *= w_len;
      }
    }
  }
}

int main(int argc, char** argv) {
  // parse commandline argument for signal length
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0]
              << " <signal_length (must be a power of 2)>" << std::endl;
    return 1;
  }

  // create dummy signal vector (length has to be power of two for fft)
  size_t N;
  try {
    N = std::stoi(argv[1]);
  } catch (const std::exception& e) {
    std::cerr << "Error: signal length must be an integer." << std::endl;
    return 1;
  }

  if (!is_power_of_two(N)) {
    std::cerr << "Error: signal length must be a power of 2." << std::endl;
    return 1;
  }

  std::vector<Complex> signal;
  signal.reserve(N);
  const double freq = 5.0;
  for (size_t n = 0; n < static_cast<size_t>(N); n++) {
    double value = sin(2.0 * PI * freq * n / N);
    signal.push_back(Complex(value, 0.0));
  }

  // time the naive dft
  auto start_dft = std::chrono::steady_clock::now();
  std::vector<Complex> dft_result = naive_dft(signal);
  auto end_dft = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_dft = end_dft - start_dft;

  // time the recursive fft
  auto start_fft = std::chrono::steady_clock::now();
  std::vector<Complex> fft_result = recursive_fft(signal);
  auto end_fft = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_fft = end_fft - start_fft;

  // time the optimized fft
  auto start_offt = std::chrono::steady_clock::now();
  optimized_fft(signal);
  auto end_offt = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_offt = end_offt - start_offt;

  // output for dft
  std::cout << "Naive DFT results (first ten elements):" << std::endl;
  for (size_t i = 0; i < 10 && i < dft_result.size(); ++i) {
    std::cout << dft_result[i].real() << " + " << dft_result[i].imag() << "i"
              << std::endl;
  }
  std::cout << "Elapsed time (naive DFT): " << elapsed_dft.count() << " seconds"
            << std::endl
            << std::endl;

  // output for recursive fft
  std::cout << "Recursive FFT results (first ten elements):" << std::endl;
  for (size_t i = 0; i < 10 && i < fft_result.size(); ++i) {
    std::cout << fft_result[i].real() << " + " << fft_result[i].imag() << "i"
              << std::endl;
  }
  std::cout << "Elapsed time (recursive FFT): " << elapsed_fft.count()
            << " seconds" << std::endl
            << std::endl;

  // output for optimized fft
  std::cout << "Optimized FFT results (first ten elements):" << std::endl;
  for (size_t i = 0; i < 10 && i < signal.size(); ++i) {
    std::cout << signal[i].real() << " + " << signal[i].imag() << "i"
              << std::endl;
  }
  std::cout << "Elapsed time (optimized FFT): " << elapsed_offt.count()
            << " seconds" << std::endl
            << std::endl;

  return 0;
}
