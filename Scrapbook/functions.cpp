#include <iostream>
using namespace std;



void printMatrixColumnMajor(double* A, int height, int width) {
    // used for LAPACK
    for (int j{0}; j < height; j++) {
        cout << (j == 0 ? "[[" : "\n [");
        for (int i{0}; i < width; i++) {
            cout << A[i*height + j] << (i == width-1 ? "" : ", ");
        }
        cout << "]";
    }
    cout << "]" << endl;
}

void printMatrixRowMajor(double* A, int height, int width) {
    for (int j{0}; j < height; j++) {
        cout << (j == 0 ? "[[" : "\n [");
        for (int i{0}; i < width; i++) {
            cout << A[j*width + i] << (i == width-1 ? "" : ", ");
        }
        cout << "]";
    }
    cout << "]" << endl;
}