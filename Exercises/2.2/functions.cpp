#include <cmath>


double piFromSum(int n) {
    double sum = 0.0;
    for (int k = 0; k < n; k++) {
        sum += pow(-1.0, k)/(2.0*k + 1.0);
    }
    return 4.0*sum;
}