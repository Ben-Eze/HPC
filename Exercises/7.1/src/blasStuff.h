#define F77NAME(x) x##_

extern "C" {
    void F77NAME(dgemm) (
        const char& transa, const char& transb, 
        const int& m, const int& n, 
        const int& k, const double& alpha, 
        const double* A, const int& lda, 
        const double* B, const int& ldb, 
        const double& beta, double* C, 
        const int& ldc);
}

void blasTest();