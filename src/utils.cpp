#include "include/utils.h"
#include <regex>
#include <iostream>
#include <fstream>

using namespace std;

bool rename_main(string& filename) {
    ifstream in(filename.c_str());
    if (in.fail()) {
        cout << "Failed to open intput file" << endl;
        return false;
    }

    filename = "renamed_" + filename;
    ofstream out(filename.c_str());
    if (out.fail()) {
        cout << "Failed to open output file" << endl;
        return false;
    }

    string in_line;

    smatch sm;
    regex main("(.*)int main\\(.*\\)(.*)");
    while(getline(in, in_line)) {
        if (regex_match(in_line, sm, main)) {
            out << sm[1] << "int student_main(int argc, char** argv)" << sm[2] << endl;
        } else {
            out << in_line << endl;
        }
    }

    in.close();
    out.close();
    return true;
}

bool externify(string& filename) {
    ifstream in(filename.c_str());
    if (in.fail())
        return false;

    int last_include = 0;
    int line_num = 0;
    string line;
    while (getline(in, line)) {
        if (line.find("#include") != string::npos)
            last_include = line_num;
        line_num++;
    }
    in.clear();
    in.seekg(0, ios::beg);

    filename = "externed_" + filename;
    ofstream out(filename.c_str());
    if (out.fail())
        return false;
    line_num = 0;
    while (getline(in, line)) {
        out << line << endl;
        if (line_num == last_include)
            out << "extern \"C\"{" << endl;
        line_num++;
    }
    out << "}" << endl;
    in.close();
    out.close();
    return true;
}
