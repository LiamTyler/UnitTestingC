#include <iostream>
#include <string>
#include "include/io_tester.h"
#include "include/function_tester.h"

using namespace std;

void print_name() {
    string s;
    cin >> s;
    cout << s << endl;
}

int add(int a, int b) {
    return a + b;
}

void add2(int a, int b) {
    int c = a + b;
}

int main(int argc, char* argv[]) {
    IOTester<void> iotester("Print name", print_name);
    iotester.AddTest("Liam's", "Liam", "Liam\\s+");
    iotester.AddTest("Nick's", "Nick", "Niick\\s+");
    iotester.RunAllTests();
    iotester.GetSummary(cout);

    /*
    string s = "Int Addition";
    FunctionTester<int, int, int> tester(s, add);
    tester.AddTest("Pos + Pos", 5, 2, 3);
    tester.AddTest("Neg + Neg", -4, -2, -3);
    tester.RunAllTests();
    tester.GetSummary(cout);
    */

    /*
    FunctionTester<void, int, int> tester("Int Tester", add2);
    tester.AddTest("Pos + Pos", 2, 3);
    tester.AddTest("Neg + Neg", -2, -3);
    tester.RunAllTests();
    tester.GetSummary(cout);
    */


    return 0;
}
