#include <iostream>
#include <mpi.h>
#include <vector>


using namespace std;

#define uint unsigned int

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    uint N = 64;

    if (N % size) {
        cout << "No. of processes must divide N (" << N << ")" << endl;
        MPI_Finalize();
        return 1;
    }

    uint n = N / size;

    vector<double> A_partial(n, (double)(rank));
    // A_partial: [rank, rank, rank, ...]
    
    vector<double> A(N);
    
    // broadcast 
    MPI_Gather(A_partial.data(), n, MPI_DOUBLE, 
               A.data(), n, MPI_DOUBLE, 
               0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (double a : A) {
            cout << a << ", ";
        }
        cout << endl; 
        // produces something like...
        // >> 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 
        // NOTE: it does this in order
    }

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}