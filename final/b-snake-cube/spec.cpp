#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N;
  vector<int> A;

  string result;
  void InputFormat() {
    LINE(N);
    LINE(A % SIZE(N));
  }

  void OutputFormat() {
    LINE(result);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS((int) A.size() == N);
    CONS(ElementsBetween(A, 2, 3));
    CONS(SumEqual(A, 27 + N - 1));
  }


private:
  template<class T>
  bool SumEqual(vector<T> elements, T sum){
    T sumElements = 0;
    for (T element : elements) {
      sumElements += element;
    }
    return sumElements == sum;
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
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Input({
      "17",
      "3 2 2 3 2 3 2 2 3 3 2 2 2 3 3 3 3"
    });
    Output({
      "Ya"
    });
  }

  void BeforeTestCase() {
    A.clear();
  }

  void TestCases() {
    // RANDOM CASE
    for (int i = 0; i < 50; ++i) {
      CASE(randomSnake());
    }

    // RANDOM YES CASES
    for (int i = 0; i < 30; ++i) {
      CASE(randomHamiltonianPath());
    }

    // BRUTE FORCE KILLER
    // NO SOLUTION WITH HUGE SEARCH SPACE
    CASE(N = 26, A = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2});
    for (int i = 0; i < 25; ++i) {
      CASE(oneThreeSegment(i));
    }
  }

private:
  void randomSnake() {
    N = 1;
    A.push_back(rnd.nextInt(2, 3));
    int sum = A[0];
    while (sum != 27) {
      int nxt = rnd.nextInt(2, 3);
      if (sum + nxt - 1 <= 27) {
        A.push_back(nxt);
        sum += nxt - 1;
        N++;
      }
    }
  }

  void randomHamiltonianPath() {
    int dx[6], dy[6], dz[6];
    dx[0] = 0; dy[0] = 0; dz[0] = 1;
    dx[1] = 0; dy[1] = 0; dz[1] = -1;
    dx[2] = 0; dy[2] = 1; dz[2] = 0;
    dx[3] = 0; dy[3] = -1; dz[3] = 0;
    dx[4] = 1; dy[4] = 0; dz[4] = 0;
    dx[5] = -1; dy[5] = 0; dz[5] = 0;

    vector<int> dirs;
    bool found = false;
    while (!found) {
      int vis[3][3][3] = {0}, c;
      int x = rnd.nextInt(3), y = rnd.nextInt(3), z = rnd.nextInt(3);
      vis[x][y][z] = 1, c = 1;
      found = true;
      dirs.clear();
      while (c < 27) {
        vector<int> candidates;
        for (int d = 0; d < 6; ++d) {
          int nx = x + dx[d];
          int ny = y + dy[d];
          int nz = z + dz[d];
          if (0 <= nx && nx < 3 && 0 <= ny && ny < 3 && 0 <= nz && nz < 3 && !vis[nx][ny][nz]) {
            candidates.push_back(d);
          }
        }
        if (candidates.empty()) {
          found = false;
          break;
        }
        c++;
        int d = candidates[rnd.nextInt((int)candidates.size())];
        dirs.push_back(d);
        x += dx[d];
        y += dy[d];
        z += dz[d];
        vis[x][y][z] = 1;
      }
    }

    int len = 2;
    for (int i = 1; i < (int)dirs.size(); ++i) {
      if (dirs[i] == dirs[i - 1]) {
        len++;
      } else {
        A.push_back(len);
        len = 2;
      }
    }
    A.push_back(len);
    N = (int)A.size();
  }

  // include a single segment of length tree at position k
  void oneThreeSegment(int k) {
    N = 25;
    for (int i = 0; i < 25; ++i) {
      if (i == k) {
        A.push_back(3);
      } else {
        A.push_back(2);
      }
    }
  }
};
