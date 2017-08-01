#include "program.h"
#include "utils.h"
#include <cstdlib>
#include <iostream>
#include <dlfcn.h>

using namespace std;

Program::Program(string fname) {
    filename_ = fname;
    compiles_ = false;
    externed_ = false;
    renamed_main_ = false;
    library_created_ = false;
    lib_handle_ = nullptr;
}

Program::~Program() {
    CloseLib();
}

bool Program::Compile() {
    string command = "g++ -std=c++11 " + filename_ + " > /dev/null 2>&1";
    int ret = 0;
    ret = system(command.c_str());
    compiles_ = (ret == 0);
    return compiles_;
}

bool Program::Externify() {
    externed_ = externify(filename_);
    return externed_;
}

bool Program::RenameMain() {
    renamed_main_ = rename_main(filename_);
    return renamed_main_;
}

bool Program::MakeLibrary() {
    library_created_ = false;
    if (!compiles_)
        return false;

    // Get the name of the object file that will be created
    int end = filename_.find(".c");
    if (end == 0 || end == string::npos)
        return false;
    string ofile = filename_.substr(0, end) + ".o";

    // Build the .o file
    string command = "g++ -std=c++11 -fPIC -c " + filename_ +\
                      " > /dev/null 2>&1";

    int ret = 0;
    ret = system(command.c_str());
    if (ret)
        return false;

    // Build the .so file (named 'libcurtest.so')
    command = "g++ -shared -Wl,-soname,libcurtest.so -o libcurtest.so " +\
               ofile + " > /dev/null 2>&1";
    ret = system(command.c_str());
    if (ret)
        return false;
    library_created_ = true;

    return library_created_;
}

bool Program::OpenLib() {
    if (!lib_handle_)
        lib_handle_ = dlopen("./libcurtest.so", RTLD_LAZY);

    return lib_handle_;
}

void Program::CloseLib() {
    if (lib_handle_)
        dlclose(lib_handle_);
}

void* Program::GetFunction(string func) {
    char* error;
    void* ret = dlsym(lib_handle_, func.c_str());
    if ((error = dlerror()) != NULL)
        return nullptr;

    return ret;
}

bool Program::FullPrepare() {
    return (Compile() && Externify() && RenameMain() &&
            MakeLibrary() && OpenLib());
}

/*
int main() {
    Program p("sqrt.cpp");
    if (p.FullPrepare()) {
        typedef double (*sqrt)(double);
        sqrt fn = (sqrt) p.GetFunction("sqrt");
        cout << "sqrt(9): " << (*fn)(9) << endl;
    } else {
        cout << "Did not pass full prepare" << endl;
    }

    return 0;
}
*/
