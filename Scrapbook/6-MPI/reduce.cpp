#include <iostream>
#include <mpi.h>
#include <vector>
#include <random>
#include <time>

#define F77NAME(x) x##_

extern "C" {
    double F77NAME(ddot) (const int& n,
                          const double* x, const int& incx,
                          const double* y, const int& incy);
}


using namespace std;

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    int N = 1024;

    int rank, N_proc;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &N_proc);

    int N_loc = N / N_proc;

    srand(time(0) + rank*100);

    vector<double> a(N_loc), b(N_loc);
    for (int i{0}; i < N_loc; i++){
        a[i] = (double)(rand())/RAND_MAX;
        a[i] = (double)(rand())/RAND_MAX;
    }
    
    double dot_loc = F77NAME(ddot)(N_loc, a.data(), 1, b.data(), 1);
    double dot;

    MPI_Reduce(&dot_loc, &dot, 1, MPI_DOUBLE, MPI_SUM)
}