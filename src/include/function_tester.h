#ifndef SRC_INCLUDE_FUNCTION_TESTER_H_
#define SRC_INCLUDE_FUNCTION_TESTER_H_

#include "include/tester.h"
#include <tuple>
#include <vector>
#include <utility>

using namespace std;

template<int ...> struct seq {};

template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};

template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };

 
namespace aux{
template<std::size_t...> struct seq{};
 
template<std::size_t N, std::size_t... Is>
struct gen_seq : gen_seq<N-1, N-1, Is...>{};
 
template<std::size_t... Is>
struct gen_seq<0, Is...> : seq<Is...>{};
 
template<class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple(std::basic_ostream<Ch,Tr>& os, Tuple const& t, seq<Is...>){
  using swallow = int[];
  (void)swallow{0, (void(os << (Is == 0? "" : ", ") << std::get<Is>(t)), 0)...};
}
} // aux::
 
template<class Ch, class Tr, class... Args>
auto operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t)
    -> std::basic_ostream<Ch, Tr>&
{
  os << "(";
  aux::print_tuple(os, t, aux::gen_seq<sizeof...(Args)>());
  return os << ")";
}

template <typename retType, typename... Args>
class FunctionTester : public Tester {
    typedef retType (*func_ptr)(Args...);

    public:
        FunctionTester(string name, func_ptr f) : Tester(name) {
            func_ = f;
        }
        virtual void AddTest(string test_name, retType ans, Args... inputs) {
            answers_.push_back(ans);
            test_names_.push_back(test_name);
            test_results_.push_back(-1);
            input_argsets_.push_back(tuple<Args...>(inputs...));
        }
        virtual void RunAllTests() {
            for (int i = 0; i < input_argsets_.size(); i++)
                RunTest(i);
        }
        virtual bool RunTest(int test_num) {
            bool ret = answers_[test_num] ==
                callFunc(test_num, typename gens<sizeof...(Args)>::type());
            if (ret) {
                test_results_[test_num] = 0;
            } else {
                test_results_[test_num] = 1;
            }
            return ret;
        }

        virtual void PrintTestInfo(ostream& out, int test) {
            out << "\tFunction Inputs: " << input_argsets_[test] << endl;
            out << "\tExpected Return: " << answers_[test] << endl;
            Tester::PrintTestInfo(out, test);
        }

        template<int ...S>
        retType callFunc(int test_num, seq<S...>) {
            return func_(get<S>(input_argsets_[test_num]) ...);
        }

        void SetFunction(func_ptr f) { func_ = f; }
        func_ptr GetFunction() { return func_; }

    protected:
        retType (*func_)(Args...);
        vector<tuple<Args...>> input_argsets_;
        vector<retType> answers_;
        vector<retType> return_vals_;
};

template <typename... Args>
class FunctionTester<void, Args...> : public Tester {
    typedef void (*func_ptr)(Args...);

    public:
        FunctionTester(string name, func_ptr f) : Tester(name) {
            func_ = f;
        }
        virtual void AddTest(string test_name, Args... inputs) {
            test_names_.push_back(test_name);
            test_results_.push_back(-1);
            input_argsets_.push_back(tuple<Args...>(inputs...));
        }
        virtual void RunAllTests() {
            for (int i = 0; i < input_argsets_.size(); i++)
                RunTest(i);
        }
        virtual bool RunTest(int test_num) {
            callFunc(test_num, typename gens<sizeof...(Args)>::type());
            return true;
        }

        virtual void PrintTestInfo(ostream& out, int test) {
            out << "\tFunction Inputs: " << input_argsets_[test] << endl;
            Tester::PrintTestInfo(out, test);
        }

        template<int ...S>
        void callFunc(int test_num, seq<S...>) {
            func_(get<S>(input_argsets_[test_num]) ...);
        }

        void SetFunction(func_ptr f) { func_ = f; }
        func_ptr GetFunction() { return func_; }

    protected:
        void (*func_)(Args...);
        vector<tuple<Args...>> input_argsets_;
};

#endif  // SRC_INCLUDE_FUNCTION_TESTER_H_
