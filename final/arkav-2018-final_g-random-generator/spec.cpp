#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;
typedef long long LL;
const int MAXM = 2000000000;
const int AKAR = (int)sqrt(MAXM);

class ProblemSpec : public BaseProblemSpec {
protected:
  int P, Q, A_0;
  int M, X;

  int result;
  void InputFormat() {
    LINE(P, Q, A_0);
    LINE(M, X);
  }

  void OutputFormat() {
    LINE(result);
  }

  void GradingConfig() {
    TimeLimit(1);
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
  bool isPrime(int n){
    int akar = (int) sqrt(n);
    for(int i = 2;i <= akar; ++i) if(n % i == 0) return false;
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
    manual();

    ValidCases();
    InvalidCases();
    RandomCases();
    CASE(M = 999983; randomP(); randomQ(); randomInitialA(); randomX());
    CASE(M = 1999999973; randomP(); randomQ(); randomInitialA(); randomX());

  }

  void ValidCases(){
    CASE(M = 2; P = 0; Q = 0; X = 0; A_0 = 0);
    CASE(M = 2; P = 0; Q = 0; X = 0; A_0 = 1);
    CASE(M = 3; P = 0; Q = 1; X = 1; A_0 = 0);
    CASE(M = 2; P = 1; Q = 1; X = 1; A_0 = 1);
    CASE(M = 2; P = 1; Q = 0; X = 1; A_0 = 1);
    CASE(M = 1999999973; P = M - 1; Q = M - 1; X = 0; A_0 = 1);
    CASE(randomMBig(); P = M - 1; Q = M - 1; randomX(); A_0 = M - 2);
    CASE(M = 1999999973; P = 939711378; Q = 638950699; A_0 = 1915067939; X = 121790188);
  }

  void InvalidCases(){
    CASE(M = 2; P = 0; Q = 0; X = 1; A_0 = 0);
    CASE(M = 2; P = 0; Q = 1; X = 0; A_0 = 0);
    CASE(M = 1999999973; P = 0; Q = 1; X = 2; A_0 = 1);
    CASE(M = 999983; P = 423651; Q = 623558; A_0 = 645889; X = 384378);
  }

  void RandomCases(){
    for(int i = 0;i <= 20; ++i) {
      CASE(randomMSmall(); randomP(); randomQ(); randomInitialA(); randomX());
    }
    for(int i = 0;i <= 20; ++i) {
      CASE(randomMBig(); randomP(); randomQ(); randomInitialA(); randomX());
    }
    CASE(M = 1000000007; randomP(); randomQ(); randomInitialA(); randomX());
  }


private:
  vector<int> pnum_small;
  vector<int> pnum_big;
  bitset<AKAR + 5> prim;
  void sieve(){
    pnum_small.clear();
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
        pnum_small.push_back(i);
      }
    }
  }

  void manual(){
    vector<int> v_prime = {103054759,1036815239,1731205687,949365763,231710569,1781653871,384535201,910816493,166809557,1788229561,75991417,1749838897,1234060573,1264055227,1165896401,1125943957,481714627,1107907763,180115931,1835501963,1361691623,1642037591,122769707,4226939,642338803,1440528769,1604799877,377420093,558246803,524304241,610851407,992749333,582106631,1225861081,25127087,1711305727,285014123,1304550983,1832856587,1380609869,1882316393,1475375047,420910453,1506771389,477464527,286665811,1514128559,81141491,275270197,56520253,1525353113,668610497,1157761279,697469243,1577039993,1486285649,78292147,1965424039,403435727,213977789,1697364041,936116527,1183685147,1992015679,563628641,1380426919,6499903,1581205469,803060969,1647747653,434803079,76722637,628202557,606314179,1805530561,1444801273,166726363,1696785199,1090315631,898940281,1846786597,570014287,1760830843,1241887133,765831761,1058775383,674738747,363046003,866417159,506081711,1863437959,1980853619,1539007199,107874587,90227833,1007937991,1251995429,643349051,109777817,842499113,1710245179,714893723};
    pnum_big = v_prime;
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
    int idx = rnd.nextInt((int)pnum_small.size());
    M = pnum_small[idx];
  }

  void randomMBig(){
    int idx = rnd.nextInt((int)pnum_big.size());
    M = pnum_big[idx];
  }

};