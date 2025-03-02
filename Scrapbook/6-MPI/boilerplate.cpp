#include <iostream>
#include <mpi.h>

using namespace std;


int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}