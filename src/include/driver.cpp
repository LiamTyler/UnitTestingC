#include <iostream>
#include <string>
#include "io_tester.h"

using namespace std;

int student_main(int argc, char* argv[]) {
    int a, b;
    cin >> a >> b;
    cout << to_string(a + b) << endl;

    return 0;
}

int main(int argc, char* argv[]) {
    IOTester<int, int, char**> tester(student_main);
    tester.AddTest(0, argc, argv, "1 2", "3\\s+");
    cout << tester.RunTest(0) << endl;


    return 0;
}
