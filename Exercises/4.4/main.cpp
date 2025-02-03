#include <iostream>
#include <cmath>
#include "../4.3/conjugateGradientMethod.h"
#include "main.h"

using namespace std;

// NOT WORKING :)

int main() {
    double a = 0;
    double b = 2;
    double l = 1;  // lambda
    uint n = 5;
    double dx = 0.1;
    double alpha = -2/(dx*dx) - l;
    double beta = 1/(dx*dx);
    double u_a = 0;
    double u_b = 0;

    double* X = new double[n];
    double* F = new double[n];
    double* A = new double[n*n];
    double* U = new double[n];
    
    buildA(A, n, alpha, beta);
    buildX(X, n, dx);
    buildF(F, X, n, &f, l);
    buildU(U, n, u_a, u_b);

    cout << "Matrix A (with Fortran indexing convention)" << endl;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            cout << A[i*n + j] << " ";
        }
        cout << endl;
    }

    conjGradSolve(F, A, &U[1], n-2);

    cout << "Solution U" << endl;
    for (int i = 0; i < n; i++) {
        cout << U[i] << " ";
    }
}

void buildA(double* A, const uint n, 
            const double alpha, const double beta) {
    // fill alpha
    for (uint i{0}; i < n; i++) {
        A[i*(n + 1)] = alpha;
    }

    // fill beta
    for (uint i{1}; i < n; i++) {
        A[i*(n + 1)-1] = beta;
    }
    for (uint i{0}; i < n-1; i++) {
        A[i*(n + 1)+1] = beta;
    }
}

void buildX(double* X, const uint n, const double dx) {
    for (uint i{0}; i < n; i++) {
        X[i] = i * dx;
    }
}

void buildF(double* F, double* X, const uint n, 
            double (*f)(double, double), const double l) {
    for (uint i{0}; i < n; i++) {
        F[i] = f(X[i], l);
    }
}

void buildU(double* U, const uint n, 
            const double u_a, const double u_b) {
    for (uint i{1}; i < n-1; i++) {
        U[i] = 0;
    }
    U[0] = u_a;
    U[n-1] = u_b;
}

double f(double x, double l) {
    return -(l + PI*PI) * sin(PI * x);
}

