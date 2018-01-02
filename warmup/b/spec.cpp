#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;
    long long N,result;

    void InputFormat() {
        LINE(N);
    }

    void OutputFormat() {
        LINE(result);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
        OutputPrefix("");
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 1000);
    }

    void Constraints() {
        CONS(1 <= N <= 1000);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "1"
        });
        Output({
            "1"
        });
    }

    void SampleTestCase2() {
        Input({
            "5"
        });
        Output({
            "5"
        });
    }

    void TestCases() {
        vector<int> a;
        for (int i = 1; i <= 1000; i++)
            a.push_back(i);
        random_shuffle(a.begin(), a.end());
        for (int i = 0; i < 1000; i++)
            CASE(N = a[i]);
    }
};