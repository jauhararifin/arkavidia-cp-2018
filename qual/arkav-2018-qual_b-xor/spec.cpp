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
        TimeLimit(2);
        MemoryLimit(256);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
        OutputPrefix("");
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 200000);
    }

    void Constraints() {
        CONS(1 <= L <= R <= 1000000000000000000LL);
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

    void SampleTestCase4() {
        Input({
            "1 1"
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
        CASE(L = 999999999999999995, R = 1000000000000000000);
        CASE(L = 999999999999999994, R = 1000000000000000000);
        CASE(L = 999999999999999993, R = 1000000000000000000);
        CASE(L = 999999999999999992, R = 1000000000000000000);
        CASE(L = 999999999999999991, R = 1000000000000000000);
        CASE(L = 999999999999999990, R = 1000000000000000000);
        CASE(L = 999999999999999989, R = 1000000000000000000);
        CASE(L = 999999999999999988, R = 1000000000000000000);
        CASE(L = 288230376151711743, R = 288230376151711744);
        CASE(L = 288230376151711743, R = 288230376151711745);
        CASE(L = 288230376151711743, R = 288230376151711746);
        CASE(L = 288230376151711743, R = 288230376151711747);
        CASE(L = 288230376151711743, R = 288230376151711748);
        CASE(L = 288230376151711743, R = 288230376151711749);
        CASE(L = 288230376151711743, R = 288230376151711750);
        CASE(L = 288230376151711743, R = 288230376151711751);
        CASE(L = 288230376151711743, R = 288230376151711752);
        CASE(L = 288230376151711743, R = 288230376151711753);
        CASE(L = 288230376151711743, R = 288230376151711754);
        CASE(L = 288230376151711743, R = 288230376151711755);
        CASE(L = 288230376151711742, R = 288230376151711743);
        CASE(L = 288230376151711741, R = 288230376151711743);
        CASE(L = 288230376151711740, R = 288230376151711743);
        CASE(L = 288230376151711739, R = 288230376151711743);
        CASE(L = 288230376151711738, R = 288230376151711743);
        CASE(L = 288230376151711737, R = 288230376151711743);
        CASE(L = 288230376151711736, R = 288230376151711743);
        CASE(L = 288230376151711735, R = 288230376151711743);
        CASE(L = 288230376151711734, R = 288230376151711743);
        CASE(L = 288230376151711733, R = 288230376151711743);
        CASE(L = 288230376151711732, R = 288230376151711743);
        CASE(L = 288230376151711731, R = 288230376151711743);
        CASE(L = 382171928734723100, R = 382171928734723100);
        CASE(L = 382171928734723100, R = 382171928734723101);
        CASE(L = 382171928734723100, R = 382171928734723102);
        CASE(L = 382171928734723100, R = 382171928734723103);
        CASE(L = 382171928734723100, R = 382171928734723104);
        CASE(L = 382171928734723100, R = 382171928734723105);
        CASE(L = 382171928734723100, R = 382171928734723106);
        CASE(L = 382171928734723100, R = 382171928734723107);
        CASE(L = 382171928734723100, R = 382171928734723108);
        CASE(L = 382171928734723100, R = 382171928734723109);
        CASE(L = 382171928734723100, R = 382171928734723110);
        CASE(L = 382171928734723100, R = 382171928734723111);
        
        CASE(L = 1, R = 1);
        CASE(L = 2, R = 2);
        CASE(L = 3, R = 3);
        CASE(L = 4, R = 4);
        CASE(L = 5, R = 5);
        CASE(L = 9, R = 9);
        CASE(L = 25, R = 25);
        CASE(L = 100, R = 100);
        CASE(L = 826, R = 826);
        CASE(L = 827, R = 827);
        CASE(L = 828, R = 828);
        CASE(L = 829, R = 829);
        CASE(L = 230376151, R = 230376151);
        CASE(L = 230376152, R = 230376152);
        CASE(L = 230376153, R = 230376153);
        CASE(L = 230376154, R = 230376154);
        CASE(L = 38217192873472, R = 38217192873472);
        CASE(L = 38217192873472, R = 38217192873472);

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