//boileplate c++ file
using namespace std;
#include <iostream>

int main() {
    int x = 1;
    x ++;
    cout << "Hello World!" << endl;
    return 0;
}

/*  Various ways of compiling the code
    g++ simple.cpp -E simple    // preprocessor output
    g++ simple.cpp -S simple    // assembly output
    g++ simple.cpp -o simple    // object file
*/