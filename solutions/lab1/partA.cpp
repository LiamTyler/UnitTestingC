#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]){
    double init, halflife, time, residual;

    cout << "Enter the initial amount, half-life, and time" << endl;
    cin >> init >> halflife >> time;

    residual = init*pow(0.5, time / halflife);

    cout << "residual amount remaining = " << residual << endl;

    return 0;
}
