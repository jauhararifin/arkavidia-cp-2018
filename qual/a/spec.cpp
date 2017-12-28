#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;
    int N;
    vector<int> A;
    long long result;

    void InputFormat() {
        LINE(N, A);
    }

    void OutputFormat() {
        LINE(result);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(32);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
        OutputPrefix("");
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 100);
    }

    void Constraints() {
        CONS(1 <= N <= 100000);
        CONS(eachElementBetween(A, 1, 1000000));
    }
private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        for (long long x : v)
            if (x < lo || x > hi)
                return 0;
        return 1;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "5 1 2 3 4 5"
        });
        Output({
            "10"
        });
    }

    void SampleTestCase2() {
        Input({
            "3 7 2 5"
        });
        Output({
            "8"
        });
    }

    void SampleTestCase3() {
        Input({
            "10 7 7 7 7 7 7 7 7 7 7"
        });
        Output({
            "0"
        });
    }

    void BeforeTestCase() {
        A.clear();
    }

    void TestCases() {
        CASE(N = 1, A = {1000000});
        CASE(N = 1, A = {1});
        CASE(N = 1, A = {rand()%1000000+1});
        CASE(N = 5000, sameNumber(1));
        CASE(N = 5000, sameNumber(1000000));
        CASE(N = 5000, sameNumber(rand()%1000000+1));
        CASE(N = 100000, sameNumber(1000000));
        CASE(N = 100000, sameNumber(928472));
        CASE(N = 100000, sameNumber(1));
        CASE(N = 100, numberAbove(5));
        CASE(N = 100, numberAbove(528271));
        CASE(N = 100, numberAbove(999999));
        CASE(N = 10000, numberAbove(102));
        CASE(N = 10000, numberAbove(294172));
        CASE(N = 10000, numberAbove(999999));
        CASE(N = 100000, numberAbove(712));
        CASE(N = 100000, numberAbove(123794));
        CASE(N = 100000, numberAbove(999999));
        CASE(N = 100, randomElement());
        CASE(N = 100, randomElement());
        CASE(N = 100, randomElement());
        CASE(N = 10000, randomElement());
        CASE(N = 10000, randomElement());
        CASE(N = 100000, randomElement());
        CASE(N = rand()%100000 + 1, randomElement());
        CASE(N = rand()%100000 + 1, randomElement());
        CASE(N = rand()%100000 + 1, randomElement());
    }

private:
    mt19937 mersenne = mt19937(0xdead);

    void sameNumber(int x) {
        for (int i = 0; i < N; i++)
            A.push_back(x);
        random_shuffle(A.begin(), A.end());
    }
    void numberAbove(int x) {
        for (int i = 0; i < N; i++)
            A.push_back(x + mersenne() % (1000000-x));
        random_shuffle(A.begin(), A.end());
    }
    void randomElement() {
        for (int i = 0; i < N; i++)
            A.push_back(mersenne()%1000000+1);
        random_shuffle(A.begin(), A.end());
    }
};