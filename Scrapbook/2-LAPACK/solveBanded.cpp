#include <iostream>

#define F77NAME(x) x##_

extern "C" {
    void F77NAME(dgesv)(const int& n, const int& nrhs, 
                        const double * A, const int& lda, 
                        int * ipiv, double * B,
                        const int& ldb, int& info);
    void F77NAME(dgbsv)(const int& n, const int& KL, const int& KU, 
                        const int& nrhs, const double * AB, const int& lda, 
                        int * ipiv, double * B, const int& ldb, int& info);    
}

int main() {
    /* Solve the system Ax = b where...
      A = [1, 2
           3, 4]
      b = [1, 2].T
    */
    double* A = new double[4] {1, 3, 2, 4};     // note: column-major order
    double* b = new double[2] {1, 2};
    double* x = new double[2];
    int* ipiv = new int[2];
    int n = 2;
    int info;

    F77NAME(dgesv)(n, 1, A, n, ipiv, b, n, info);
    
    std::cout << "Solution: " << b[0] << ", " << b[1] << std::endl;

    // Use banded matrix
    int k = 5, m = 6;
    int KL = 2, KU = 1;
    int nb = 1 + 2*KL + KU;
    double X = 0;   // Placeholder for unused elements
    double* A_banded = new double[nb * m] {X, X, X,  1,  2,  3, 
                                           X, X, 4,  5,  6,  7, 
                                           X, X, 8,  9,  10, 11, 
                                           X, X, 12, 13, 14, X, 
                                           X, X, 15, 16, X,  X};
    double* b_banded = new double[k] {1, 2, 3, 4, 5};
    double* x_banded = new double[k];
    int* ipiv_banded = new int[k];
    int info_banded;
    F77NAME(dgbsv)(k, KL, KU, 1, A_banded, nb, ipiv_banded, b_banded, k, info_banded);
    
    for (int i{0}; i < k; i++) {
        std::cout << b_banded[i] << std::endl;
    }
}