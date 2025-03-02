#include <iostream>
#define F77NAME(x) x##_

extern "C" {
    // Level 1 BLAS
    // x <- alpha * x                        
    void F77NAME(dscal) (const int& n,          // no. of elements
                         const double& alpha,   // scalar
                         double* x,             // vector x
                         const int& incx        // stride of x
                        );
    
    // y <- alpha * x + y    
    void F77NAME(daxpy) (const int& n,          // no. of elements
                         const double& alpha,   // scalar
                         const double* x,       // vector x
                         const int& incx,       // stride of x
                         double* y,             // vector y
                         const int& incy        // stride of y
                        );

    // x . y
    double F77NAME(ddot) (const int& n,         // no. of elements
                          const double* x,      // vector x
                          const int& incx,      // stride of x
                          const double* y,      // vector y
                          const int& incy       // stride of y
                        );
    
    // l2-norm of x
    double F77NAME(dnrm2) (const int& n,        // no. of elements
                            const double* x,    // vector x
                            const int& incx     // stride of x
                        );    

    // Level 2 BLAS    
    // y <- alpha * A * x + beta * y    
    void F77NAME(dgemv) (const char& trans,     // transpose or not
                         const int& m,          // no. of rows
                         const int& n,          // no. of columns
                         const double& alpha,   // scalar
                         const double* A,       // matrix A
                         const int& lda,        // leading dimension of A
                         const double* x,       // vector x
                         const int& incx,       // stride of x
                         const double& beta,    // scalar
                         double* y,             // vector y
                         const int& incy        // stride of y
                        );

    void F77NAME(dgemm) (const char& transa,    // transpose A or not
                         const char& transb,    // transpose B or not
                         const int& m,          // no. of rows of C
                         const int& n,          // no. of columns of C
                         const int& k,          // no. of columns of A and rows 
                                                // of B
                         const double& alpha,   // scalar
                         const double* A,       // matrix A
                         const int& lda,        // leading dimension of A
                         const double* B,       // matrix B
                         const int& ldb,        // leading dimension of B
                         const double& beta,    // scalar
                         double* C,             // matrix C
                         const int& ldc         // leading dimension of C
                        );
}