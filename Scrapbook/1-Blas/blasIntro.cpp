#include <vector>
#include <stdexcept>
#include <iostream>
#include <complex>
#define F77NAME(x) x##_

extern "C" {
    double F77NAME(ddot) (const int& n, 
                          const double* x, const int& incx, 
                          const double* y, const int& incy);
    void F77NAME(dgemv) (const char& trans,  const int& m, 
                         const int& n,       const double& alpha, 
                         const double* a,    const int& lda, 
                         const double* x,    const int& incx, 
                         const double& beta, double* y, 
                         const int& incy);
    void F77NAME(zscal) (const int& n, const std::complex<double>& alpha,
                         std::complex<double>* x, const int& incx);
}


double dotProduct(const std::vector<double>& a, const std::vector<double>& b);
std::vector<double> matrixVectorProduct(const std::vector<std::vector<double>>& A, const std::vector<double>& x);

using namespace std;

int main() {
    // Declare variables
    int n = 5;
    std::vector<double> a = {1, 2, 3, 4, 5};
    std::vector<double> b = {1, 2, 3, 4, 5};
    double adotb = dotProduct(a, b);
    std::cout << "a . b = " << adotb << std::endl;

    std::vector<std::vector<double>> A = {{1, 2, 3}, {4, 5, 6}};
    std::vector<double> x = {1, 1, 2};
    auto y = matrixVectorProduct(A, x);

    std::complex<double>* z = new std::complex<double> [2];
    std::complex<double> alpha = 1i;

    z[0] = 1.0 + 2.0i;
    z[1] = 3.0 + 4.0i;

    F77NAME(zscal)(2, alpha, z, 1);

    std::cout << "z[0] = " << z[0].real() << " + " << z[0].imag() << "i" << std::endl;
    std::cout << "z[1] = " << z[1].real() << " + " << z[1].imag() << "i" << std::endl;

    return 0;
}

double dotProduct(const std::vector<double>& a, const std::vector<double>& b) {
    int n = a.size();
    if (b.size() != n) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    return F77NAME(ddot)(n, a.data(), 1, b.data(), 1);
}

std::vector<double> matrixVectorProduct(const std::vector<std::vector<double>>& A, const std::vector<double>& x) {
    // y = A@x
    int m = A.size();
    int n = A[0].size();
    if (x.size() != n) {
        throw std::invalid_argument("Matrix and vector must have compatible sizes");
    }
    std::vector<double> y(m);

    double* Amat = new double[m*n];
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            Amat[i*m + j] = A[j][i];
        }
    }

    F77NAME(dgemv)('N', m, n, 1.0, Amat, m, x.data(), 1, 0, y.data(), 1);

    return y;
}