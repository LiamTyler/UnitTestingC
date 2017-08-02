#include "include/tester.h"

using namespace std;

Tester::Tester() {
    name_ = "Default Tester";
}

Tester::Tester(string name) {
    name_ = name;
}

void Tester::PrintTestInfo(ostream& out, int test) {
    string res = "";
    switch(test_results_[test]) {
        case -1:
            res = "Not run";
            break;
        case 0:
            res = "Passed";
            break;
        case 1:
            res = "Failed";
            break;
        case 2:
            res = "Crashed";
            break;
    }
    out << "\tResult: " << res << endl << endl;
}


void Tester::GetSummary(ostream& out) {
    string title = "[=== START TEST: " + name_ + " ===]";
    string dash(title.length(), '-');
    out << title << endl;
    int sum = 0;
    for (int i = 0; i < test_results_.size(); i++) {
        out << "Test Case #" << i << " : \"" << test_names_[i] << "\"" << endl;
        out << dash << endl;
        PrintTestInfo(out, i);
        sum += (int) test_results_[i] == 1;
    }
    out << endl;
    out << "Final Summary: " << sum << "/" << test_results_.size() << " Passed" << endl;
    out << endl;
    string end = "[=== END TEST: " + name_ + " ===]";
    out << end << endl;
    out << endl;
}
