#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

const int MAXN = 50000;
const int MAXH = 100000;
const int MAXQ = 50000;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N,Q;
  vector<int> H, L, R;
  vector<int> result;

  void InputFormat() {
    LINE(N);
    LINE(H % SIZE(N));
    LINE(Q);
    LINES(L, R) % SIZE(Q); 
  }

  void OutputFormat() {
    LINES(result) % SIZE(Q);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(1 <= Q && Q <= MAXQ);
    CONS(eachElementBetween(H, 1, MAXH));
    CONS(eachElementBetween(L, 1, N));
    CONS(eachElementBetween(R, 1, N));
    CONS(L.size() == R.size());
    CONS(L.size() == Q);
    CONS(eachElementBefore(L, R));
  }

private:
  bool eachElementBetween(vector<int>& A, int L, int R) {
    for (int x : A)
      if (x < L || x > R)
        return 0;
    return 1;
  }
  bool eachElementBefore(vector<int>& A, vector<int>& B) {
    for (int i = 0; i < A.size(); i++)
      if (A[i] >= B[i])
        return 0;
    return 1;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Input({
      "7",
      "4 1 2 3 2 3 1",
      "2",
      "2 5",
      "1 7"
    });
    Output({
      "4",
      "3",
    });
  }

  void BeforeTestCase() {
    H.clear();
    L.clear();
    R.clear();
    result.clear();
  }

  void TestCases() {
    // random testcases
    CASE(N = MAXN; Q = MAXQ; randomHeight(N); randomRestQuery());
    CASE(N = MAXN; Q = MAXQ; randomHeight(N); randomRestQueryMinimal(20000));
    CASE(N = MAXN; Q = MAXQ; randomHeight(N); randomRestQueryMinimal(30000));
    CASE(N = MAXN; Q = MAXQ; randomHeight(N); randomRestQueryMinimal(49900));

    // when heights are increasing/decreasing
    CASE(N = MAXN; Q = MAXQ; heightSameAsIndex(N); largestQuery(MAXQ));
    CASE(N = MAXN; Q = MAXQ; heightSameAsIndex(N); reverse(H.begin(), H.end()); largestQuery(MAXQ));
    CASE(N = MAXN; Q = MAXQ; heightSameAsIndex(N); reverse(H.begin(), H.end()); largestQuery(MAXQ/2), randomRestQuery());

    // when heights are increasing but contain some random value
    CASE(N = MAXN; Q = MAXQ; heightSameAsIndex(N); changeSomeHeightWithRandom(N/10); largestQuery(MAXQ));
    CASE(N = MAXN; Q = MAXQ; heightSameAsIndex(N); changeSomeHeightWithRandom(N/10); reverse(H.begin(), H.end()); largestQuery(MAXQ));
    CASE(N = MAXN; Q = MAXQ; heightSameAsIndex(N); changeSomeHeightWithRandom(N/10); largestQuery(MAXQ/3); randomRestQuery());

    // all heights are same, largest query range
    CASE(N = MAXN; Q = MAXQ; largestQuery(MAXQ); allSameHeight(N, 1));
    CASE(N = MAXN; Q = MAXQ; largestQuery(MAXQ); allSameHeight(N, MAXH));
    CASE(N = MAXN; Q = MAXQ; largestQuery(MAXQ); allSameHeight(N, MAXH/2+rand()%100));

    // always traverse to the right
    CASE(N = MAXN; Q = MAXQ; allSameHeight(3, MAXH); heightSameAsIndex(N - 3); largestQuery(Q));
    CASE(N = MAXN, Q = MAXQ; allSameHeight(3, MAXH); heightSameAsIndex(N - 3); reverse(H.begin(), H.end()); largestQuery(Q));
  }

private:
  void allSameHeight(int N, int X) {
    for (int i = 0; i < N; i++)
      H.push_back(X);
  }
  void heightSameAsIndex(int N) {
    for (int i = 0; i < N; i++)
      H.push_back(i+1);
  }
  void randomHeight(int N) {
    for (int i = 0; i < N; i++)
      H.push_back(1 + rand() % MAXH);
  }
  void changeSomeHeightWithRandom(int changes) {
    while (changes--)
      H[rand() % N] = 1 + rand() % MAXH;
  }
  void largestQuery(int Q) {
    for (int width = N; Q > 0 && width > 1; width--)
      for (int i = 0; Q > 0 && i <= N - width; i++) {
        L.push_back(i+1);
        R.push_back(i+width);
        Q--;
      }
  }
  void randomRestQuery() {
    while (L.size() < Q) {
      int l = 1 + rand() % N;
      int r = 1 + rand() % N;
      if (l > r) swap(l, r);
      if (l == r && l > 1) l--;
      else if (l == r) r++;
      L.push_back(l);
      R.push_back(r);
    }
  }
  void randomRestQueryMinimal(int minimal) {
    while (L.size() < Q) {
      int width = minimal + rand() % (N - minimal + 1);
      int l = 1 + rand() % (N - width + 1);
      int r = l + width - 1;
      L.push_back(l);
      R.push_back(r);
    }
  }
};
