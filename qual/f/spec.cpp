#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T, N, Q;
    vector<int> a,b,c,r;

    void InputFormat() {
        LINE(N);
        LINE(a);
        LINE(b);
        LINE(Q);
        LINES(c) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(c) % SIZE(Q);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
        OutputPrefix("");
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 10);
    }

    void Constraints() {
        CONS(1 <= N <= 100000);
        CONS(1 <= Q <= 100000);
        for (int x : a)
            CONS(1 <= x <= 100000);
        for (int x : b)
            CONS(1 <= x <= 100000);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "5",
            "1 6 2 3 4",
            "8 2 4 5 7",
            "3",
            "3",
            "6",
            "5"
        });
        Output({
            "1",
            "3",
            "2"
        });
    }

    void TestCases() {
    }
};