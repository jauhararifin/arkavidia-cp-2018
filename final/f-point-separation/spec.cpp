#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N, M;
  vector<int> X, Y;

  int ans;

  void InputFormat() {
    LINE(N, M);
    LINES(X, Y) % SIZE(N + M);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(0 <= N && N <= 75);
    CONS(0 <= M && M <= 75);
    CONS(X.size() == N + M && Y.size() == N + M);
    CONS(eachElementBetween(X, -1000, 1000) && eachElementBetween(Y, -1000, 1000));
    CONS(distinctPoints(N+M, X, Y));
  }
private:
  bool eachElementBetween(const vector<int>& v, int lo, int hi) {
    for (int x : v)
      if (x < lo || x > hi)
        return 0;
    return 1;
  }
  bool distinctPoints(int sz, const vector<int>& x, const vector<int>& y) {
    set<pair<int, int> > st;
    for (int i = 0; i < sz; ++i)
      st.insert(make_pair(x[i], y[i]));
    return st.size() == sz;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Input({
      "3 1",
      "0 0",
      "10 0",
      "5 10",
      "5 5",
    });
    Output({
      "1"
    });
  }

  void BeforeTestCase() {
    X.clear();
    Y.clear();
  }

  void TestCases() {
    // N = 0 || M = 0
    CASE(N = 0, M = 3, X = {1, 3, 5}, Y = {0, 7, 3});
    CASE(N = 3, M = 0, X = {1, 6, 5}, Y = {0, 5, 9});
    CASE(N = 0, M = 0, X = {}, Y = {});

    // small N, M
    CASE(N = 1, M = 1, randomPoints(N+M, X, Y, -1000, 1000));
    CASE(N = 2, M = 2, randomPoints(N+M, X, Y, -1000, 1000));
    CASE(N = 1, M = 3, randomPoints(N+M, X, Y, -1000, 1000));
    CASE(N = 3, M = 2, randomPoints(N+M, X, Y, -1000, 1000));

    // satu garis
    CASE(N = 2, M = 3, X = {4, 5, 1, 2, 6}, Y = {9, 10, 6, 7, 11});
    CASE(N = 3, M = 3, X = {4, 5, 1, 2, 3, 6}, Y = {9, 10, 6, 7, 8, 11});
    CASE(N = rnd.nextInt(1, 25), M = rnd.nextInt(1, 75), randomLinear(N+M, X, Y));
    CASE(N = rnd.nextInt(25, 50), M = rnd.nextInt(1, 75), randomLinear(N+M, X, Y, rnd.nextInt(0, 5)));
    CASE(N = rnd.nextInt(50, 75), M = rnd.nextInt(1, 75), randomLinear(N+M, X, Y, rnd.nextInt(0, 5)));
    CASE(N = 75, M = 75, randomLinear(N+M, X, Y, rnd.nextInt(0, 5)));

    // ANS = 0
    CASE(N = rnd.nextInt(1, 25), M = rnd.nextInt(1, 25), generateAns0(N+M, X, Y, -1000, 1000));
    CASE(N = rnd.nextInt(25, 50), M = rnd.nextInt(25, 50), generateAns0(N+M, X, Y, -1000, 1000));
    CASE(N = rnd.nextInt(50, 75), M = rnd.nextInt(50, 75), generateAns0(N+M, X, Y, -1000, 1000));
    CASE(N = rnd.nextInt(1, 75), M = rnd.nextInt(1, 75), generateAns0(N+M, X, Y, -1000, 1000));
    CASE(N = 75, M = 75, generateAns0(N+M, X, Y, -1000, 1000));
    CASE(N = 75, M = 75, generateAns0(N+M, X, Y, -1000, 1000));

    // random
    CASE(N = rnd.nextInt(1, 25), M = rnd.nextInt(1, 25), randomPoints(N+M, X, Y, -1000, 1000));
    CASE(N = rnd.nextInt(1, 25), M = rnd.nextInt(25, 50), randomPoints(N+M, X, Y, -1000, 1000));
    CASE(N = rnd.nextInt(1, 25), M = rnd.nextInt(50, 75), randomPoints(N+M, X, Y, -1000, 1000));
    CASE(N = rnd.nextInt(25, 50), M = rnd.nextInt(1, 25), randomPoints(N+M, X, Y, -1000, 1000));
    CASE(N = rnd.nextInt(25, 50), M = rnd.nextInt(25, 50), randomPoints(N+M, X, Y, -1000, 1000));
    CASE(N = rnd.nextInt(25, 50), M = rnd.nextInt(50, 75), randomPoints(N+M, X, Y, -1000, 1000));
    CASE(N = rnd.nextInt(50, 75), M = rnd.nextInt(1, 25), randomPoints(N+M, X, Y, -1000, 1000));
    CASE(N = rnd.nextInt(50, 75), M = rnd.nextInt(25, 50), randomPoints(N+M, X, Y, -1000, 1000));
    CASE(N = rnd.nextInt(50, 75), M = rnd.nextInt(50, 75), randomPoints(N+M, X, Y, -1000, 1000));
    CASE(N = 75, M = 75, randomPoints(N+M, X, Y, -1000, 1000));
    CASE(N = 75, M = 75, randomPoints(N+M, X, Y, -1000, 1000));
    CASE(N = 75, M = 75, randomPoints(N+M, X, Y, -1000, 1000));
  }

private:
  void randomLinear(int sz, vector<int> & x, vector<int> & y, int mul = 0) {
    int offsetx = rnd.nextInt(-1000, 0);
    int offsety = rnd.nextInt(-1000, 0);
    set<int> st;
    while (st.size() < sz)
      st.insert(rnd.nextInt(0, 400));
    x.clear();
    for (int v : st) {
      x.push_back(v);
      offsetx = min(offsetx, 1000-v);
    }
    rnd.shuffle(x.begin(), x.end());
    y.clear();
    for (int v : x) {
      y.push_back(v * mul);
      offsety = min(offsety, 1000-v*mul);
    }
    for (int & v : x)
      v += offsetx;
    for (int & v : y)
      v += offsety;
  }

  void randomOrder(vector<int> & x, vector<int> &y) {
    int sz = x.size();
    vector<int> tmpx = x, tmpy = y, id(sz);
    for (int i = 0; i < sz; ++i)
      id[i] = i;
    rnd.shuffle(id.begin(), id.end());
    for (int i = 0; i < sz; ++i)
      x[i] = tmpx[id[i]], y[i] = tmpy[id[i]];
  }

  void randomPoints(int sz, vector<int> & x, vector<int> &y, int lo, int hi) {
    x.clear(), y.clear();
    set<pair<int, int> > st;
    while (st.size() < sz) {
      int px = rnd.nextInt(lo, hi), py = rnd.nextInt(lo, hi);
      st.insert(make_pair(px, py));
    }
    for (auto it : st)
      x.push_back(it.first), y.push_back(it.second);
    randomOrder(x, y);
  }

  void generateAns0(int sz, vector<int> & x, vector<int> & y, int lo, int hi) {
    int centerx = rnd.nextInt(lo, hi), centery = rnd.nextInt(lo, hi);
    randomPoints(sz, x, y, lo, hi);
    vector<pair<int, int> > id(sz);
    for (int i = 0; i < sz; ++i) {
      int dx = centerx - x[i], dy = centery - y[i];
      id[i].first = dx * dx + dy * dy;
      id[i].second = i;
    }
    sort(id.begin(), id.end());
    vector<int> tmpx = x, tmpy = y;
    for (int i = 0; i < sz; ++i)
      x[i] = tmpx[id[i].second], y[i] = tmpy[id[i].second];
  }
};