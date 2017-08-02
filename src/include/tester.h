#ifndef SRC_INCLUDE_TESTER_H_
#define SRC_INCLUDE_TESTER_H_

#include <iostream>
#include <string>
#include <vector>

class Tester {
    public:
        Tester();
        Tester(std::string name);
        virtual ~Tester() {}
        virtual void PrintTestInfo(std::ostream& out, int test);
        virtual void GetSummary(std::ostream& out);

        std::string GetTesterName() { return name_; }
        int GetTestResult(int i) { return test_results_[i]; }
        std::string GetTestName(int i) { return test_names_[i]; }

    protected:
        std::string name_;
        std::vector<std::string> test_names_;
        std::vector<int> test_results_;
};

#endif  // SRC_INCLUDE_TESTER_H_

