#include <iostream>

#define F77NAME(x) x##_

extern "C" {
    void F77NAME(dgemv)(const char& trans, const int& m, const int& n,
                        const double& alpha, const double* A, const int& lda,
                        const double* x, const int& incx,
                        const double& beta, double* y, const int& incy);
    void F77NAME(dsymv)(const char& uplo, const int& n, const double& alpha,
                        const double* A, const int& lda,
                        const double* x, const int& incx,
                        const double& beta, double* y, const int& incy);
    void F77NAME(dtbmv)(const char& uplo, const char& trans, const char& diag,
                        const int& n, const int& k, const double* A, const int& lda,
                        double* x, const int& incx);
}

int main() {
    const int n = 3;
    double A[] = {1, 4, 7, 2, 5, 8, 3, 6, 9}; // Column-major storage
    double x[] = {1.0, 2.0, 3.0};
    double y[] = {0.0, 0.0, 0.0};
    
    // General matrix-vector multiplication (y = A * x)
    /*
    Matrix A:
    |1 2 3|
    |4 5 6|
    |7 8 9|
    */
    F77NAME(dgemv)('N', n, n, 1.0, A, n, x, 1, 0.0, y, 1);
    
    std::cout << "Result (General Matrix):\n";
    for (int i = 0; i < n; ++i) {
        std::cout << y[i] << " ";
    }
    std::cout << std::endl;
    
    // Symmetric matrix-vector multiplication (only storing lower part)
    double A_symmetric[] = {1, 4, 5, 7, 8, 9};
    /*
    Symmetric Matrix (Lower part stored):
    |1 4 7|
    |4 5 8|
    |7 8 9|
    */
    F77NAME(dsymv)('L', n, 1.0, A_symmetric, n, x, 1, 0.0, y, 1);
    
    std::cout << "Result (Symmetric Matrix):\n";
    for (int i = 0; i < n; ++i) {
        std::cout << y[i] << " ";
    }
    std::cout << std::endl;
    
    // Triangular banded matrix (upper triangular, bandwidth = 1)
    double A_tri_band[] = {1, 2, 0, 3, 4, 5, 0, 6, 7};
    /*
    Triangular Banded Matrix (Upper):
    |1 2 0|
    |0 3 4|
    |0 0 5|
    */
    F77NAME(dtbmv)('U', 'N', 'N', n, 1, A_tri_band, n, x, 1);
    
    std::cout << "Result (Triangular Banded Matrix):\n";
    for (int i = 0; i < n; ++i) {
        std::cout << x[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
