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
                        const int& ldab,        // leading dimension ofA_band
                        int * ipiv,             // pivot indices
                        double * y,             // matrix/vector y
                        const int& ldy,         // leading dimension of y
                        int& info               // 0: success, >0: failure, 
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
    /*
    A = [[1, 4, 0,  0,  0],    b = [[1],
         [2, 5, 8,  0,  0],          [2], 
         [3, 6, 9,  12, 0],          [3],
         [0, 7, 10, 13, 15],         [4],
         [0, 0, 11, 14, 16]])        [5]]
    
    A_b = [[X, X, X , X , X ],
           [X, X, X , X , X ],
           [X, 3, 7 , 11, 14],
           [0, 4, 8 , 12, 15],
           [1, 5, 9 , 13, X ],
           [2, 6, 10, X , X ]]  
    */

    int n = 5;          // A: (n, n)
    int KL = 2, KU = 1; // A_b: (nb, n)
    int nb = 1 + 2*KL + KU;     // height of banded matrix (with padding)
    double X = 0;   // Placeholder for unused elements
    double* A_b = new double[nb * n] {X, X, X , 0 , 1 , 2 ,
                                      X, X, 3 , 4 , 5 , 6 ,
                                      X, X, 7 , 8 , 9 , 10,
                                      X, X, 11, 12, 13, X ,
                                      X, X, 14, 14, X , X };

    printMatrixColumnMajor(A_b, nb, n);
    double* b = new double[n] {1, 2, 3, 4, 5};
    int* ipiv = new int[n];
    int info;

    F77NAME(dgbsv)(n, KL, KU, 1, A_b, nb, ipiv, b, n, info);

    printMatrixColumnMajor(b, n, 1);
}