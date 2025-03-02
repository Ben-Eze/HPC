#include <iostream>
#include <mpi.h>

using namespace std;


int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Request request;

    double x, y;

    if (rank == 0) {
        x = 5;
        MPI_Irecv(&y, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &request);
        MPI_Send(&x, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
    }
    else {
        x = 10;
        MPI_Irecv(&y, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Send(&x, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    
    MPI_Wait(&request, MPI_STATUS_IGNORE);
    cout << "rank: " << rank << ", x = " << x << ". Received " << y << endl;

    MPI_Finalize();
}