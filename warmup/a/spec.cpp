#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;
    long long A,B,result;

    void InputFormat() {
        LINE(A, B);
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
        CONS(1 <= T && T <= 100);
    }

    void Constraints() {
        CONS(-1000000000 <= A <= 1000000000);
        CONS(-1000000000 <= B <= 1000000000);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "1 2"
        });
        Output({
            "3"
        });
    }

    void SampleTestCase2() {
        Input({
            "3 4"
        });
        Output({
            "7"
        });
    }

    void TestCases() {
        CASE(A = -1000000000, B = 0);
        CASE(A = 1000000000, B = 0);
        CASE(A = 0, B = 0);
        CASE(A = -1000000000, B = -1000000000);
        CASE(A = 1000000000, B = -1000000000);
        CASE(A = 0, B = -1000000000);
        CASE(A = -1000000000, B = 1000000000);
        CASE(A = 1000000000, B = 1000000000);
        CASE(A = 0, B = 1000000000);
        for (int i = 0; i < 100-9; i++)
            CASE(A = randomNumber(), B = randomNumber());
    }

private:
    mt19937 mersenne = mt19937(0xdead);

    long long randomNumber() {
        return (abs((int) mersenne()) % 2000000001) - 1000000000;
    }
};