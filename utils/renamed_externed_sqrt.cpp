#include <cmath>
#include <iostream>
extern "C"{

int xx;

using namespace std;

double sqrt2(double x) {
    return sqrt(x);
}

int student_main(int argc, char* argv[]) {
    cin >> xx;
    cout << "sqrt of 9 is: " << sqrt2(xx) << endl;
    return 0;
}
}
