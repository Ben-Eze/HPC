#include <iostream>
#include <mpi.h>

using namespace std;


int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int x;


    // // Method 1: broadcast
    // if (rank == 0) {
    //     cout << "Inter an integer: " << endl;
    //     cin >> x;
    // }

    // MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // cout << "Rank: " << rank << ". Received message x = " << x << endl;


    // Method 2: send and receive
    if (rank == 0) {
        // first process
        cout << "Inter an integer: " << endl;
        cin >> x;

        cout << "Rank: " << rank << ". Message x = " << x << endl;
        MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else if (rank == size - 1) {
        // last process
        MPI_Recv(&x, 1, MPI_INT, rank - 1, 0, 
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Rank: " << rank << ". Received message x = " << x << endl;
    }
    else {
        // everything in between
        MPI_Recv(&x, 1, MPI_INT, rank - 1, 0, 
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Rank: " << rank << ". Received message x = " << x << endl;
        MPI_Send(&x, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }


    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}