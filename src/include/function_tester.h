#include <tuple>
#include <vector>

using namespace std;

template<int ...> struct seq {};

template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};

template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };


template <typename retType, typename... Args>
class FunctionTester {
    public:
        FunctionTester(retType (*f)(Args...)) {
            func_ = f;
        }
        virtual void AddTest(retType ans, Args... inputs) {
            answers_.push_back(ans);
            input_argsets_.push_back(tuple<Args...>(inputs...));
        }
        virtual void RunAllTests() {
            for (int i = 0; i < input_argsets_.size(); i++)
                RunTest(i);
        }
        virtual bool RunTest(int test_num) {
            return answers_[test_num] ==
                callFunc(test_num, typename gens<sizeof...(Args)>::type());
        }

        template<int ...S>
        retType callFunc(int test_num, seq<S...>) {
            return func_(get<S>(input_argsets_[test_num]) ...);
        }


    protected:
        retType (*func_)(Args...);
        vector<tuple<Args...>> input_argsets_;
        vector<retType> answers_;
};
