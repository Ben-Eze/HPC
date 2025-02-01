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
void vecPrint(vector<vector<double>> x);
vector<vector<double>> DFTReal(vector<double> x);
vector<double> IDFTReal(vector<vector<double>> X);

int main() {
    vector<double> x = readSignal("signal.txt");
    cout << "Signal:" << endl;
    vecPrint(x);

    vector<vector<double>> X = DFTReal(x);
    cout << "Frequencies:" << endl;
    vecPrint(X);

    vector<double> x_ = IDFTReal(X);
    cout << "Reconstructed signal:" << endl;
    vecPrint(x_);
    return 0;
}

vector<vector<double>> DFTReal(vector<double> x) {
    // Declare variables
    int N = x.size();
    fftw_complex *in, *out;
    fftw_plan p;

    // Allocate memory
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

    // Create a plan
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    // Copy the input data
    for (int i = 0; i < N; i++) {
        in[i][0] = x[i];
        in[i][1] = 0.0;
    }

    // Execute the plan
    fftw_execute(p);

    // Copy the output data
    vector<vector<double>> X(N, vector<double>(2));
    for (int i = 0; i < N; i++) {
        X[i][0] = out[i][0];
        X[i][1] = out[i][1];
    }

    // Free memory
    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);

    return X;
}

vector<double> IDFTReal(vector<vector<double>> X) {
    // Declare variables
    int N = X.size();
    fftw_complex *in, *out;
    fftw_plan p;

    // Allocate memory
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

    // Create a plan
    p = fftw_plan_dft_1d(N, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);

    // Copy the input data
    for (int i = 0; i < N; i++) {
        in[i][0] = X[i][0];
        in[i][1] = X[i][1];
    }

    // Execute the plan
    fftw_execute(p);

    // Copy the output data
    vector<double> x(N);
    for (int i = 0; i < N; i++) {
        x[i] = out[i][0]/N;
    }

    // Free memory
    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);

    return x;
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
    cout << "[";
    for (int i = 0; i < x.size(); i++) {
        cout << " " << x[i] << endl;
        if (i > 10) {
            cout << "...";
            break;
        }
    }
    cout << "]" << endl;
}

void vecPrint(vector<vector<double>> x) {
    // Print out the values
    cout << "[";
    for (int i = 0; i < x.size(); i++) {
        if (i > 10) {
            cout << "...";
            break;
        }
        cout << " ";
        for (int j = 0; j < x[i].size(); j++) {
            cout << x[i][j] << " ";
        }
        cout << endl;
    }
    cout << "]" << endl;
}