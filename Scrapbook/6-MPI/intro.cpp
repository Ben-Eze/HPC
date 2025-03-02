#include <iostream>
using namespace std;

#include <mpi.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    int rank, Nproc;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &Nproc);
    cout << "Hello! from process " << rank << " of " << Nproc << endl;

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}