#include "blasStuff.h"
#include <iostream>

void blasTest() {
    double A[4] = {1, 3, 2, 4};
    double B[4] = {1, 3, 2, 4};
    double C[4];

    F77NAME(dgemm)('N', 'N', 2, 2, 2, 1, A, 2, B, 2, 0, C, 2);

    for (int i = 0; i < 4; i++) {
        std::cout << C[i] << " ";
    }
    std::cout << std::endl;
}