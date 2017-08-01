#include "include/io_tester.h"

using namespace std;

template<typename retType, typename... Args>
IOTester<retType, Args...>::IOTester(retType (*f)(Args...)) :
    FunctionTester<retType, Args...>(f) {

}

template<typename retType, typename... Args>
void IOTester<retType, Args...>::AddTest(retType ans, Args... inputs,
        string cin_in, string cout_ans) {
    this->answers_.push_back(ans);
    this->input_argsets_.push_back(tuple<Args...>(inputs...));
    cin_inputs_.push_back(cin_in);
    cout_answers_.push_back(cout_ans);
}

template<typename retType, typename... Args>
bool IOTester<retType, Args...>::RunTest(int test_num) {
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

template<typename retType, typename... Args>
bool IOTester<retType, Args...>::OutputMatches(int test) {
    regex match(cout_answers_[test]);
    return regex_match(cout_buffer_.str(), match);
}

template<typename retType, typename... Args>
void IOTester<retType, Args...>::LoadCinInputs(int test) {
    cin_buffer_ = istringstream(cin_inputs_[test]);
    cin.rdbuf(cin_buffer_.rdbuf());
}

template<typename retType, typename... Args>
void IOTester<retType, Args...>::UndoCinRedirect() {
    cin.rdbuf(old_cin_buf_);
}

template<typename retType, typename... Args>
void IOTester<retType, Args...>::RedirectOutput() {
    old_cout_buf_ = cout.rdbuf(cout_buffer_.rdbuf());
}

template<typename retType, typename... Args>
void IOTester<retType, Args...>::UndoRedirectOutput() {
    cout.rdbuf(old_cout_buf_);
}
