#include <iostream>
#include <dlfcn.h>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    void* lib_handle;
    double (*fn)(double);
    lib_handle = dlopen("./libsqrt.so", RTLD_LAZY);
    if (!lib_handle) {
        cerr << dlerror() << endl;
        exit(1);
    }
    fn = (double (*)(double))dlsym(lib_handle, "sqrt2");
    char* error;
    if ((error = dlerror()) != NULL) {
        cerr << error << endl;
        exit(1);
    }
    double x = (*fn)(9);
    cout << x << endl;

    dlclose(lib_handle);

    return 0;
}
