#ifndef IO_TESTER_H_
#define IO_TESTER_H_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

class IOTester {
    public:
        IOTester();
        void SetCinInputs(std::string inputs) { cin_inputs_ = inputs; }
        void SetArgs(std::vector<std::string> args);
        void ClearArgv();
        void SetExpectedAnswer(std::string regex) { regex_ = regex; }
        int Test(std::string filename);

    private:
        void LoadArgs();
        void LoadCinInputs();
        void UndoCinRedirect();
        void RedirectOutput();
        void UndoRedirectOutput();

        std::vector<std::string> args_;
        int argc_;
        char** argv_;
        std::string cin_inputs_;
        std::string regex_;
        int exit_code_;

        std::stringstream cout_buffer_;
        std::istringstream cin_buffer_;
        std::streambuf* old_cout_buf_;
        std::streambuf* old_cin_buf_;

};

#endif  // IO_TESTER_H_
