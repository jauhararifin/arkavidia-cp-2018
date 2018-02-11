#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;
typedef long long LL;
const int MAXN = 5000;
const int MAXX = 5000;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N, X;
  vector<int> U;

  int result;
  void InputFormat() {
    LINE(N, X);
    LINES(U) % SIZE(N - 1);
  }

  void OutputFormat() {
    LINE(result);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(1 <= X && X <= MAXX);
    CONS((int) U.size() == N - 1);
    CONS(HierarchyTree(U));
  }


private:
  template<class T>
  bool HierarchyTree(vector<T> elements){
    for(int i = 0;i < (int) elements.size(); ++i){
      if(elements[i] > (T) i) return false;
    }
    return true;
  }

  template<class T>
  bool ElementsBetween(vector<T> elements, T lowerBound, T upperBound) {
    for(T element: elements) {
      if ((element < lowerBound) || (element > upperBound)) {
        return false;
      }
    }

    return true;
  }

  template<class T>
  bool DifferentElements(vector<T> elementsA, vector<T> elementsB) {
    for(int i = 0; i < elementsA.size(); i++) {
      if (elementsA[i] == elementsB[i]) return false;
    }

    return true;
  }

  template<class T>
  bool UniquePairs(vector<T> elementsA, vector<T> elementsB) {
    set<pair<T,T> > visitedElements;

    for(int i = 0; i < elementsA.size(); i++) {
      pair<T,T> currentPair = {min(elementsA[i], elementsB[i]), max(elementsA[i], elementsB[i])};
      if (visitedElements.count(currentPair) > 0) return false;
      visitedElements.insert(currentPair);
    }

    return true;
  }

  int root(int * parent, int u) { return parent[u] = (parent[u] == u? u : root(parent, parent[u]));}
  bool sama(int * parent, int u, int v) {return root(parent, u) == root(parent, v);}
  void uni(int * parent, int u, int v) {parent[root(parent, u)] = root(parent, v);}

  bool Connected(vector<int> u, vector<int> v, int n) {
    int parent[n+1];

    for(int i = 1; i <= n; i++) {
      parent[i] = i;
    }

    for(int i = 0; i < u.size(); i++) {
      uni(parent, u[i], v[i]);
    }

    int akar = root(parent, 1);
    for(int i = 2; i <= n; i++) {
      if (root(parent, i) != akar) return false;
    }

    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Input({
      "3 3",
      "0",
      "0"
    });
    Output({
      "5"
    });
  }

  void BeforeTestCase() {
    U.clear();
  }

  void TestCases() {
    CASE(N = 1; X = 1);
    CASE(N = 1; X = MAXX);

    CASE(N = 2; X = 1; linearTree());
    CASE(N = 2; X = MAXX; linearTree());

    CASE(N = MAXN; X = 1; starTree());
    CASE(N = MAXN; X = 1; linearTree());
    CASE(N = MAXN; X = 1; sqrtStarTree());
    CASE(N = MAXN; X = 1; randomTree());

    // MAX CASE
    CASE(N = MAXN; X = MAXX; starTree());
    CASE(N = MAXN; X = MAXX; linearTree());
    CASE(N = MAXN; X = MAXX; sqrtStarTree());
    CASE(N = MAXN; X = MAXX; randomTree());

    for(int i = 0;i < 3; ++i){
      CASE(N = MAXN; X = rnd.nextInt(1, MAXX); starTree());
      CASE(N = MAXN; X = rnd.nextInt(1, MAXX); linearTree());
      CASE(N = MAXN; X = rnd.nextInt(1, MAXX); sqrtStarTree());
      CASE(N = MAXN; X = rnd.nextInt(1, MAXX); randomTree());
    }

    for(int i = 0;i < 3; ++i){
      CASE(N = rnd.nextInt(1, MAXN); X = MAXX; starTree());
      CASE(N = rnd.nextInt(1, MAXN); X = MAXX; linearTree());
      CASE(N = rnd.nextInt(1, MAXN); X = MAXX; sqrtStarTree());
      CASE(N = rnd.nextInt(1, MAXN); X = MAXX; randomTree());
    }

    for(int i = 0;i < 3; ++i){
      CASE(N = rnd.nextInt(1, MAXN); X = rnd.nextInt(1, MAXX); starTree());
      CASE(N = rnd.nextInt(1, MAXN); X = rnd.nextInt(1, MAXX); linearTree());
      CASE(N = rnd.nextInt(1, MAXN); X = rnd.nextInt(1, MAXX); sqrtStarTree());
      CASE(N = rnd.nextInt(1, MAXN); X = rnd.nextInt(1, MAXX); randomTree());
    }
  }

private:
  void linearTree(){
    for(int i = 1;i < N; ++i) U.push_back(i - 1);
  }

  void starTree(){
    for(int i = 1;i < N; ++i) U.push_back(0);
  }

  void sqrtStarTree(){
    int len = (int) sqrt(N - 1);
    int now = 0;
    for(int i = 1;i < N; ++i){
      if(now % len == 0) U.push_back(0);
      else U.push_back(i - 1);
      now++;
    }
  }
  void randomTree(){
    for(int i = 1;i < N; ++i) U.push_back(rnd.nextInt(i));
  }
};
