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
    void F77NAME(dsyev)(const char& v,      // 'N': eigvalues, 'V': eigvectors
                        const char& ul,     // 'U': upper, 'L': lower
                        const int& n,       // size of A: (n, n)
                        double* A_sym,      // matrix A_sym
                        const int& ldas,    // leading dimension of A_sym
                        double* w,          // eigenvalues
                        double* work,       // workspace
                        const int& lwork,   // size of workspace
                        int* info           // 0: success, >0: failure, 
                                            // <0: singular
                        );
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
    const int n = 3, 
              lda = n, 
              ldv = n;
    int info = 0, 
        lwork;
    double wkopt;

    double X = 0;   // Placeholder
    double* A_sym = new double[n*n] {4, -2,  2, 
                                     X,  5, -3,
                                     X,  X,  6};
    double* w = new double[n];
    double* work;    

    // Calculate the optimal size of `work`
    F77NAME(dsyev)('V', 'L', n, A_sym, lda, w, &wkopt, -1, &info);
    lwork = (int)wkopt;
    work = new double[lwork];
    
    F77NAME(dsyev)('V', 'L', n, A_sym, lda, w, work, lwork, &info);

    for (int i{0}; i < n; i++) {
        double* eigvect = new double[n] {A_sym[i], A_sym[i+1], A_sym[i+2]};
        cout << "Eigenvalue " << i << ": " << w[i] << endl;
        cout << "Eigenvector: "; 
        printMatrixColumnMajor(eigvect, 1, n);
        cout << endl;
    }
}