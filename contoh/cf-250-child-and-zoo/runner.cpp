#include "tcframe/runner.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class Problem : public BaseProblem {
 protected:
  int N, M;
  double result;
  vector<int> A;
  vector<int> U, V;

  void InputFormat() {
    LINE(N, M);
    LINE(A % SIZE(N));
    LINES(U, V) % SIZE(M);
  }

  void OutputFormat() {
    LINE(result);
  }

  void Subtask1() {
    CONS(2 <= N && N <= 100);
    CONS(0 <= M && M <= 300);
    CONS(eachElementBetween(A, 0, 1e5));
    CONS(simple(U, V));
    CONS(connected(N, U, V));
  }

  void Subtask2() {
    CONS(2 <= N && N <= 1000);
    CONS(0 <= M && M <= 3000);
    CONS(eachElementBetween(A, 0, 1e5));
    CONS(simple(U, V));
    CONS(connected(N, U, V));
  }

  void Subtask3() {
    CONS(2 <= N && N <= 100000);
    CONS(M == N - 1);
    CONS(eachElementBetween(A, 0, 1e5));
    CONS(simple(U, V));
    CONS(connected(N, U, V));
  }

  void Subtask4() {
    CONS(2 <= N && N <= 100000);
    CONS(0 <= M && M <= 100000);
    CONS(eachElementBetween(A, 0, 1e5));
    CONS(simple(U, V));
    CONS(connected(N, U, V));
  }

private:

  bool eachElementBetween(const vector<int> &A, int lo, int hi) {
    for (int it : A) {
      if (it < lo || it > hi) {
        return false;
      }
    }
    return true;
  }

  bool simple(const vector<int> &U, const vector<int> &V) {
    set<pair<int, int>> edges;
    int m = U.size();
    for (int i = 0; i < m; i++) {
      if (U[i] > V[i]) {
        edges.emplace(V[i], U[i]);
      } else if (U[i] < V[i]) {
        edges.emplace(U[i], V[i]);
      } else {
        return false;
      }
    }
    return (int)edges.size() == M;
  }

  bool connected(int N, const vector<int> &U, const vector<int> &V) {
    vector<vector<int>> adj(N);
    for (int i = 0; i < (int)U.size(); i++) {
      adj[U[i]].push_back(V[i]);
      adj[V[i]].push_back(U[i]);
    }
    vector<bool> visited(N, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v : adj[u]) {
        if (!visited[v]) {
          visited[v] = true;
          q.push(v);
        }
      }
    }
    return count(begin(visited), end(visited), true) == N;
  }
};

class Generator : public BaseGenerator<Problem> {
protected:
  void Config() {
    setSlug("cf-250-child-and-zoo");
  }

  void SampleTestCases() {
    SAMPLE_CASE({"2 1", "155 155", "0 1"}, {1, 2, 3, 4});
    SAMPLE_CASE({"3 3", "4 5 6", "0 1", "0 2", "1 2"}, {1, 2, 4});
  }

  void TestGroup1() { //tree kecil
    assignToSubtasks({1, 2, 3, 4});

    CASE(N = 2; M = 0; uniformArray(N, 155); randomTree(N));
    CASE(N = 2; M = N - 1; uniformArray(N, 1); randomTree(N));
    CASE(N = 2; M = N - 1; uniformArray(N, 100000); randomTree(N));
    CASE(N = nextInt(2, 5); M = N - 1; uniformArray(N, 12345); randomTree(N));
    CASE(N = nextInt(1, 70); M = N - 1; randomArray(N, 1, 1e5); randomTree(N));
    CASE(N = nextInt(1, 100); M = N - 1; randomArray(N, 1, 333); randomTree(N));
    CASE(N = nextInt(50, 100); M = N - 1; randomArray(N, 1, 10); randomTree(N));
    CASE(N = nextInt(70, 100); M = N - 1; randomArray(N, 1, 1e5); randomTree(N));
    CASE(N = 31; M = 30; randomArray(N, 1, 1e5); fullBinaryTree(5));
    CASE(N = 10; M = 9; randomArray(N, 1, 1e5); lineGraph(10));
    CASE(N = 70; M = 69; randomArray(N, 99, 1e5); lineGraph(70));
    CASE(N = 100; M = 99; randomArray(N, 1e4, 1e5); lineGraph(100));
    CASE(N = 100; M = 99; randomArray(N, 1e4, 1e5); starGraph(100));
  }

  void TestGroup2() { //graf kecil
    assignToSubtasks({1, 2, 4});

    CASE(N = 5; M = 4; uniformArray(N, 155); randomTree(N); addEdge(N, 300); M = U.size());
    CASE(N = 5; M = 4; uniformArray(N, 1); randomTree(N); addEdge(N, 300); M = U.size());
    CASE(N = 5; M = 4; uniformArray(N, 100000); randomTree(N); addEdge(N, 300); M = U.size());
    CASE(N = nextInt(2, 5); uniformArray(N, 12345); randomTree(N); addEdge(N, 300); M = U.size());
    CASE(N = nextInt(1, 70); randomArray(N, 1, 1e5); randomTree(N); addEdge(N, 300); M = U.size());
    CASE(N = nextInt(1, 100); randomArray(N, 1, 333); randomTree(N); addEdge(N, 300); M = U.size());
    CASE(N = nextInt(50, 100); randomArray(N, 1, 10); randomTree(N); addEdge(N, 300); M = U.size());
    CASE(N = nextInt(70, 100); randomArray(N, 1, 1e5); randomTree(N); addEdge(N, 300); M = U.size());
    CASE(N = 31; randomArray(N, 1, 1e5); fullBinaryTree(5); addEdge(N, 300); M = U.size());
    CASE(N = 10; randomArray(N, 1, 1e5); lineGraph(10); addEdge(N, 300); M = U.size());
    CASE(N = 70; uniformArray(N, 1e4); lineGraph(70); addEdge(N, 300); M = U.size());
    CASE(N = 100; randomArray(N, 1, 555); lineGraph(100); addEdge(N, 300); M = U.size());
    CASE(N = 100; randomArray(N, 1, 555); starGraph(100); addEdge(N, 300); M = U.size());
  }

  void TestGroup3() { //graf sedang
    assignToSubtasks({2, 4});

    CASE(N = 500; uniformArray(N, 155); randomTree(N); addEdge(N, 3000); M = U.size());
    CASE(N = 499; uniformArray(N, 1); randomTree(N); addEdge(N, 3000); M = U.size());
    CASE(N = 700; uniformArray(N, 100000); randomTree(N); addEdge(N, 3000); M = U.size());
    CASE(N = nextInt(200, 500); uniformArray(N, 12345); randomTree(N); addEdge(N, 3000); M = U.size());
    CASE(N = nextInt(101, 700); randomArray(N, 1, 1e5); randomTree(N); addEdge(N, 3000); M = U.size());
    CASE(N = nextInt(101, 1000); randomArray(N, 1, 333); randomTree(N); addEdge(N, 3000); M = U.size());
    CASE(N = nextInt(500, 1000); randomArray(N, 1, 10); randomTree(N); addEdge(N, 3000); M = U.size());
    CASE(N = nextInt(700, 1000); randomArray(N, 1, 1e5); randomTree(N); addEdge(N, 3000); M = U.size());
    CASE(N = 255; randomArray(N, 1, 1e5); fullBinaryTree(8); addEdge(N, 3000); M = U.size());
    CASE(N = 101; randomArray(N, 1, 1e5); lineGraph(10); addEdge(N, 3000); M = U.size());
    CASE(N = 790; randomArray(N, 1, 1e5); lineGraph(790); addEdge(N, 3000); M = U.size());
    CASE(N = 753; uniformArray(N, 2e4); lineGraph(753); addEdge(N, 3000); M = U.size());
    CASE(N = 1000; uniformArray(N, 2e4); lineGraph(1000); addEdge(N, 3000); M = U.size());
  }

  void TestGroup4() { //tree gede
    assignToSubtasks({3, 4});

    CASE(N = 1500; M = 1499; uniformArray(N, 13575); randomTree(N));
    CASE(N = 2001; M = 2000; uniformArray(N, 1e5); randomTree(N));
    CASE(N = 10000; M = 9999; uniformArray(N, 4e4); randomTree(N));
    CASE(N = 10000; M = 9999; randomArray(N, 1, 5e4); randomTree(N));
    CASE(N = 50000; M = 49999; uniformArray(N, 4e4+76); randomTree(N));
    CASE(N = 50000; M = 49999; randomArray(N, 3e4, 4e4+76); randomTree(N));
    CASE(N = 100000; M = 99999; uniformArray(N, 1e5); randomTree(N));
    CASE(N = 100000; M = 99999; randomArray(N, 2e4, 1e5); randomTree(N));
    CASE(N = 65535; M = 65534; uniformArray(N, 33333); fullBinaryTree(16));
    CASE(N = 97000; M = 96999; randomArray(N, 2e4, 1e5); lineGraph(N));
    CASE(N = 97000; M = 96999; randomArray(N, 2e4, 1e5); starGraph(N));
    CASE(N = 97000; randomArray(N, 2e4, 1e5); starGraph(N));
  }

  void TestGroup5() { //graf gede
    assignToSubtasks({4});

    CASE(N = 1500; uniformArray(N, 13575); randomTree(N); addEdge(N, 100000); M = U.size());
    CASE(N = 2001; uniformArray(N, 1e5); randomTree(N); addEdge(N, 100000); M = U.size());
    CASE(N = 10000; uniformArray(N, 4e4); randomTree(N); addEdge(N, 100000); M = U.size());
    CASE(N = 10000; randomArray(N, 1, 5e4); randomTree(N); addEdge(N, 100000); M = U.size());
    CASE(N = 50000; uniformArray(N, 4e4+76); randomTree(N); addEdge(N, 100000); M = U.size());
    CASE(N = 50000; randomArray(N, 3e4, 4e4+76); randomTree(N); addEdge(N, 100000); M = U.size());
    CASE(N = 100000; uniformArray(N, 1e5); randomTree(N); addEdge(N, 100000); M = U.size());
    CASE(N = 100000; randomArray(N, 2e4, 1e5); randomTree(N); addEdge(N, 100000); M = U.size());
    CASE(N = 65535; uniformArray(N, 33333); fullBinaryTree(16); addEdge(N, 100000); M = U.size());
    CASE(N = 97000; randomArray(N, 2e4, 1e5); lineGraph(N); addEdge(N, 100000); M = U.size());
    CASE(N = 97000; randomArray(N, 2e4, 1e5); starGraph(N); addEdge(N, 100000); M = U.size());
  }

private:
  mt19937 mersenne = mt19937(0xfafa);

  void addEdge(int size, int limit) {
    limit -= size - 1;
    set<pair<int, int>> adds;
    if (size >= 5000) {
      for (int i = 0; i + 1 < size; i++) {
        for (int j = 0; j < 10; j++) {
          adds.emplace(i, nextInt(i + 1, size - 1));
        }
      }
    } else {
      for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
          adds.emplace(i, j);
        }
      }
    }
    for (int i = 0; i < (int)U.size(); i++) {
      int u = U[i], v = V[i];
      if (u > v) swap(u, v);
      auto it = adds.find({u, v});
      if (it != adds.end()) {
        adds.erase(it);
      }
    }
    int take = nextInt((limit + 1) / 2, limit);
    vector<pair<int, int>> add;
    for (auto &it : adds) add.push_back(it);
    assert(add.size() > 0);
    take = min(take, (int)add.size());
    random_shuffle(begin(add), end(add));
    for (int i = 0; i < take; i++) {
      if (i & 1) {
        U.push_back(add[i].first);
        V.push_back(add[i].second);
      } else {
        U.push_back(add[i].second);
        V.push_back(add[i].first);
      }
    }
    if (take == 0) {
      cerr << "GABOLEH " << "n, m = " << N << ' ' << M << endl;
      assert(false);
    }
  }

  void starGraph(int size) {
    int center = nextInt(0, size - 1);
    U.clear(); V.clear();
    for (int i = 0; i < size; i++) {
      if (i != center) {
        U.push_back(center);
        V.push_back(i);
        if (i % 2 == 0) swap(U[i], V[i]);
      }
    }
  }

  void randomArray(int size, int L = 1, int R = 100000) {
    A.clear();
    for (int i = 0; i < size; i++) {
      A.push_back(nextInt(L, R));
    }
  }

  void uniformArray(int size, int value) {
    A.assign(size, value);
  }

  void randomTree(int size) {
    vector<int> order(size);
    iota(begin(order), end(order), 0);
    random_shuffle(begin(order), end(order));
    vector<int> parent(size);
    parent[order[0]] = -1;
    for (int i = 1; i < size; i++) {
      int par = nextInt(0, i - 1);
      parent[order[i]] = order[par];
    }
    U.clear(); V.clear();
    for (int i = 0; i < N; i++) {
      if (parent[i] == -1) {
        continue;
      }
      int u = parent[i], v = i;
      if (nextInt(0, 1)) {
        swap(u, v);
      }
      U.push_back(u);
      V.push_back(v);
    }
    M = N - 1;
  }

  void fullBinaryTree(int h) {
    int n = (1 << h) - 1;
    vector<int> order(n);
    iota(begin(order), end(order), 0);
    random_shuffle(begin(order), end(order));
    U.clear(); V.clear();
    for (int i = 0; i < n; i++) {
      if (i * 2 + 1 < n) {
        U.push_back(order[i]);
        V.push_back(order[i * 2 + 1]);
      }
      if (i * 2 + 2 < n) {
        U.push_back(order[i * 2 + 2]);
        V.push_back(order[i]);
      }
    }
    N = n;
    M = N - 1;
  }

  void lineGraph(int size) {
    vector<int> order(size);
    iota(begin(order), end(order), 0);
    random_shuffle(begin(order), end(order));
    U.clear(); V.clear();
    for (int i = 1; i < size; i++) {
      if (i & 1) {
        U.push_back(order[i - 1]);
        V.push_back(order[i]);
      } else {
        U.push_back(order[i]);
        V.push_back(order[i - 1]);
      }
    }
    M = N - 1;
  }

  int nextInt(int L = 0, int R = 1e5) {
    return L + mersenne() % (R - L + 1);
  }

  void randomArray() {
    A.clear();
    for (int i = 0; i < N; i++) {
      A.push_back(nextInt(-100000, 100000));
    }
  }
};

int main(int argc, char* argv[]) {
  Runner<Problem> runner(argc, argv);

  runner.setGenerator(new Generator());
  return runner.run();
}
