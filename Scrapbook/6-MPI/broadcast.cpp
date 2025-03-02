/*
int MPI_Bcast(void *buffer, 
              int count, 
              MPI_Datatype datatype,
              int root, 
              MPI_Comm comm )

Sends the data in `buffer` on process rank = `root` to `buffer` in all ranks
*/

#include <iostream>
#include <mpi.h>
#include <vector>

using namespace std;


int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    vector<double> A(5);
    if (rank == 0) {
        A = {1, 2, 3, 4, 5};
    }

    MPI_Bcast(A.data(), 5, MPI_DOUBLE,
              0, MPI_COMM_WORLD);
    
    for (int i{0}; i < 5; i++) {
        cout << A[i] << ", ";
    }  
    cout << endl;

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}