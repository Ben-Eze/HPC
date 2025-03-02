#include <iostream>
#include <mpi.h>

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

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}