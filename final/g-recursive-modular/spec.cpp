#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;
typedef long long LL;
const LL MAXM = 1000000000000LL;
const int AKAR = (int)sqrt(MAXM);

class ProblemSpec : public BaseProblemSpec {
protected:
  LL P, Q, A_0;
  LL M, X;

  LL result;
  void InputFormat() {
    LINE(P, Q, A_0);
    LINE(M, X);
  }

  void OutputFormat() {
    LINE(result);
  }

  void GradingConfig() {
    // Berapa nih?
    TimeLimit(2);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(2 <= M && M <= MAXM);
    CONS(isPrime(M));
    CONS(0 <= P && P < M);
    CONS(0 <= Q && Q < M);
    CONS(0 <= A_0 && A_0 < M);
    CONS(0 <= X && X < M); 
  }


private:
  bool isPrime(LL n){
    LL akar = (int) sqrt(n);
    for(LL i = 2;i <= akar; ++i) if(n % i == 0) return false;
    return true; 
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Input({
      "2 1 5",
      "7 2"
    });
    Output({
      "2"
    });
  }

  void SampleTestCase2() {
    Input({
      "2 0 2",
      "7 3"
    });
    Output({
      "-1"
    });
  }

  void SampleTestCase3() {
    Input({
      "7 9 5",
      "11 5"
    });
    Output({
      "0"
    });
  }

  void TestCases() {
    sieve();
    CASE(M = 2; randomP(); randomQ(); randomInitialA(); randomX());
    CASE(M = 3; randomP(); randomQ(); randomInitialA(); randomX());
    CASE(M = 999999999989LL; randomP(); randomQ(); randomInitialA(); randomX());
    CASE(M = 999983; randomP(); randomQ(); randomInitialA(); randomX());
    CASE(M = 2147483647; randomP(); randomQ(); randomInitialA(); randomX());
    CASE(M = 1000000007; randomP(); randomQ(); randomInitialA(); randomX());
    CASE(M = 2147483659LL; randomP(); randomQ(); randomInitialA(); randomX());
    CASE(M = 127; P = 0; Q = 0; A_0 = 0; X = 0);
    CASE(M = 999999999989LL; P = 0; Q = 0LL; A_0 = 0; X = 0);
    CASE(M = 999999999989LL; P = 0; Q = 0LL; randomX(); A_0 = X);
    CASE(M = 2; P = 0; Q = 0LL; randomX(); A_0 = X);    
    for(int i = 0;i <= 10; ++i) CASE(randomMSmall(); randomP(); randomQ(); randomInitialA(); randomX());

  }

private:
  vector<int> pnum;
  bitset<AKAR + 5> prim;
  void sieve(){
    pnum.clear();
    prim.set();
    prim[0] = prim[1] = false;
    for(int i = 2;i <= AKAR; ++i){
      if(prim[i]){
        int limits = (int) sqrt(AKAR);
        if(i <= limits){
          int now = i * i;
          while(now <= AKAR){
            prim[now] = false;
            now += i;
          }
        }
        pnum.push_back(i);
      }
    }
  }

  void randomP(){
    P = rnd.nextLongLong(0, M - 1);
  }
  void randomQ(){
    Q = rnd.nextLongLong(0, M - 1);
  }
  void randomX(){
    X = rnd.nextLongLong(0, M - 1);
  }
  void randomInitialA(){
    A_0 = rnd.nextLongLong(0, M - 1);
  }

  void randomMSmall(){
    int idx = rnd.nextInt((int)pnum.size());
    M = pnum[idx];
  }

};