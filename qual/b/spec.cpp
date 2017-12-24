#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

#define ull unsigned long long

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;
    long long L, R, result;

    void InputFormat() {
        LINE(L, R);
    }

    void OutputFormat() {
        LINE(result);
    }

    void GradingConfig() {
        TimeLimit(0.5);
        MemoryLimit(16);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
        OutputPrefix("");
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 200000);
    }

    void Constraints() {
        CONS(1 <= L < R <= 1000000000000000000LL);
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
            "7 10"
        });
        Output({
            "12"
        });
    }

    void SampleTestCase3() {
        Input({
            "100 101"
        });
        Output({
            "1"
        });
    }

    void TestCases() {
        CASE(L = 1, R = 2);
        CASE(L = 999999999999999999, R = 1000000000000000000);
        CASE(L = 999999999999999998, R = 1000000000000000000);
        CASE(L = 999999999999999997, R = 1000000000000000000);
        CASE(L = 999999999999999996, R = 1000000000000000000);
        CASE(L = 288230376151711743, R = 288230376151711744);
        CASE(L = 288230376151711743, R = 288230376151711745);
        CASE(L = 288230376151711743, R = 288230376151711746);
        CASE(L = 288230376151711743, R = 288230376151711747);
        CASE(L = 288230376151711742, R = 288230376151711743);
        CASE(L = 288230376151711741, R = 288230376151711743);
        CASE(L = 288230376151711740, R = 288230376151711743);
        CASE(L = 288230376151711739, R = 288230376151711743);

        for (long long i = 0; i <= 100; i++)
            for (long long j = 0; j <= 100; j++)
                CASE(L = 1 + i, R = 1000000000000000000 - j);

        for (long long i = 0; i <= 10; i++)
            for (long long j = 0; j <= 10; j++)
                CASE(L = 144115188075855871 + i, R = 288230376151711743 - j);

        for (long long i = 0; i <= 10; i++)
            for (long long j = 0; j <= 10; j++)
                CASE(L = 159202181970746799 + i, R = 529566899057755602 - j);

        for (long long i = 0; i <= 1000; i++)
            for (long long j = 0; j <= 100; j++)
                CASE(L = 297379960876591172 + i, R = 801972410549895275 - j);
    }
};