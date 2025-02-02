#include <iostream>
#include <math.h>

#define F77NAME(x) x##_

using namespace std;

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

int main() {
    int n = 1;
    // N = 2^n;
    int N = pow(2, n);
    
    double* A = new double[N*N] {1, 0, -1, 1};
    double* B = new double[N*N] {1, 2, 7, 8};
    double* C = new double[N*N];

    F77NAME(dgemm)('T', 'T', N, N, N, 1.0, A, N, B, N, 0.0, C, N);

    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            cout << C[i*N + j] << " ";
        }
        cout << endl;
    }
}