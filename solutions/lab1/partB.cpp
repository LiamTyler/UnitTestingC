#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]){
    double volts = 120, watts, current;

    cout << "Enter the wattage rating of your electical appliance: " << endl;
    cin >> watts;
    double amps = watts / volts;
    cout << "An appliance with a power rating of " << watts << " watts places " <<
        amps << " amperes of current on the circuit. The number of " << 
        "such appliances which can be placed on a circuit with a 20-amp" <<
        " circuit breaker is " << (int) 20 / amps << "." << endl;

    return 0;
}
