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

# LAPACK
- We can split F77NAME(dgesv)... # solve
  into F77NAME(dgetrf)...     # triangular factorise
  and F77NAME(dgetrs)         # triangular solve
- dgesv solves a system of linear equations
    - the first step (triangular factorising) is the more expensive part 
- if we are solving the same system over and over again, we can use dgetrf to do the factorising step
    - this allows us to do the most expensive step only once
    - then at each iteration, you just need to use dgetrs

# Performance tests (profilers)
- when compiling, we need to use the debugging flag (-g) AND an older version of the compiler (version 10)
  eg. `g++-10 -g main.cpp -o main.exe`
- we also need to 'module load' the dev-studio
  ie. `module load dev-studios`
- next we 'collect'
  eg. `collect main.exe`
- we run the 
