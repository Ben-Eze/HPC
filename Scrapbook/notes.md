## Compiling
# Various ways of compiling the code
// Preprocessing to 'expanded' code
g++ main.cpp -E main.ii 

// Compilation to assembly/'symbolic' code
g++ main.cpp -S main.s

// Assembly to 'object'
g++ main.cpp -c main.o    // 

Linking
g++ main.o -o main.exe

# Flags
-o      // specify output file name
-g      // generate debug info
-Wall   // enable warnings
-l      // link library by name eg. -lblas
-L      // link library by path eg. -L/path/to/my/lib
-I      // include header file by path
-O1 -O2 -O3

# Libraries
Note: the order in which libs are specified matters
eg. if libA depends on libB, we must do g++ main.cpp libA libB

## LAPACK
- We can split F77NAME(dgesv)... # solve
  into F77NAME(dgetrf)...     # triangular factorise
  and F77NAME(dgetrs)         # triangular solve
- dgesv solves a system of linear equations
    - the first step (triangular factorising) is the more expensive part 
- if we are solving the same system over and over again, we can use dgetrf to do the factorising step
    - this allows us to do the most expensive step only once
    - then at each iteration, you just need to use dgetrs

## Performance tests (profilers)
- when compiling, we need to use the debugging flag (-g) AND an older version of the compiler (version 10)
  eg. `g++-10 -g main.cpp -o main.exe`
- we also need to 'module load' the dev-studio
  ie. `module load dev-studios`
- next we 'collect'
  eg. `collect main.exe`
- we run the 


## Cluster
1. create the job that you want to execute on the cluster
eg.    myjob.slr:
    -------------------------------
    |  #!/bin/bash
    |  #SBATCH --nodes=1
    |  #SBATCH --ntasks=1
    |  #SBATCH --mem=2000MB
    |  #SBATCH --time=00:05:00
    |  #SBATCH --job-name=myjob1
    |  #SBATCH --partition=test           # to see which queues are available, use sinfo
    |  ./myprog.exe
    -------------------------------
    
2. convert the job to an exacutable
    >> chmod +x myjob.slr 

3. submit the job
    >> sbatch myjob.slr

4. check the status of the queue
    >> squeue

5. to cancel a job...
    scancel {job_id}

6. check the output of the job in `slurm-{job_id}.out`


## MPI
1. create your script
eg. main.cpp
    ---------------------------------------------------------
    |  #include <iostream>
    |  using namespace std;
    |  
    |  #include <mpi.h>
    |  
    |  int main(int argc, char** argv) {
    |      // Initialize the MPI environment
    |      MPI_Init(&argc, &argv);
    |  
    |      int rank;
    |      MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    |      cout << "Hello! from process " << rank << endl;
    |  
    |      // Finalize the MPI environment
    |      MPI_Finalize();
    |  
    |      return 0;
    |  }
    ---------------------------------------------------------

2. compile WITH MPIXX
    >> mpicxx main.cpp -o myprog

3. run WITH MPIRUN (specifying the no. of processes)
    >> mpirun -np 2 ./myprog

# MPI Functions
SEND:
int MPI_Send(type var,              // address of variable
             int count,             // size/no. of elements in var
             MPI_Datatype type,     // type of var (see below)
             int dest,              // rank of receiver
             int tag,               // message tag
             MPI_Comm comm          // normally MPI_COMM_WORLD
)

RECEIVE:
int MPI_Recv(type var, 
             int count, 
             MPI_Datatype type, 
             int source,            // rank of sender
             int tag, 
             MPI_Comm comm, 
             MPI_Status *status     // default: MPI_STATUS_IGNORE
)

SYNCHRONOUS SEND: (waits until messave is received before continuing)
int MPI_Ssend(type var, int count, MPI_Datatype type, int dest, 
              int tag, MPI_Comm comm)

Other functions:
// Synchronise processes
int MPI_Barrier(MPI_Comm comm);

// Broadcast copies data from process ’root’
int MPI_Bcast(void *buffer, 
              int count, 
              MPI_Datatype datatype,
              int root, 
              MPI_Comm comm )

// Distribute data among processes from process ’root’
int MPI_Scatter(const void *sendbuf, 
                int sendcount, 
                MPI_Datatype sendtype,
                void *recvbuf, 
                int recvcount, 
                MPI_Datatype recvtype, 
                int root,
                MPI_Comm comm)

// Gather data from processes to process ’root’
int MPI_Gather(const void *sendbuf, 
               int sendcount, 
               MPI_Datatype sendtype,
               void *recvbuf, 
               int recvcount, 
               MPI_Datatype recvtype, 
               int root,
               MPI_Comm comm)

// Reduce data using ’op’ onto process ’root’
int MPI_Reduce(const void *sendbuf, 
               void *recvbuf, 
               int count,
               MPI_Datatype datatype, 
               MPI_Op operation, 
               int root, 
               MPI_Comm comm)

// Reduce data using ’op’ onto all processes
int MPI_Allreduce(const void *sendbuf, 
                  void *recvbuf, 
                  int count,
                  MPI_Datatype datatype, 
                  MPI_Op op, 
                  MPI_Comm comm)

// Each process sends a chunk of data to each other process
int MPI_Alltoall(const void *sendbuf, 
                 int sendcount, 
                 MPI_Datatype sendtype,
                 void *recvbuf, 
                 int recvcount, 
                 MPI_Datatype recvtype,
                 MPI_Comm comm)

# MPI Datatypes
MPI_CHAR            signed char
MPI_SHORT           signed short
MPI_INT             signed int
MPI_LONG            signed long
MPI_UNSIGNED_*      unsigned * (as above)
MPI_FLOAT           float
MPI_DOUBLE          double
MPI_LONG_DOUBLE     long double

# MPI OPERATIONS
MPI_MAX
MPI_MIN
MPI_SUM
MPI_PROD