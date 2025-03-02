#include <iostream>
#include <mpi.h>
#include <random>

using namespace std;

int main(int argc, char** argv) {
    // Initialise MPI
    if (MPI_Init(&argc, &argv)) {
        cout << "Error initializing MPI" << endl;
        MPI_Finalize();
        return 1;
    }

    // Get rank and no. of processes
    int rank, size;

    if (MPI_Comm_rank(MPI_COMM_WORLD, &rank)) {
        cout << "Error getting rank" << endl;
        MPI_Finalize();
        return 1;
    }

    if (MPI_Comm_size(MPI_COMM_WORLD, &size)) {
        cout << "Error getting size" << endl;
        MPI_Finalize();
        return 1;
    }

    // Ensure that only 2 processors
    if (size != 2){
        cout << "This program is meant to be run with 2 processes" << endl;
        MPI_Finalize();
        return 1;
    }

    // Create variables to send and receive to 
    srand(time(0) + rank*100);
    double x = (double)(rand())/RAND_MAX;
    cout << "Process " << rank << " sends message: " << x << endl;

    double y = 0.0;

    // Point-to-point communication
    // SEND:   
    // int MPI_Send(type var, int count, MPI_Datatype type, int dest, 
    //              int tag, MPI_Comm comm)
    // RECEIVE:
    // int MPI_Recv(type var, int count, MPI_Datatype type, int source,
    //              int tag, MPI_Comm comm, MPI_Status *status)

    if (rank == 0){
        MPI_Send(&x, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&y, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    
    else {
        MPI_Send(&x, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(&y, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    cout << "Process " << rank << " receives message: " << y << endl;

    MPI_Finalize();
    return 0;
}