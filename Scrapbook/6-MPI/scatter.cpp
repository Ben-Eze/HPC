#include <iostream>
#include <numeric>
#include <mpi.h>

using namespace std;

#define uint unsigned int


int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    uint N = 64;

    if (N % size) {
        cout << "No. of processes must divide N (64)" << endl;
        MPI_Finalize();
        return 1;
    }

    uint n = N / size;
    double* A;

    if (rank == 0) {
        A = new double[N];
        
        for (uint i{0}; i < N; i++) {
            A[i] = (double)(i);
            // cout << A[i] << endl;
        }
    }

    double* A_partial = new double[n];

    MPI_Scatter(A, n, MPI_DOUBLE,
                A_partial, n, MPI_DOUBLE,
                0, MPI_COMM_WORLD);

    double partial_sum = reduce(A_partial, A_partial + n);    // sums up elements of a, #include <numeric>
    cout << "partial_sum = " << partial_sum << endl;

    double sum;
    MPI_Reduce(&partial_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "sum = " << sum << endl;
    }

    MPI_Finalize();
}