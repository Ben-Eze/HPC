/*
Read from signal.txt file and print the values
signal.txt contains a list of numbers separated by newlines
*/ 

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <fftw3.h>

using namespace std;

vector<double> readSignal(string filename);
void vecPrint(vector<double> x);

int main() {
    vector<double> x = readSignal("signal.txt");
    vecPrint(x);


    return 0;
}

vector<double> readSignal(string filename) {
    // Declare variables
    vector<double> x;
    ifstream file(filename);

    // Check if file is open
    if (!file.is_open()) {
        // cout << "Could not open file" << endl;
        // raise error
        throw runtime_error("Could not open file");
    }

    // Read from file
    double value;
    while (file >> value) {
        x.push_back(value);
    }

    return x;
}

void vecPrint(vector<double> x) {
    // Print out the values
    for (int i = 0; i < x.size(); i++) {
        if (i > 10) {
            cout << "..." << endl;
            break;
        }
        cout << x[i] << endl;
    }
}