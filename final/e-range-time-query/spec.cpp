#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

const int MAXN = 100000;
const int MAXQ = 100000;
const int MAXS = 1000000000;
const int MAXD = 1000000000;
const int MAXT = 1000000000;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N, Q;
  vector<int> A;
  vector<int> B;
  vector<int> L,R,T;
  vector<long long> result;

  void InputFormat() {
    LINE(N);
    LINES(A, B) % SIZE(N);
    LINE(Q);
    LINES(L,R,T) % SIZE(Q);
  }

  void OutputFormat() {
    LINES(result) % SIZE(Q);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(A.size() == N);
    CONS(B.size() == N);
    CONS(L.size() == Q);
    CONS(R.size() == Q);
    CONS(T.size() == Q);

    CONS(1 <= N && N <= MAXN);
    CONS(1 <= Q && Q <= MAXQ);
    CONS(elementsBetween(A, 1, MAXS));
    CONS(elementsBetween(B, 1, MAXD));
    CONS(elementsBetween(L, 1, N));
    CONS(elementsBetween(R, 1, N));
    CONS(elementsBetween(T, 1, MAXT));
    CONS(validRange(L,R));
  }


private:
  bool elementsBetween(vector<int>& v, int a, int b) {
    for (int x : v)
      if (x < a || x > b) return 0;
    return 1;
  }
  bool validRange(vector<int>& a, vector<int>& b) {
    if (a.size() != b.size()) return 0;
    for (int i = 0; i < a.size(); i++)
      if (a[i] > b[i])
        return 0;
    return 1;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Input({
      "4",
      "30 2",
      "15 4",
      "10 4",
      "1 5",
      "3",
      "1 4 1",
      "2 4 1",
      "1 4 20",
    });
    Output({
      "32",
      "19",
      "101"
    });
  }

  void BeforeTestCase() {
    A.clear();
    B.clear();
    L.clear();
    R.clear();
    T.clear();
  }

  void TestCases() {
    CASE(N = MAXN; randomRestComputer(); Q = MAXQ; randomRestQuery());
    CASE(N = MAXN; randomRestComputer(); Q = MAXQ; randomRestQuery());
    CASE(N = MAXN; randomRestComputer(); Q = MAXQ; randomRestQuery());
    CASE(N = MAXN; randomRestComputer(); Q = MAXQ; randomRestQuery());
    CASE(N = MAXN; randomRestComputer(); Q = MAXQ; randomRestQuery());
  }

  void randomRestComputer() {
    while (A.size() < N) {
      A.push_back(rand() % MAXS + 1);
      B.push_back(rand() % MAXD + 1);
    }
  }

  void randomRestQuery() {
    while (L.size() < Q) {
      int a = rand() % N + 1;
      int b = rand() % N + 1;
      if (a > b)
          swap(a,b);
      int t = rand() % MAXT + 1;
      L.push_back(a);
      R.push_back(b);
      T.push_back(t);
    }
  }

};
