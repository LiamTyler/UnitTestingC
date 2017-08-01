#include "include/io_tester.h"
#include <sstream>
#include <cstring>
#include <cmath>

using namespace std;

int student_main(int argc, char* argv[]);

IOTester::IOTester() {
    argc_ = 0;
    argv_ = nullptr;
    cin_inputs_ = "";
    regex_ = "";
    exit_code_ = 0;
}

void IOTester::LoadCinInputs() {
    cin_buffer_ = istringstream(cin_inputs_);
    cin.rdbuf(cin_buffer_.rdbuf());
}

void IOTester::UndoCinRedirect() {
    cin.rdbuf(old_cin_buf_);
}

void IOTester::SetArgs(vector<string> args) {
    args_ = args;
}

void IOTester::ClearArgv() {
    if (argc_ != 0) {
        for (int i = 0; i <= argc_; i++)
            delete[] argv_[i];
        delete[] argv_;
        argc_ = 0;
    }
}

void IOTester::LoadArgs() {
    ClearArgv();
    args_.insert(args_.begin(), "./a.out");
    argc_ = args_.size();
    argv_ = new char*[argc_ + 1];
    for (int i = 0; i < argc_; i++) {
        argv_[i] = new char[args_[i].length() + 1];
        strcpy(argv_[i], args_[i].c_str());
    }
    argv_[argc_] = (char) NULL;
}

void IOTester::RedirectOutput() {
    old_cout_buf_ = cout.rdbuf(cout_buffer_.rdbuf());
}

void IOTester::UndoRedirectOutput() {
    cout.rdbuf(old_cout_buf_);
}

int IOTester::Test(string filename) {
    LoadArgs();
    LoadCinInputs();
    RedirectOutput();

    student_main(argc_, argv_);

    UndoRedirectOutput();

    cout << "Output was: " << endl;
    cout << cout_buffer_.str() << endl;

    args_.clear();
}
