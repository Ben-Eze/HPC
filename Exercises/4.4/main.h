#define PI 3.14159265

void buildA(double* A, const uint n, const double alpha, const double beta);
void buildX(double* X, const uint n, const double dx);
void buildF(double* F, double* X, const uint n, 
            double (*f)(double, double), const double l);
void buildU(double* U, const uint n, 
            const double u_a, const double u_b);
double f(double x, double l);