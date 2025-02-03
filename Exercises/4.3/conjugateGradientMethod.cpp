// implementation of the conjugate gradient method

#include <iostream>
#include <random>
#include "conjugateGradientMethod.h"

using namespace std;

void main4_3() {
    srand(123);

    uint n = 2;
    double* M = new double[n*n];
    double* A = new double[n*n];
    double* b = new double[n];
    double* xsolution = new double[n];

    // buildM(M, n);
    // buildX(x, n);
    A[0] = 1; A[1] = 3; A[2] = 2; A[3] = 4;     // remember that A is stored in 
                                                // column-major order
    b[0] = 1; b[1] = 2;

    // squareM(M, A, n);
    // multAx(A, x, b, n);
    
    printSquare(A, n);
    // printSquare(A, n);
    printVector(b, n);

    conjGradSolve(b, A, xsolution, n);
    printVector(xsolution, n);
}

void conjGradSolve(double* b, double* A, double* xsolution, const uint n) {
    double* x = new double[n];
    double* r = new double[n];
    double* p = new double[n];
    double* Ax = new double[n];
    double* Ap = new double[n];
    double* X = new double[n];      // x_{k+1}
    double* R = new double[n];      // r_{k+1}
    double* P = new double[n];      // p_{k+1}
    
    for (uint i = 0; i < n; i++) {
        x[i] = 0;
    }

    multAx(A, x, Ax, n);

    for (uint i = 0; i < n; i++) {
        r[i] = b[i] - Ax[i];
        p[i] = r[i];
    }

    double a, beta;
    double k = 0;

    while (true) {
        multAx(A, p, Ap, n);
        a = dotProduct(r, r, n) / dotProduct(p, Ap, n);

        for (uint i = 0; i < n; i++) {
            X[i] = x[i] + a * p[i];
            R[i] = r[i] - a * Ap[i];
        }

        if (dotProduct(R, R, n) < 1e-10) {
            break;
        }

        beta = dotProduct(R, R, n) / dotProduct(r, r, n);

        for (uint i = 0; i < n; i++) {
            P[i] = R[i] + beta * p[i];
        }

        F77NAME(dcopy)(n, X, 1, x, 1);
        F77NAME(dcopy)(n, R, 1, r, 1);
        F77NAME(dcopy)(n, P, 1, p, 1);
    }

    F77NAME(dcopy)(n, X, 1, xsolution, 1);
}

void printSquare(double* x, const uint n) {
    for (uint i = 0; i < n; i++) {
        for (uint j = 0; j < n; j++) {
            cout << x[i*n + j] << " ";
        }
        cout << endl;
    }
}

void printVector(double* x, const uint n) {
    for (uint i = 0; i < n; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}

void buildM(double* M, const uint n) {
    for (uint i = 0; i < n; i++) {
        for (uint j = 0; j < n; j++) {
            M[i*n + j] = (double)(rand())/RAND_MAX * 2 - 1;
        }
    }
}

void buildX(double* x, const uint n) {
    for (uint i = 0; i < n; i++) {
        x[i] = (double)(rand())/RAND_MAX * 2 - 1;
    }
}

void squareM(double* M, double* A, const uint n) {
    F77NAME(dgemm)('T', 'N', n, n, n, 1.0, M, n, M, n, 0.0, A, n);
}

void multAx(double* A, double* x, double* b, const uint n) {
    F77NAME(dgemv)('N', n, n, 1.0, A, n, x, 1, 0.0, b, 1);
}

double dotProduct(double* a, double* b, const uint n) {
    return F77NAME(ddot)(n, a, 1, b, 1);
}