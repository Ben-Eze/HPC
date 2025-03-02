#include <iostream>
#include <mpi.h>
using namespace std;


int main(int argc, char* argv[]) {
    int my_rank, p, i, k;
    MPI_Init(&argc, &argv); // Initialise MPI program
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank); // Get rank
    MPI_Comm_size(MPI_COMM_WORLD,&p); // Get number of procs

    const int n = 64;
    int loc_n = n/p; // Assume p divides n

    double* x = new double[loc_n]; // Only allocate local chunk
    double* y = new double[loc_n];
    
    srand(time(0)+my_rank); // Seed using time and rank

    for (i = 0; i < loc_n; ++i) { // Just populate with random
        x[i] = double(rand())/RAND_MAX; // numbers for this example
        y[i] = double(rand())/RAND_MAX;
    }

    double loc_dot = 0.0; // Local contribution
    for (i = 0; i < loc_n; i++) {
        loc_dot += x[i]*y[i];
    }

    double* loc_dots;
    if (my_rank == 0) loc_dots = new double[p];

    MPI_Gather(&loc_dot,1,MPI_DOUBLE,
               loc_dots,1,MPI_DOUBLE,
               0,
    MPI_COMM_WORLD); // Collate local contributions

    if (my_rank == 0) { // First process computes result
        double dot = 0.0;
        for (k = 0; k < p; k++) {
            dot += loc_dots[k];
        }
        cout << "Dot product: " << dot << endl;
    }

    MPI_Finalize(); // Finish MPI program
}
