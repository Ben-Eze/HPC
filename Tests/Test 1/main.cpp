#include <iostream>
#include <cmath>
#include <complex>
using namespace std;

#define F77NAME(x) x##_

extern "C" {
    void F77NAME(cgemv) (const char& trans,  const int& m, 
                         const int& n,       const complex<double>& alpha, 
                         const complex<double>* a,    const int& lda, 
                         const complex<double>* x,    const int& incx, 
                         const complex<double>& beta, complex<double>* y, 
                         const int& incy);
    void   F77NAME(caxpy)(const int& n, const complex<double>& alpha,
                         const complex<double>* x, const int& incx, 
                         const complex<double>* y, const int& incy);
    double F77NAME(dnrm2)(const int& n, const double* x, const int& incx);
}

int main() {
    const double PI = std::acos(-1);
    const complex<double> i(0, 1);

    // // 1.
    int N = 16;
    double N_doub = 16;
    complex<double>* W = new complex<double>[N*N];

    // W = k * w ^(jk)
    const complex<double> k = 1 / sqrt(N_doub);
    const complex<double> w = exp(-2.0*i * PI / N_doub);
    
    for (int j{0}; j < N; j++) {
        for (int k{0}; k < N; k++) {
            W[j*N + k] = (k*1.0) * pow(w, j*k*1.0);
        }
    }

    complex<double>* x = new complex<double>[N];

    for (int j{0}; j < N; j++) {
        x[N] = cos(2*PI*j*(1/(N_doub-1)));
    }

    complex<double>* X = new complex<double>[N];

    // X = Wx
    F77NAME(cgemv) ('n', N, N, 1.0, W, N, x, 1, 0, X, 1);

    for (int j{0}; j < N/2; j++) {
        cout << "X[" << j << "] = " << real(X[j]) << " + " << imag(X[j]) << "i" << endl;
    }

    // y = W^4 x
    for (int j{0}; j < 3; j++) {
        F77NAME(cgemv) ('n', N, N, 1.0, W, N, X, 1, 0, X, 1);
    }

    F77NAME(caxpy)(N, -1.0, x, 1, X, 1);

    double* Y = new double[N];

    for (int j{0}; j < N/2; j++) {
        Y[j] = real(X[j]);
    }

    cout << "Epsilon: " << F77NAME(dnrm2)(N, Y, 1) << endl;
}