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
    
    // General matrix (Column-major storage)
    double A[] = {1, 4, 7, 2, 5, 8, 3, 6, 9};
    /*
    General Matrix (Column-major storage):
    |1 2 3|
    |4 5 6|
    |7 8 9|
    */
    
    // Symmetric matrix (Lower storage)
    double A_symmetric[] = {1, 4, 7, 5, 8, 9};
    /*
    Symmetric Matrix (Lower part stored):
    |1 4 7|
    |4 5 8|
    |7 8 9|
    */
    
    // Upper triangular matrix (Only upper elements stored)
    double A_upper_tri[] = {1, 2, 3, 4, 5, 6};
    /*
    Upper Triangular Matrix:
    |1 2 3|
    |0 4 5|
    |0 0 6|
    */
    
    // Lower triangular matrix (Only lower elements stored)
    double A_lower_tri[] = {1, 2, 3, 4, 5, 6};
    /*
    Lower Triangular Matrix:
    |1 0 0|
    |2 3 0|
    |4 5 6|
    */
    
    // General banded matrix (Lower bandwidth = 1, Upper bandwidth = 1)
    double A_banded[] = {0, 1, 2, 1, 3, 4, 2, 4, 5};
    /*
    General Banded Matrix (Bandwidth = 1):
    |0 1 2|
    |1 3 4|
    |2 4 5|
    */
    
    // Triangular banded matrix (Upper triangular, bandwidth = 1)
    double A_tri_band[] = {1, 2, 0, 3, 4, 5, 0, 6, 7};
    /*
    Triangular Banded Matrix (Upper, Bandwidth = 1):
    |1 2 0|
    |0 3 4|
    |0 0 5|
    */
    
    return 0;
}
