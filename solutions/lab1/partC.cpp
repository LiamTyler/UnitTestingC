#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]){
    double c = 3e10;
    double L, v, RL;

    cout << "Enter the length of the object and its velocity: ";
    cin >> L >> v;

    RL = L * sqrt(1 - (v*v)/(c*c));

    cout << "The relativistic length is: " << RL << endl;

    return 0;
}
