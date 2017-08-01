#ifndef IO_TESTER_H_
#define IO_TESTER_H_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include "include/function_tester.h"

using namespace std;

int student_main(int argc, char* argv[]);

template<typename retType, typename... Args>
class IOTester : public FunctionTester<retType, Args...> {
    typedef retType (*func_ptr)(Args...);
    public:
        IOTester(func_ptr f) : FunctionTester<retType, Args...>(f) {

        }
        virtual void AddTest(retType ans, Args... inputs, string cin_in, string cout_ans) {
            this->answers_.push_back(ans);
            this->input_argsets_.push_back(tuple<Args...>(inputs...));
            cin_inputs_.push_back(cin_in);
            cout_answers_.push_back(cout_ans);
        }

        virtual bool RunTest(int test_num) {
            LoadCinInputs(test_num);
            RedirectOutput();

            retType ret = this->callFunc(test_num, typename gens<sizeof...(Args)>::type());
            UndoRedirectOutput();
            UndoCinRedirect();
            /*
            cout << "Should return: " << this->answers_[test_num] << endl;
            cout << "Actually returned: " << ret << endl;
            cout << "Should output: " << cout_answers_[test_num] << endl;
            cout << "Actually outputted: " << cout_buffer_.str() << endl;
            bool a = this->answers_[test_num] == ret;
            bool b = cout_answers_[test_num] == cout_buffer_.str();
            cout << a << endl;
            cout << b << endl;
            cout << OutputMatches(test_num) << endl;
            */

            return ret == this->answers_[test_num] && OutputMatches(test_num);
        }

    protected:
        bool OutputMatches(int test) {
            regex match(cout_answers_[test]);
            return regex_match(cout_buffer_.str(), match);
        }
        void LoadCinInputs(int test) {
            cin_buffer_ = istringstream(cin_inputs_[test]);
            cin.rdbuf(cin_buffer_.rdbuf());
        }
        void UndoCinRedirect() {
            cin.rdbuf(old_cin_buf_);
        }
        void RedirectOutput() {
            old_cout_buf_ = cout.rdbuf(cout_buffer_.rdbuf());
        }
        void UndoRedirectOutput() {
            cout.rdbuf(old_cout_buf_);
        }

        vector<string> cin_inputs_;
        vector<string> cout_answers_;

        stringstream cout_buffer_;
        istringstream cin_buffer_;
        streambuf* old_cout_buf_;
        streambuf* old_cin_buf_;
};

#endif  // IO_TESTER_H_
