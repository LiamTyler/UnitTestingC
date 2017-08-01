#include "include/function_tester.h"

using namespace std;

/*
template<int ...> struct seq {};

template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};

template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };
*/

template <typename retType, typename... Args>
FunctionTester<retType, Args...>::FunctionTester(func_ptr f) {
    func_ = f;
}

template <typename retType, typename... Args>
void FunctionTester<retType, Args...>::AddTest(retType ans, Args... inputs) {
    answers_.push_back(ans);
    input_argsets_.push_back(tuple<Args...>(inputs...));
}

template <typename retType, typename... Args>
void FunctionTester<retType, Args...>::RunAllTests() {
    for (int i = 0; i < input_argsets_.size(); i++)
        RunTest(i);
}

template <typename retType, typename... Args>
bool FunctionTester<retType, Args...>::RunTest(int test_num) {
    return answers_[test_num] ==
        callFunc(test_num, typename gens<sizeof...(Args)>::type());
}

template <typename retType, typename... Args>
    template<int ...S>
retType FunctionTester<retType, Args...>::callFunc(int test_num, seq<S...>) {
    return func_(get<S>(input_argsets_[test_num]) ...);
}

