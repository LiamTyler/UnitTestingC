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
        IOTester(string name, retType (*f)(Args...)) :
            FunctionTester<retType, Args...>(name, f) {}
        virtual void AddTest(string name, retType ans, string cin_in,
                string cout_ans, Args... inputs) {
            this->answers_.push_back(ans);
            this->input_argsets_.push_back(tuple<Args...>(inputs...));
            this->test_names_.push_back(name);
            this->test_results_.push_back(-1);
            cin_inputs_.push_back(cin_in);
            cout_answers_.push_back(cout_ans);
        }

        virtual bool RunTest(int test_num) {
            LoadCinInputs(test_num);
            RedirectOutput();

            retType ret = this->callFunc(test_num, typename gens<sizeof...(Args)>::type());
            UndoRedirectOutput();
            UndoCinRedirect();

            bool r = ret == this->answers_[test_num] && OutputMatches(test_num);
            if (r)
                this->test_results_[test_num] = 0;
            else
                this->test_results_[test_num] = 1;
            return r;
        }

    protected:
        bool OutputMatches(int test) {
            regex match(cout_answers_[test]);
            return regex_match(cout_buffer_.str(), match);
        }

        void LoadCinInputs(int test) {
            old_cin_buf_ = cin.rdbuf();
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

template<typename... Args>
class IOTester<void, Args...> : public FunctionTester<void, Args...> {
    typedef void (*func_ptr)(Args...);
    public:
        IOTester(string name, void (*f)(Args...)) :
            FunctionTester<void, Args...>(name, f) {}
        virtual void AddTest(string name, string cin_in,
                string cout_ans, Args... inputs) {
            this->input_argsets_.push_back(tuple<Args...>(inputs...));
            this->test_names_.push_back(name);
            this->test_results_.push_back(-1);
            cin_inputs_.push_back(cin_in);
            cout_answers_.push_back(cout_ans);
        }

        virtual bool RunTest(int test_num) {
            LoadCinInputs(test_num);
            RedirectOutput();

            this->callFunc(test_num, typename gens<sizeof...(Args)>::type());

            UndoRedirectOutput();
            UndoCinRedirect();

            if (OutputMatches(test_num)) { 
                this->test_results_[test_num] = 0;
                return true;
            } else {
                this->test_results_[test_num] = 1;
                return false;
            }
        }

    protected:
        bool OutputMatches(int test) {
            regex match(cout_answers_[test]);
            return regex_match(cout_buffer_.str(), match);
        }

        void LoadCinInputs(int test) {
            old_cin_buf_ = cin.rdbuf();
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

#endif  // SRC_INCLUDE_IO_TESTER_H_
