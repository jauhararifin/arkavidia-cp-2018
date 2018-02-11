#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
  const int LIMIT_BOX = 1e9;

  int N, Q;
  vector<int> X, Y;
  vector<vector<int>> A;
  vector<int> ans;

  void InputFormat() {
    LINE(N, Q);
    LINES(A) % SIZE(Q);
  }

  void OutputFormat() {
    LINES(ans);
  }

  void GradingConfig() {
    TimeLimit(5);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(1 <= N && N <= LIMIT_BOX);
    CONS(1 <= Q && Q <= 100000);
    CONS(Q == A.size());
    CONS(query_type_correctness());
    CONS(first_second_query());
    CONS(third_query());
    CONS(coordinate_correctness());
  }
private:
  bool query_type_correctness() {
    for (auto it : A) {
      if (!between(it[0], 1, 3)) return 0;
    }
    return 1;
  }
  bool first_second_query() {
    for (auto it : A) {
      if (it[0] <= 2) {
        if (it.size() != 3) return 0;
        if (!between(it[1], 1, N) || !between(it[2], 1, N)) return 0;
      }
    }
    return 1;
  }
  bool third_query() {
    int ada = 0;
    for (auto it : A) {
      if (it[0] == 3) {
        ada++;
        if (it.size() != 5) return 0;
        if (!between(it[1], 1, N) || !between(it[2], 1, N)) return 0;
        if (!between(it[3], 1, N) || !between(it[4], 1, N)) return 0;
        if (it[1] > it[3]) return 0;
        if (it[2] > it[4]) return 0;
      }
    }
    return ada >= 1;
  }
  bool between(int v, int lo, int hi) {
    return lo <= v && v <= hi;
  }
  bool coordinate_correctness() {
    set<pair<int, int>> s;
    for (int i = 0; i < Q; i++) {
      if (A[i][0] == 1) {
        int x = A[i][1];
        int y = A[i][2];
        if (s.count(make_pair(x, y))) {
          //puts("udah pernah kok dimasukin");
          return 0;
        }
        s.insert(make_pair(x, y));
      } else if (A[i][0] == 2) {
        int x = A[i][1];
        int y = A[i][2];
        if (!s.count(make_pair(x, y))) {
          //puts("gak ada kok dihapus");
          return 0;
        }
        s.erase(make_pair(x, y));
      }
    }
    return 1;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Input({
      "10 7",
      "1 1 1",
      "1 2 1",
      "1 3 3",
      "1 6 5",
      "3 1 1 5 4",
      "2 2 1",
      "3 1 1 4 5"
    });
    Output({
      "3",
      "2"
    });
  }

  void BeforeTestCase() {
    A.clear();
    X.clear();
    Y.clear();
    ans.clear();
  }

  void AfterTestCase() {

  }

  void TestCases() {
    // small random
    CASE(N = LIMIT_BOX, Q = 1, X = unique(N, 3), Y = unique(N, 3), random({3}));
    CASE(N = LIMIT_BOX, Q = 4, X = unique(N, 1), Y = unique(N, 1), random({1, 3, 2, 3}));
    CASE(N = LIMIT_BOX, Q = 3, X = random_array(10, 1, N), Y = random_array(10, 1, N), random({1, 3, 3}));
    CASE(N = LIMIT_BOX, Q = 1000, X = unique(N, Q),
                                  Y = unique(N, Q),
                                  random());
    CASE(N = LIMIT_BOX, Q = 1000, X = random_array(Q / 2, 1, N),
                                  Y = unique(N, Q),
                                  random());
    CASE(N = LIMIT_BOX, Q = 1000, X = unique(N, Q),
                                  Y = random_array(Q / 2, 1, N),
                                  random());
    CASE(N = LIMIT_BOX, Q = 1000, X = random_array(1, 1, N),
                                  Y = random_array(2 * Q, 1, N),
                                  random());
    CASE(N = LIMIT_BOX, Q = 1000, X = random_array(2 * Q, 1, N),
                                  Y = random_array(1, 1, N),
                                  random());

    // 20k taruh, 80k tanya
    CASE(N = LIMIT_BOX, Q = 100000, X = unique(N, Q), Y = unique(N, Q),
      random(create_T({20000, 1}, {80000, 3})));

    // 10k taruh, 80k tanya, 10k kehapus
    CASE(N = LIMIT_BOX, Q = 100000, X = unique(N, Q), Y = unique(N, Q),
      random(create_T({10000, 1}, {80000, 3}, {10000, 2})));

    // 1k taruh, 98k tanya, 1k hapus
    CASE(N = LIMIT_BOX, Q = 100000, X = unique(N, Q), Y = unique(N, Q),
      random(create_T({1000, 1}, {98000, 3}, {1000, 2})));

    // 75% taruh 25% tanya
    CASE(N = LIMIT_BOX, Q = 100000, X = unique(N, Q), Y = unique(N, Q),
      random(create_T({75000, 1}, {25000, 3})));

    // 90% taruh 10% tanya
    CASE(N = LIMIT_BOX, Q = 100000, X = unique(N, Q), Y = unique(N, Q),
      random(create_T({90000, 1}, {10000, 3})));

    // 100% taruh 1 tanya
    CASE(N = LIMIT_BOX, Q = 100000, X = unique(N, Q), Y = unique(N, Q),
      random(create_T({99999, 1}, {1, 3})));

    // 50% taruh 50% tanya
    CASE(N = LIMIT_BOX, Q = 100000, X = unique(N, Q), Y = unique(N, Q),
      random(create_T({50000, 1}, {50000, 3})));

    // 50% taruh 50% hapus, tanya dikit dikit
    CASE(N = LIMIT_BOX, Q = 100000, X = unique(N, Q), Y = unique(N, Q),
      random(taruh_hapus_tanya_dikit(49900, 49900, 200)));

    // 33% taruh, 33% tanya, 33% hapus
    CASE(N = LIMIT_BOX, Q = 99999, X = unique(N, Q), Y = unique(N, Q),
      random(create_T({33333, 1}, {33333, 3}, {33333, 2})));

    // 40% taruh, 50% tanya, 10% hapus
    CASE(N = LIMIT_BOX, Q = 100000, X = unique(N, Q), Y = unique(N, Q),
      random(create_T({40000, 1}, {50000, 3}, {10000, 2})));
  }

private:
  mt19937 mersenne = mt19937(0xfafa);

  vector<int> unique(int N, int Q) {
    return random_array(4*Q, 1, N);
  }

  vector<int> taruh_hapus_tanya_dikit(int taruh, int hapus, int tanya) {
    vector<int> ret, ask, sip;
    while (tanya--) ask.push_back(nextInt(0, taruh + hapus - 1));
    while (taruh--) ret.push_back(1);
    while (hapus--) ret.push_back(2);
    sort(ask.begin(), ask.end());
    int j = 0;
    for (int i = 0; i < hapus; i++) {
      if (j < ask.size() && i == ask[j]) {
        sip.push_back(3);
      }
      sip.push_back(ret[i]);
    }
    return sip;
  }

  // kali - tipe
  vector<int> create_T(pair<int, int> first, pair<int, int> second = {0, 0}, pair<int, int> third = {0, 0}) {
    vector<int> ret;
    while (first.first--) ret.push_back(first.second);
    while (second.first--) ret.push_back(second.second);
    while (third.first--) ret.push_back(third.second);
    return ret;
  }

  void random(vector<int> T = {}) {
    set<pair<int, int>> s;
    for (int i = 0; i < Q; i++) {
      int t = (i < T.size()? T[i] : nextInt(1, 3));
      while (t == 2 && s.empty()) t = nextInt(1, 3);
      if (t == 1) {
        int x = X[nextInt(0, X.size() - 1)];
        int y = Y[nextInt(0, Y.size() - 1)];
        while (s.count(make_pair(x, y))) {
          x = X[nextInt(0, X.size() - 1)];
          y = Y[nextInt(0, Y.size() - 1)];
        }
        vector<int> T = {t, x, y};
        A.push_back(T);
        s.insert(make_pair(x, y));
      } else if (t == 2) {
        int x = X[nextInt(0, X.size() - 1)];
        int y = Y[nextInt(0, Y.size() - 1)];
        while (s.lower_bound(make_pair(x, y)) == s.end()) {
          if (s.size() < 10) {
            int rand = nextInt(0, s.size() - 1);
            auto it = s.begin();
            while (rand--) it++;
            x = it->first;
            y = it->second;
          } else {
            x = X[nextInt(0, X.size() - 1)];
            y = Y[nextInt(0, Y.size() - 1)];
          }
        }
        auto it = s.lower_bound(make_pair(x, y));
        x = it->first;
        y = it->second;
        vector<int> T = {t, x, y};
        A.push_back(T);
        s.erase(s.lower_bound(make_pair(x, y)));
      } else {
        int x1 = X[nextInt(0, X.size() - 1)];
        int x2 = X[nextInt(0, X.size() - 1)];
        int y1 = Y[nextInt(0, Y.size() - 1)];
        int y2 = Y[nextInt(0, Y.size() - 1)];
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        vector<int> T = {t, x1, y1, x2, y2};
        A.push_back(T);
      }
    }
  }

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

  int nextInt(int L = 0, int R = 1e5) {
    assert(L <= R);
    return L + mersenne() % (R - L + 1);
  }
};