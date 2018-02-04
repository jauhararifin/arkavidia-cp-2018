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
    TimeLimit(2);
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
      "YES"
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
};
