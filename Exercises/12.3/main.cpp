#include <iostream>
#include <random>
#include <vector>
#include <mpi.h>

using namespace std;

#define uint unsigned int
#define F77NAME(x) x##_

extern "C" {
    // Level 1 BLAS
    // x . y
    double F77NAME(ddot) (const int& n,         // no. of elements
                          const double* x,      // vector x
                          const int& incx,      // stride of x
                          const double* y,      // vector y
                          const int& incy       // stride of y
                        );
}

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // uint N = 1024;
    uint N = 4;
    
    if (N % size) {
        cout << "No. of processes must divide N (" << N << ")" << endl;
        MPI_Finalize();
        return 1;
    }
    
    uint n = N / size;

    vector<double> x1(n), x2(n);

    srand(time(0) + rank);
    for (uint i{0}; i < n; i++) {
        x1[i] = double(rand())/RAND_MAX;
        x2[i] = double(rand())/RAND_MAX;
    }

    cout << "X1 (rank " << rank << ") = ";
    for (double e : x1) {
        cout << e << ", ";
    }
    cout << endl;

    cout << "X2 (rank " << rank << ") = ";
    for (double e : x2) {
        cout << e << ", ";
    }
    cout << endl;

    double dot_loc = F77NAME(ddot)(n, x1.data(), 1, x2.data(), 1);
    cout << "dot_loc (rank " << rank << ") = " << dot_loc << endl;

    double dot;
    // MPI_Gather(&dot_loc, 1, MPI_DOUBLE, 
    //            &dot, 1, MPI_DOUBLE, 
    //            0, MPI_COMM_WORLD);
    MPI_Reduce(&dot_loc, &dot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Dot = " << dot << endl;
    }

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}