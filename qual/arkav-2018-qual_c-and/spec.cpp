#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
  int T;
  int N, Q;
  vector<int> A, L, R;

  vector<int> ans;

  void InputFormat() {
    LINE(N);
    LINE(A);
    LINE(Q);
    LINES(L, R) % SIZE(Q);
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
    CONS(eachElementBetween(A, 0, (int) 1e9));
    CONS(eachElementBetween(L, 1, N));
    CONS(N == A.size());
    CONS(Q == L.size() && Q == R.size());
    CONS(lessEqual(L, R));
  }
private:
  bool lessEqual(vector<int> L, vector<int> R) {
    if (L.size() != R.size()) return 0;
    for (int i = 0; i < L.size(); i++) if (L[i] > R[i]) return 0;
    return 1;
  }
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
      "7",
      "7 4 5 6 31 58 1",
      "4",
      "1 5",
      "3 4",
      "1 7",
      "4 6"
    });
    Output({
      "4",
      "4",
      "0",
      "2"
    });
  }

  void BeforeTestCase() {
    A.clear();
    L.clear();
    R.clear();
    ans.clear();
  }

  // correctness check
  void TestGroup1() {
    // same
    CASE(N = 1000, Q = 10, A = same_array(N, 7), random(L, R, N, Q));
    // ascending ke
    CASE(N = 1000, Q = 1000, A = ascending_array(28, N), from_kanan(L, R, N, Q));
    // descending ke
    CASE(N = 1000, Q = 1000, A = descending_array(28, N), from_kiri(L, R, N, Q));
    // selang seling, ascending/descending, random, full
    CASE(N = 1000, Q = 1000, A = campur_array(28, N), random(L, R, N, Q));
    CASE(N = 1000, Q = 1000, A = campur_array(28, N), random(L, R, N, Q));
    CASE(N = 1000, Q = 1000, A = campur_array(28, N), random(L, R, N, Q));
    // random
    CASE(N = 1000, Q = 1000, A = random_array(28, N), random(L, R, N, Q));
    CASE(N = 1000, Q = 1000, A = random_array(28, N), random(L, R, N, Q));
    CASE(N = 1000, Q = 1000, A = random_array(28, N), random(L, R, N, Q));
    CASE(N = 1000, Q = 1000, A = random_array(28, N), random(L, R, N, Q));
  }
  // killer
  void TestGroup2() {
    // same - pojok kanan kiri
    CASE(N = 200000, Q = 200000, A = same_array(N, 1000000000), from_kiri_kanan(L, R, N, Q));
  }
  void TestGroup3() {
    // campur - pojok kanan kiri
    CASE(N = 200000, Q = 190000, A = campur_array(2, N), from_kiri_kanan(L, R, N, Q));
    // random - pojok kanan kiri
    CASE(N = 200000, Q = 200000, A = random_array(2, N), from_kiri_kanan(L, R, N, Q));
  }

private:
  mt19937 mersenne = mt19937(0xfafa);

  vector<int> same_array(int size, int val) {
    vector<int> ret;
    for (int i = 0; i < size; i++) ret.push_back(val);
    return ret;
  }

  vector<int> ascending_array(int ke_max, int size) {
    vector<int> ret(size, 0);
    for (int i = 0; i <= ke_max; i++) {
      vector<int> ke = ascending(i, size);
      for (int j = 0; j < size; j++) {
        ret[j] |= ke[j];
      }
    }
    return ret;
  }

  vector<int> descending_array(int ke_max, int size) {
    vector<int> ret(size, 0);
    for (int i = 0; i <= ke_max; i++) {
      vector<int> ke = descending(i, size);
      for (int j = 0; j < size; j++) {
        ret[j] |= ke[j];
      }
    }
    return ret;
  }

  vector<int> campur_array(int ke_max, int size) {
    vector<int> ret(size, 0);
    for (int i = 0; i <= ke_max; i++) {
      vector<int> ke;
      int gacha = nextInt(1, 4);
      if (gacha == 1) {
        ke = selang_seling(i, size);
      } else if (gacha == 2) {
        int cok = nextInt(0, 1);
        if (cok) {
          ke = ascending(i, size);
        } else {
          ke = descending(i, size);
        }
      } else if (gacha == 3) {
        ke = random(i, size);
      } else {
        ke = full(i, size);
      }
      for (int j = 0; j < size; j++) {
        ret[j] |= ke[j];
      }
    }
    return ret;
  }

  vector<int> random_array(int ke_max, int size) {
    vector<int> ret(size, 0);
    for (int i = 0; i <= ke_max; i++) {
      vector<int> ke = random(i, size);
      for (int j = 0; j < size; j++) {
        ret[j] |= ke[j];
      }
    }
    return ret;
  }


  /**** return array per ke secara independen ****/
  vector<int> selang_seling(int ke, int size) {
    vector<int> ret;
    int now = nextInt(0, 1);
    for (int i = 0; i < size; i++) {
      if (now) {
        ret.push_back(1 << ke);
      } else {
        ret.push_back(0);
      }
      now ^= 1;
    }
    return ret;
  }
  vector<int> ascending(int ke, int size) {
    vector<int> ret(size, 0);
    int l = nextInt(0, size - 1);
    for (int i = l; i < size; i++) {
      ret[i] = (1 << ke);
    }
    return ret;
  }
  vector<int> descending(int ke, int size) {
    vector<int> ret(size, 0);
    int l = nextInt(0, size - 1);
    for (int i = 0; i <= l; i++) {
      ret[i] = (1 << ke);
    }
    return ret;
  }
  vector<int> random(int bit, int size) {
    vector<int> ret(size, 0);
    vector<int> sum(size, 0);
    for (int i = 0; i < 5; i++) {
      int l = nextInt(0, size - 1);
      int r = nextInt(0, size - 1);
      sum[l]++;
      if (r + 1 < size) sum[r + 1]--;
    }
    for (int i = 0; i < size; i++) {
      if (i) sum[i] += sum[i - 1];
      if (sum[i]) {
        ret[i] = (1 << bit);
      }
    }
    return ret;
  }
  vector<int> full(int ke, int size) {
    vector<int> ret(size, 1 << ke);
    return ret;
  }


  /**** return array query ****/

  void from_kiri(vector<int>& L, vector<int>& R, int N, int size) {
    for (int i = 0; i < size; i++) {
      auto it = from_kiri(N);
      L.push_back(it.first);
      R.push_back(it.second);
    }
  }
  void from_kanan(vector<int>& L, vector<int>& R, int N, int size) {
    for (int i = 0; i < size; i++) {
      auto it = from_kanan(N);
      L.push_back(it.first);
      R.push_back(it.second);
    }
  }
  void from_kiri_kanan(vector<int>& L, vector<int>& R, int N, int size) {
    for (int i = 0; i < size; i++) {
      auto it = from_kiri_kanan(N);
      L.push_back(it.first);
      R.push_back(it.second);
    }
  }
  void random(vector<int>& L, vector<int>& R, int N, int size) {
    for (int i = 0; i < size; i++) {
      pair<int, int> ret;
      int gacha = nextInt(1, 11);
      if (gacha <= 6) {
        ret = random(N);
      } else if (gacha <= 8) {
        ret = from_kiri_kanan(N);
      } else if (gacha <= 9) {
        ret = from_kiri(N);
      } else if (gacha <= 10) {
        ret = from_kanan(N);
      } else {
        ret = same(N);
      }
      L.push_back(ret.first);
      R.push_back(ret.second);
    }
  }

  /****  return pair query  *****/
  pair<int, int> from_kiri(int size) {
    int L = nextInt(1, max(1, size / 10));
    int R = nextInt(1, size);
    if (L > R) swap(L, R);
    return make_pair(L, R);
  }

  pair<int, int> from_kanan(int size) {
    int L = nextInt(1, size);
    int R = nextInt(size - size / 10, size);
    if (L > R) swap(L, R);
    return make_pair(L, R);
  }

  pair<int, int> from_kiri_kanan(int size) {
    int l = nextInt(1, min(size, (int) sqrt(size)));
    int r = nextInt(max(1, size - (int) sqrt(size)), size);
    if (l > r) swap(l, r);
    return make_pair(l, r);
  }

  pair<int, int> random(int size) {
    int L = nextInt(1, size);
    int R = nextInt(1, size);
    if (L > R) swap(L, R);
    return make_pair(L, R);
  }

  pair<int, int> same(int size) {
    int L = nextInt(1, size);
    return make_pair(L, L);
  }

  int nextInt(int L = 0, int R = 1e5) {
    assert(L <= R);
    return L + mersenne() % (R - L + 1);
  }
};