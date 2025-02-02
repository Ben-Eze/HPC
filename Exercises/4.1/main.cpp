#include <iostream>

#define F77NAME(x) x##_

extern "C" {
    double F77NAME(dnrm2) (const int&n, 
                           const double*x, const int& incx);
    double F77NAME(dasum) (const int&n, 
                           const double*x, const int& incx);
    int F77NAME(idamax) (const int&n, 
                         const double*x, const int& incx);
        
}

int main() {
    double* x = new double [4];
    x[0] = 3;
    x[1] = -4;
    x[2] = 1;
    x[3] = -2;
    double x_norm = F77NAME(dnrm2)(4, x, 1);
    double x_asum = F77NAME(dasum)(4, x, 1);
    int i_max = F77NAME(idamax)(4, x, 1) - 1;   // Fortran is 1-indexed!
    double x_max = x[i_max];
    std::cout << "Norm of x: " << x_norm << std::endl;
    std::cout << "Asum of x: " << x_asum << std::endl;
    std::cout << "Max of x: " << x_max << std::endl;
}