#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
  int T;
  int N, Q;
  vector<int> A, X;

  vector<long long> ans;

  void InputFormat() {
    LINE(N, Q);
    LINE(A);
    LINES(X) % SIZE(Q);
  }

  void OutputFormat() {
    LINES(ans) % SIZE(Q);
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
    CONS(1 <= T && T <= 10);
  }

  void Constraints() {
    CONS(1 <= N && N <= 200000);
    CONS(1 <= Q && Q <= 200000);
    CONS(eachElementBetween(A, 1, 200000));
    CONS(eachElementBetween(X, 1, 1000000000));
    CONS(N == A.size());
    CONS(Q == X.size());
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
      "5 3",
      "1 100 7 33 20",
      "1",
      "5",
      "123456789"
    });
    Output({
      "0",
      "14",
      "11539"
    });
  }

  void BeforeTestCase() {
    A.clear();
    X.clear();
    ans.clear();
  }

  void AfterTestCase() {
    random_shuffle(begin(A), end(A));
    random_shuffle(begin(X), end(X));
  }

  void TestGroup1() {
    // all number, all divide
    CASE(N = 10, Q = 10, A = complete_array(N), X = complete_array(Q));
    CASE(N = 1000, Q = 1000, A = complete_array(N), X = complete_array(Q));

    // all number, divide small
    CASE(N = 10, Q = 10, A = complete_array(N), X = same_array(Q, 1));
    CASE(N = 1000, Q = 10, A = complete_array(N), X = same_array(Q, 5));
    CASE(N = 2000, Q = 100, A = complete_array(N), X = random_array(Q, 50, 100));
    CASE(N = 500, Q = 2000, A = complete_array(N), X = random_array(Q, 100, N));
    CASE(N = 1234, Q = 100, A = complete_array(N), X = random_array(Q, 1, 10));
    CASE(N = 1000, Q = 1000, A = complete_array(N), X = random_array(Q, 1, N));
    CASE(N = 2000, Q = 500, A = complete_array(N), X = prime_array(Q, 1, N));

    // all number, divide large
    CASE(N = 5000, Q = 10, A = complete_array(N), X = same_array(Q, N - 1));
  }

  void TestGroup2() {
    // complete tc
    CASE(N = 200000, Q = 200000, A = complete_array(N), X = complete_array(Q));
    
    // all number, divide large
    CASE(N = 50000, Q = 10, A = complete_array(N), X = same_array(Q, N));
    CASE(N = 20000, Q = 1000, A = complete_array(N), X = random_array(Q, N / 2, N));

    // all number, divide large prime
    CASE(N = 10000, Q = 100, A = complete_array(N), X = prime_array(Q, 9000, 10000));
    CASE(N = 50000, Q = 100, A = complete_array(N), X = prime_array(Q, 40000, 50000));

    // all number, divide > MAX
    CASE(N = 100000, Q = 10, A = complete_array(N), X = random_array(Q, N + 1, 1000000000));

    // big number, all divide
    CASE(N = 10, Q = 10, A = random_array(N, 150000, 200000), X = complete_array(Q));
    CASE(N = 1000, Q = 1000, A = random_array(N, 199990, 200000), X = complete_array(Q));
    CASE(N = 500, Q = 50000, A = same_array(N, 200000), X = complete_array(Q));

    // big number, divide small
    CASE(N = 100, Q = 50, A = random_array(N, 150000, 200000), X = random_array(Q, 1, 10));
  }

  void TestGroup3() {
    // big number, divide small
    CASE(N = 1000, Q = 1000, A = random_array(N, 150000, 200000), X = random_array(Q, 1, 200));

    // big number, divide large
    CASE(N = 1000, Q = 50000, A = random_array(N, 150000, 200000), X = random_array(Q, 150000, 200000));

    // big number, divide large prime
    CASE(N = 2000, Q = 12345, A = random_array(N, 150000, 200000), X = prime_array(Q, 150000, 200000));

    // prime number, all divide
    CASE(N = 10000, Q = 10000, A = prime_array(N, 150000, 200000), X = complete_array(Q));

    // prime number, divide small
    CASE(N = 5000, Q = 200, A = prime_array(N, 150000, 200000), X = random_array(Q, 1, 200));

    // prime number, divide large
    CASE(N = 5000, Q = 100, A = prime_array(N, 150000, 200000), X = random_array(Q, 150000, 200000));

    // prime number, divide large prime
    CASE(N = 200000, Q = 200000, A = prime_array(N, 150000, 200000), X = prime_array(Q, 150000, 200000));

    // prime number, divide > MAX
    CASE(N = 10000, Q = 50, A = prime_array(N, 150000, 200000), X = random_array(Q, 200001, 1000000000));

    // random
    CASE(N = 1000, Q = 1000, A = random_array(N, 1, 200000), X = random_array(Q, 1, 200000));
    CASE(N = 1000, Q = 1000, A = random_array(N, 1, 200000), X = random_array(Q, 1, 1000000000));
  }

  // no memo killer
  void TestGroup4() {
    CASE(N = 200000, Q = 200000, A = complete_array(N), X = random_array(Q, 1, 10));
  }

  // sqrt * N killer
  void TestGroup5() {
    CASE(N = 200000, Q = 400, A = random_array(N, 1, 999), X = complete_array(Q));
    CASE(N = 200000, Q = 400, A = random_array(N, 1, 999), X = complete_array(Q));
    CASE(N = 200000, Q = 400, A = random_array(N, 1, 999), X = complete_array(Q));
    CASE(N = 200000, Q = 400, A = random_array(N, 1, 999), X = complete_array(Q));
    CASE(N = 200000, Q = 400, A = random_array(N, 1, 999), X = complete_array(Q));
    CASE(N = 200000, Q = 400, A = random_array(N, 1, 999), X = complete_array(Q));
    CASE(N = 50000, Q = 400, A = random_array(N, 1, 999), X = complete_array(Q));
  }

private:
  mt19937 mersenne = mt19937(0xfafa);

  vector<int> same_array(int size, int val) {
    vector<int> ret;
    for (int i = 0; i < size; i++) ret.push_back(val);
    return ret;
  }

  vector<int> complete_array(int size) {
    vector<int> ret;
    for (int i = 1; i <= size; i++) ret.push_back(i);
    return ret;
  }

  vector<int> random_array(int size, int L, int R) {
    vector<int> ret;
    for (int i = 0; i < size; i++) ret.push_back(nextInt(L, R));
    return ret;
  }

  vector<int> prime_array(int size, int L, int R) {
    vector<bool> is(R + 1, 0);
    vector<int> prime;
    for (int i = 2; i <= R; i++) {
      if (!is[i]) prime.push_back(i);
      for (int j = 0; j < prime.size() && 1LL * i * prime[j] <= R; j++) {
        is[i * prime[j]] = 1;
        if (i % prime[j] == 0) break;
      }
    }
    int l = lower_bound(prime.begin(), prime.end(), L) - prime.begin();
    int r = prime.size() - 1;
    vector<int> ret;
    for (int i = 0; i < size; i++) {
      ret.push_back(prime[nextInt(l, r)]);
    }
    return ret;
  }

  int nextInt(int L = 0, int R = 1e5) {
    assert(L <= R);
    return L + mersenne() % (R - L + 1);
  }
};