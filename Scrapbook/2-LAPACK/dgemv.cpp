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
                        int& info);
}

void printMatrixColumnMajor(double* A, int height, int width) {
    for (int j{0}; j < height; j++) {
        cout << (j == 0 ? "[[" : "\n [");
        for (int i{0}; i < width; i++) {
            cout << A[i*height + j] << (i == width-1 ? "" : ", ");
        }
        cout << "]";
    }
    cout << "]" << endl;
}

void printMatrixRowMajor(double* A, int height, int width) {
    for (int j{0}; j < height; j++) {
        cout << (j == 0 ? "[[" : "\n [");
        for (int i{0}; i < width; i++) {
            cout << A[j*width + i] << (i == width-1 ? "" : ", ");
        }
        cout << "]";
    }
    cout << "]" << endl;
}

int main() {
    int n = 2, nrhs = 3;
    double A[n*n] = {2, 1, 1, 4};
    double y[n*nrhs] = {2, 1, 5, 6, 2, 8};
    printMatrixColumnMajor(A, n, n);
    printMatrixColumnMajor(y, n, nrhs);
    
    
    int ipiv[n];
    int info;
    
    F77NAME(dgesv)(n, nrhs, A, n, ipiv, y, n, info);
    printMatrixColumnMajor(y, n, nrhs);


    // [1, 2, 0,
    //  0, 1, 2]
}