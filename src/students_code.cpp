#include <iostream>
#include <string>

using namespace std;

void add2(int a, int b) {
    int c = a + b;
}

int div2(int a, int b) {
    return a / b;
}

int main() {
    string name;
    cin >> name;
    cout << "Hello, " << name << "!" << endl;

    return 0;
}
