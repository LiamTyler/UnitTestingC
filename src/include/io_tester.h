#ifndef SRC_INCLUDE_IO_TESTER_H_
#define SRC_INCLUDE_IO_TESTER_H_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include "include/function_tester.h"

using namespace std;

template<typename retType, typename... Args>
class IOTester : public FunctionTester<retType, Args...> {
    typedef retType (*func_ptr)(Args...);
    public:
        IOTester(func_ptr f);
        virtual void AddTest(retType ans, Args... inputs, string cin_in, string cout_ans);
        virtual bool RunTest(int test_num);

    protected:
        bool OutputMatches(int test);
        void LoadCinInputs(int test);
        void UndoCinRedirect();
        void RedirectOutput();
        void UndoRedirectOutput();

        vector<string> cin_inputs_;
        vector<string> cout_answers_;

        stringstream cout_buffer_;
        istringstream cin_buffer_;
        streambuf* old_cout_buf_;
        streambuf* old_cin_buf_;
};

#endif  // SRC_INCLUDE_IO_TESTER_H_
