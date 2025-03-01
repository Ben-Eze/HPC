#include <iostream>
#include <cmath>

using namespace std;
#define F77NAME(x) x##_
#define PI 3.141592653589
#define myfunc(x) sin(PI * x)

extern "C" {
    double F77NAME(dgbmv) (
        const char& trans, const int& m, 
        const int& n, const int& kl, 
        const int& ku, const double& alpha, 
        const double* a, const int& lda, 
        const double* x, const int& incx, 
        const double& beta, const double* y, 
        const int& incy 
    );
    double F77NAME(dnrm2) (
        const int& n, const double* x, 
        const int& incx
    );
    void F77NAME(daxpy)(const int& n, const double& alpha,
        const double* x, const int& incx, double* y, const int& incy);
}

int main() {
    int Nx = 1001;
    double h = 0.001;
    double* f = new double [Nx];
    double x;
    double L = 1.0;
    int KL = 0;
    int KU = 3;
    int lda = 1 + KL + KU;

    for (int i{0}; i < Nx; i++) {
        x = i*h;
        f[i] = sin(PI * x);
    }

    // D
    double* D = new double[lda*Nx];
    for (int i{0}; i < Nx; i++) {
        D[lda*i  ] = -1.0/h/h;
        D[lda*i+1] = 4.0/h/h;
        D[lda*i+2] = -5.0/h/h;
        D[lda*i+3] = 2.0/h/h;
    }

    // b
    double* b = new double[Nx];
    for (int i{0}; i < Nx-3; i++) {
        b[i] = 0;
    }
    b[Nx-3] = (  -myfunc(L + h)                                      )/h/h;
    b[Nx-2] = ( 4*myfunc(L + h) - myfunc(L + 2*h)                    )/h/h;
    b[Nx-1] = (-5*myfunc(L + h) + 4*myfunc(L + 2*h) - myfunc(L + 3*h))/h/h;


    // b = Df + b
    F77NAME(dgbmv) (
        'n',    // trans
        Nx,     // m
        Nx,     // n
        KL,      // KL
        KU,      // KU
        1,      // alpha
        D,      // A
        lda,     // lda
        f,      // x
        1,      // incx
        1,      // beta
        b,      // y
        1       // incy
    );

    // f"
    double* fxx_exact = new double [Nx];

    for (int i{0}; i < Nx; i++) {
        x = i*h;
        fxx_exact[i] = -PI*PI * sin(PI * x);
        // error[i] = -PI*PI * sin(PI * x) - b[i];
    }

    F77NAME(daxpy)(Nx, -1.0, fxx_exact, 1, b, 1);

    // epsilon
    double epsilon = F77NAME(dnrm2) (
        Nx, b, 1
    );

    cout << epsilon << endl;

    delete[] f;
    delete[] D;
    delete[] b;
    delete[] fxx_exact;
}
