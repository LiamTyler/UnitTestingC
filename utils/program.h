#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <string>

using std::string;

class Program {
    public:
        explicit Program(string fname);
        ~Program();
        bool Compile();
        bool Externify();
        bool RenameMain();
        bool MakeLibrary();
        bool OpenLib();
        void CloseLib();
        bool FullPrepare();
        void * GetFunction(string func);

    private:
        string filename_;
        bool compiles_;
        bool externed_;
        bool renamed_main_;
        bool library_created_;
        void* lib_handle_;
};

#endif  // PROGRAM_H_

