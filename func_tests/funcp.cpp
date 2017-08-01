#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

template<int ...> struct seq {};

template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};

template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };


template <typename retType, typename... Args>
class MyFunc {
    public:
        MyFunc(retType (*f)(Args...)) {
            func_ = f;
        }
        void AddTest(retType ans, Args... inputs) {
            answers_.push_back(ans);
            input_argsets_.push_back(tuple<Args...>(inputs...));
        }
        void RunAllTests() {
            for (int i = 0; i < input_argsets_.size(); i++)
                cout << RunTest(i) << endl;
        }
        bool RunTest(int test_num) {
            return answers_[test_num] ==
                callFunc(test_num, typename gens<sizeof...(Args)>::type());
        }

        template<int ...S>
        retType callFunc(int test_num, seq<S...>) {
            return func_(get<S>(input_argsets_[test_num]) ...);
        }


    private:
        retType (*func_)(Args...);
        vector<tuple<Args...>> input_argsets_;
        vector<retType> answers_;
};

int Add2(int a, int b) {
    return a + b;
}

int Add5(int a, int b, int c, int d, int e) {
    return a + b + c + d + e;
}

int main(int argc, char* argv[]) {
    MyFunc<int, int, int> add2Tester(Add2);
    add2Tester.AddTest(5, 2, 3);
    add2Tester.AddTest(5, 2, 3);
    add2Tester.AddTest(5, 2, 3);

    MyFunc<int, int, int, int, int, int> add5Tester(Add5);
    add5Tester.AddTest(5, 2, 3, 0, 0, 0);
    add5Tester.AddTest(0, 2, 3, -3, -1, -1);
    add5Tester.AddTest(1, 2, 3, 2, 2, -1);
    
    cout << "Add 2 Tests:" << endl << "-------------------" << endl;
    add2Tester.RunAllTests();
    cout << "Add 5 Tests:" << endl << "-------------------" << endl;
    add5Tester.RunAllTests();

    return 0;
}
