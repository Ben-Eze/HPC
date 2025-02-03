#define uint unsigned int
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
    void F77NAME(dgemv) (
        const char& trans,  const int& m, 
        const int& n,       const double& alpha, 
        const double* a,    const int& lda, 
        const double* x,    const int& incx, 
        const double& beta, double* y, 
        const int& incy);
    double F77NAME(ddot) (
        const int& n, 
        const double* x, const int& incx, 
        const double* y, const int& incy);
    double F77NAME(dcopy) (
        const int& n, 
        const double* x, const int& incx, 
        const double* y, const int& incy);
}

void buildM(double* M, const uint n);
void buildX(double* x, const uint n);
void squareM(double* M, double* A, const uint n);
void multAx(double* A, double* x, double* b, const uint n);
double dotProduct(double* a, double* b, const uint n);
void printSquare(double* M, const uint n);
void printVector(double* x, const uint n);
void conjGradSolve(double* b, double* A, double* xsolution, const uint n);