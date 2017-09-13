#include <iostream>
#include <typeinfo>
#include <string>
#include "include/io_tester.h"
#include "include/function_tester.h"
#include "include/program.h"

using namespace std;


int main(int argc, char* argv[]) {
    // Set up students code
    // ----------------------------------------------------------------------
    Program stu_code(argv[1]);
    if (!stu_code.FullPrepare()) {
        cout << "Failed to compile and load students code" << endl;
        return 1;
    }

    // TEST 1
    // ----------------------------------------------------------------------
    typedef int (*stu_main)(int, char**);
    stu_main f = (stu_main) stu_code.GetFunction("student_main");

    IOTester<int, int, char**> iotester("Print name", f);
    int argc2 = 0;
    char** argv2 = nullptr;
    iotester.AddTest("Liam's", 0, "Liam", "Hello, Liam!\\s+", argc2, argv2);
    iotester.AddTest("Nick's", 0, "Nick", "Hello, Nick\\s+", argc2, argv2);
    iotester.RunAllTests();
    iotester.GetSummary(cout);

    // TEST 2
    // ----------------------------------------------------------------------
    typedef int (*div)(int, int);
    div f2 = (div) stu_code.GetFunction("div2");

    string s = "Int division";
    FunctionTester<int, int, int> tester(s, f2);
    tester.AddTest("5 / 3", 1, 5, 3, 5, 3);
    tester.AddTest("3 / 0", 0, 3, 0, 3, 0);
    tester.RunAllTests();
    tester.GetSummary(cout);

    return 0;
}
