# Unit Testing

## Description
Right at the end of a semester, I was asked by the professor who I was a teaching assistant for, to try to make a framework for testing student's code. I only had about a week to try and make this. I was also told that I could only be paid for 10 hours of work on this, but I still put about 30 hours into it.

This framework is currently only capable of testing IO and functions and right now, including int main(). It doesn't have the same support for classes yet. What it does though, is compiles the students code, and runs each test in a separate process, so if they crash, it's ok. It then returns a final summary of how many tests passed.

## Features
#### Testing
- Create a 'Tester' object, and give it the student's function that you wish to test
- Add test cases to that Tester object by giving it the starting parameters, and what the return should be
- If you are testing standard IO, you can also give a test cases the input string it needs, and a regex of what the output should be
- Run all the tests, each in a separate process, so that crashes are fine
- Get a finally summary for a Tester object, to see how many tests succeeded

#### Handling Student's Code
- Create a 'Program' object that takes in the filename of the code you want to test
- The Program object will create a new copy of that file with int main() renamed (as to not conflict with the main() from the tester's code) and add the necessary includes for dynamic linking
- Will compile the code, or alert the user if it failed to compile
- Once compiled, you can give it the name of a function you want, and it will return it

## Example
```c++
Program student_prgm("students_code.cpp");
if (!student_prgm.FullPrepare()) {
    cout << "Failed to compile and dynamically load student's code" << endl;
    exit(1);
}

// Get student's int main() function
typedef int (*stu_main)(int, char**);
stu_main f = (stu_main) student_prgm.GetFunction("student_main");

// Create a tester object for that int main(). Lets say their code should
// just allow the user to enter their name, and then print "Hello, ____!"
// with their name in it.

// IOTester<return_type, param 1 type, param 2 type>
// iotester(test_name, test_function)
IOTester<int, int, char**> iotester("Print name", f);
// Now, set up test cases
int test_argc = 0
char** test_argv = nullptr;
//                test_name, expected ret, input, output regex, arg 1, arg2
iotester.AddTest("Bob's Test", 0, "Bob", "Hello, Bob!\\s+", test_argc, test_argv);
iotester.AddTest("Sam Smiths's Test", 0, "Sam Smith", "Hello, Sam Smith!\\s+", test_argc, test_argv);
iotester.RunAllTests();
iotester.GetSummary(cout);
```
