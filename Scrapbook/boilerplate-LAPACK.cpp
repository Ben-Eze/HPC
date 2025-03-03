#include <iostream>

using namespace std;

#define F77NAME(x) x##_

extern "C" {
    // Lapack
    // y <- solve(Ax = y, x)    ie. y <- A\y
    void F77NAME(dgesv)(const int& n,       // size of A: (n, n)
                        const int& nrhs,    // no. of columns of y
                        const double* A,    // matrix A
                        const int& lda,     // leading dimension of A
                        int* ipiv,          // pivot indices
                        double* y,          // matrix/vector y
                        const int& ldy,     // leading dimension of y
                        int& info           // 0: success, >0: failure, 
                                            // <0: singular
                        );
    // y <- solve(A*x = y, x)    ie. y <- A\y
    // ...where A is in banded form
    void F77NAME(dgbsv)(const int& n,           // size of A: (n, n)
                        const int& KL,          // no. of lower diagonals
                        const int& KU,          // no. of upper diagonals
                        const int& nrhs,        // no. of columns of y
                        const double * A_band,  // matrix A_band
                        const int& ldab,        // leading dimension of A_band
                        int * ipiv,             // pivot indices
                        double * y,             // matrix/vector y
                        const int& ldy,         // leading dimension of y
                        int& info               // 0: success, >0: failure, 
                                                // <0: singular
                        );

    // for... P@A = L@U,    A <- LU
    void F77NAME(dgbtrf) (const int& m,     // no. of rows (height)
                          const int& n,     // no. of columns (width)
                          const int& KL,    // no. of lower diagonals
                          const int& KU,    // no. of upper diagonals
                          double* A_band,   // banded matrix A
                          const int& ldab,  // leading dimension of A_band
                          int* ipiv,        // pivot indices
                          int& info         // 0: success, >0: failure, 
                                            // <0: singular
                        );
    
    // solve Ax = y     PAx = LUx = Py
    void F77NAME(dgbtrs) (const char& trans, 
                          const int& n, 
                          const int& kl,
                          const int &ku, 
                          const int& nrhs, 
                          const double* LU,
                          const int& ldlu, 
                          const int* ipiv, 
                          double* y,
                          const int& ldy, 
                          int& info);                       
}

void printMatrixColumnMajor(double* A, int height, int width) {
    // used for LAPACK
    for (int j{0}; j < height; j++) {
        cout << (j == 0 ? "[[" : "\n [");
        for (int i{0}; i < width; i++) {
            cout << A[i*height + j] << (i == width-1 ? "" : ", ");
        }
        cout << "]";
    }
    cout << "]" << endl;
}

int main() {
    
}