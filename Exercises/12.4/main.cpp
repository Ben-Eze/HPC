#include <iostream>
#include <cmath>
#include <mpi.h>

using namespace std;

#define uint unsigned int


double integrand(double x) {
    return 1 / (1 + x*x);
}

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    uint N;                          // no of trapz's
    if (rank == 0) {
        cout << "Enter the no. of intervales: ";
        cin >> N;
    }
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    double dx = 1.0 / N;
    uint N_loc = ceil((double)(N)/size);
    // uint N_full = N_loc * size;          // no. of ...    

    double x;
    double A_loc = 0;
    

    for (uint i{0}; 
         i < (rank != size-1 ? N_loc : N - (size-1) * N_loc); 
         i++) {
        x = (rank * N_loc + i) * dx;
        A_loc += (integrand(x) + integrand(x+dx)) / 2 * dx;
    }

    double A;

    MPI_Reduce(&A_loc, &A, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Pi = " << 4*A << endl;
    }    

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}