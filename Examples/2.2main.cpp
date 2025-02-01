#include <fftw3.h>

int main() {
    const int N = 64;
    fftw_complex in[N], out[N];
    fftw_plan p;

    // populate ’in’ here

    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
}
