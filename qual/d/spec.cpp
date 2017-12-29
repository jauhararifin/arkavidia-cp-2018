#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
  int T;
  int N, K;
  vector<int> A;

  int ans;

  void InputFormat() {
    LINE(N, K);
    LINE(A);
  }

  void OutputFormat() {
    LINE(ans);
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
    CONS(1 <= T && T <= 20);
  }

  void Constraints() {
    CONS(1 <= N && N <= 100000);
    CONS(1 <= K && K <= N);
    CONS(eachElementBetween(A, 1, (int) 1e9));
  }
private:
  bool eachElementBetween(const vector<int>& v, int lo, int hi) {
    for (int x : v)
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
      "1 1 1 2 2"
    });
    Output({
      "1"
    });
  }

  void SampleTestCase2() {
    Input({
      "5 2",
      "1 1 1 2 2"
    });
    Output({
      "0"
    });
  }

  void BeforeTestCase() {
    A.clear();
  }

  void AfterTestCase() {
    rnd.shuffle(A.begin(), A.end());
  }

  // manual small
  void TestGroup1() {
    CASE(N = 1, K = 1, A = {314});

    CASE(N = 2, K = 2, A = {314, 217});

    CASE(N = 5, K = 2, A = {1, 2, 3, 5, 6});
    CASE(N = 5, K = 3, A = {1, 2, 3, 5, 6});

    CASE(N = 9, K = 3, A = {1, 2, 2, 4, 7, 10, 12, 12, 200});
    CASE(N = 9, K = 3, A = {1, 2, 2, 3, 7, 10, 12, 12, 200});

    CASE(N = 10, K = 3, A = {1, 2, 2, 4, 7, 10, 12, 14, 14, 200});
    CASE(N = 10, K = 3, A = {1, 4, 7, 10, 24, 27, 42, 45, 48, 51});
    CASE(N = 10, K = 3, A = {1, 4, 7, 10, 13, 101, 104, 107, 110, 113});

    CASE(N = 12, K = 5, A = {1, 1, 1, 1, 1, 2, 2, 2, 4, 6, 6, 6});
    CASE(N = 12, K = 4, A = {1, 1, 1, 1, 3, 3, 3, 6, 8, 8, 8, 8});
    CASE(N = 12, K = 4, A = {1, 1, 1, 1, 3, 7, 7, 7, 8, 9, 9, 9});
    CASE(N = 12, K = 4, A = {1, 2, 3, 3, 3, 4, 5, 9, 13, 13, 19, 31});
    CASE(N = 12, K = 3, A = {1, 2, 3, 3, 3, 6, 7, 9, 12, 12, 19, 31});
    CASE(N = 12, K = 2, A = {1, 2, 3, 3, 3, 6, 7, 12, 12, 12, 19, 31});
  }

  // random with some distribution
  void TestGroup2() {
    CASE(N = 100000, K = rnd.nextInt(073, 13513), A = duplicate(uniformDistribution(N/100, 1, 10000, 2), 100));
    CASE(N = 100000, K = rnd.nextInt(073, 13513), A = uniformDistribution(N, 1, int(1e9), 5));
    CASE(N = 100000, K = rnd.nextInt(073, 13513), A = sinusoidal(N, 1000));
    CASE(N = 100000, K = rnd.nextInt(073, 13513), A = sinusoidal(N, 10000, 1, 1000));
    CASE(N = 100000, K = rnd.nextInt(073, 13513), A = sinusoidal(N, 1000, 1, 1000));
    CASE(N = 100000, K = rnd.nextInt(073, 13513), A = sinusoidal(N, 100, 1, 1000));
    CASE(N = 100000, K = rnd.nextInt(073, 13513), A = sinusoidal(N, 10, 1, 1000));
    CASE(N = 100000, K = rnd.nextInt(073, 13513), A = sinusoidal(N, 5, 1, 1000));
  }

  // full random
  void TestGroup3() {
    CASE(N = rnd.nextInt(10000, 100000), K = N, A = randomArray(N, 1, 100));
    CASE(N = rnd.nextInt(10000, 100000), K = N / 10, A = randomArray(N, 1, 1000));
    CASE(N = rnd.nextInt(10000, 100000), K = N / 100, A = randomArray(N, 1, 10000));
    CASE(N = rnd.nextInt(10000, 100000), K = N / 500, A = randomArray(N, 1, 100000));
    CASE(N = rnd.nextInt(10000, 100000), K = N / 2000, A = randomArray(N, 1, 1000000));
    CASE(N = rnd.nextInt(10000, 100000), K = 1, A = randomArray(N, 1, 9));
    CASE(N = rnd.nextInt(10000, 100000), K = 13, A = randomStairs(N, 314, 15, 926535));
    CASE(N = rnd.nextInt(10000, 100000), K = 73, A = randomStairs(N, 31, 415, 9265));
    CASE(N = rnd.nextInt(10000, 100000), K = 135, A = randomStairs(N, 3, 14, 15926));
    CASE(N = rnd.nextInt(10000, 100000), K = 165, A = randomStairs(N, 3141, 5, 926535));
    CASE(N = rnd.nextInt(10000, 100000), K = 182, A = randomStairs(N, 314, 1, 592653));
    CASE(N = rnd.nextInt(10000, 100000), K = 281, A = randomStairs(N, 27, 18, 281));
    CASE(N = rnd.nextInt(10000, 100000), K = 370, A = randomStairs(N, 271, 8, 28182));
    CASE(N = rnd.nextInt(10000, 100000), K = 531, A = randomStairs(N, 2718, 28, 182846));
    CASE(N = rnd.nextInt(10000, 100000), K = 561, A = randomStairs(N, 27, 182, 818284));
    CASE(N = rnd.nextInt(10000, 100000), K = 1351, A = randomStairs(N, 2718, 2, 81828));
    CASE(N = rnd.nextInt(10000, 100000), K = 1651, A = randomStairs(N, 161, 80, 339887));
    CASE(N = rnd.nextInt(20000, 100000), K = 13073, A = randomStairs(N, 16180, 3, 398875));
    CASE(N = rnd.nextInt(30000, 100000), K = 13513, A = randomStairs(N, 161, 80, 339887));
    CASE(N = rnd.nextInt(50000, 100000), K = 16513, A = randomStairs(N, 16, 180, 339));
  }

private:
  vector<int> randomArray(int n, int lo = 1, int hi = int(1e9)) {
    vector<int> ret(n);
    for (int i = 0; i < n; ++i)
      ret[i] = rnd.nextInt(lo, hi);
    return ret;
  }
  vector<int> uniformDistribution(int n, int lo = 1, int hi = int(1e9), int err = 1) {
    vector<int> ret(n);
    int maxdiff = hi - lo;
    int diff = maxdiff/n - 1 - err;
    for (int i = 0, now = lo; i < n; ++i, now += rnd.nextInt(diff, diff+err))
      ret[i] = now;
    cerr << ret.back() << endl;
    return ret;
  }

  vector<int> duplicate(vector<int> arr, int k) {
    vector<int> ret(arr.size() * k);
    for (int i = 0; i < arr.size(); ++i) {
      for (int j = 0; j < k; ++j)
        ret[i * k + j] = arr[i];
    }
    return ret;
  }
  vector<int> sinusoidal(int n, int periode, int lo = 1, int hi = int(1e9), int err = 1) {
    vector<int> ret(n);
    int maxdiff = hi - lo, ma = maxdiff / 2;
    int move = rnd.nextInt(0, periode-1);
    long double PI = acos(-1);
    for (int i = 0; i < n; ++i) {
      ret[i] = ma * (1 + sin((move + i) * PI / periode));
      ret[i] = max(min(ret[i], ma), 0);
    }
    long long sum = 0;
    for (int i = 0; i < n; ++i)
      sum += ret[i];
    int sisa = maxdiff;
    for (int i = 0; i < n; ++i) {
      ret[i] = 1LL * ret[i] * maxdiff / sum;
      ret[i] = rnd.nextInt(ret[i]-err, ret[i]+err);
      ret[i] = min(max(ret[i], 0), sisa);
      sisa -= ret[i];
    }
    for (int i = 0, now = lo; i < n; ++i) {
      now += ret[i];
      ret[i] = now;
    }
    return ret;
  }
  vector<int> randomStairs(int n, int step, int lo = 1, int hi = int(1e9)) {
    vector<int> ret(n, 0);
    set<int> stepIds;
    while (stepIds.size() < step) {
      stepIds.insert(rnd.nextInt(1, n-1));
    }
    long long sum = 0;
    int maxdiff = hi - lo;
    for (int id : stepIds) {
      int incValue = rnd.nextInt(1, maxdiff);
      ret[id] = incValue;
      sum += incValue;
    }
    for (int id : stepIds) {
      ret[id] = 1LL * ret[id] * maxdiff / sum;      
    }
    for (int i = 0, now = lo; i < n; ++i) {
      now += ret[i];
      ret[i] = now;
    }
    return ret;
  }
};