#ifndef SRC_INCLUDE_FUNCTION_TESTER_H_
#define SRC_INCLUDE_FUNCTION_TESTER_H_

#include <tuple>
#include <vector>

using namespace std;

template<int ...> struct seq {};

template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};

template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };

template <typename retType, typename... Args>
class FunctionTester {
    typedef retType (*func_ptr)(Args...);

    public:
        FunctionTester(func_ptr f);
        virtual void AddTest(retType ans, Args... inputs);
        virtual void RunAllTests();
        virtual bool RunTest(int test_num);

        template<int ...S>
        retType callFunc(int test_num, seq<S...>);

        void SetFunction(func_ptr f) { func_ = f; }
        func_ptr GetFunction() { return func_; }


    protected:
        retType (*func_)(Args...);
        vector<tuple<Args...>> input_argsets_;
        vector<retType> answers_;
};

#endif  // SRC_INCLUDE_FUNCTION_TESTER_H_
