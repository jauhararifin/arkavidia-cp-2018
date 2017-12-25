#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T, N, Q;
    vector<int> a,b,c,r;

    void InputFormat() {
        LINE(N);
        LINE(a);
        LINE(b);
        LINE(Q);
        LINES(c) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(c) % SIZE(Q);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
        OutputPrefix("");
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 20);
    }

    void Constraints() {
        CONS(1 <= N <= 50000);
        CONS(1 <= Q <= 100000);
        for (int x : a)
            CONS(0 <= x <= 50000);
        for (int x : b)
            CONS(0 <= x <= 50000);
        for (int x : c)
        	CONS(0 <= x);
       	CONS(unique(a));
       	CONS(unique(b));
    }

private:
	bool unique(const vector<int> &a) {
		unordered_set<int> st;
		for (int x : a)
			st.insert(x);
		return a.size() == st.size();
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "5",
            "1 6 2 3 4",
            "8 2 4 5 7",
            "3",
            "3",
            "6",
            "5"
        });
        Output({
            "1",
            "3",
            "2"
        });
    }

    void BeforeTestCase() {
        a.clear();
        b.clear();
        c.clear();
    }

    void AfterTestCase() {
    	random_shuffle(a.begin(), a.end());
    	random_shuffle(b.begin(), b.end());
    	random_shuffle(c.begin(), c.end());
    }

    void TestCases() {
    	CASE(N = 1, a = {0}, b = {0}, Q = 7, c = {0,1,2,3,4,100,1000000});
    	CASE(N = 4, a = {0,1,2,3}, b = {9,8,7,6}, Q = {10}, c = {0,1,2,3,6,7,8,9,100,200});
    	CASE(N = 3, a = {4,7,1}, b = {0,1,5}, Q = {12}, c = {4,5,9,7,8,12,1,2,6,0,15,1000000});
    	CASE(N = 5, a = {1, 7, 8, 9, 11}, b = {12, 6, 5, 4, 2}, Q = {12}, c = {4,5,9,7,8,13,1,2,6,0,15,1000000});
    	CASE(random_with_max_a_b(10, 20, 50));
    	CASE(random_with_max_a_b(20, 20, 50));
    	CASE(random_with_max_a_b(50, 100, 50));
    	CASE(random_with_max_a_b(100, 1000, 400));
    	CASE(random_with_max_a_b(200, 1000, 400));
    	CASE(random_with_max_a_b(500, 1000, 400));
    	CASE(random_with_max_a_b(1000, 10000, 2000));
    	CASE(random_with_max_a_b(2000, 10000, 4000));
    	CASE(random_with_max_a_b(5000, 10000, 10000));
    	CASE(random_with_max_a_b(10000, 50000, 100000));
    	CASE(random_with_max_a_b(20000, 50000, 100000));
    	CASE(random_tc(10000, 20000));
    	CASE(random_tc(20000, 30000));
    	CASE(worst_tc());
    }

private:
	void random_with_max_a_b(int N, int maxab, int Q) {
		vector<int> numbers;
		for (int i = 0; i <= maxab; i++)
			numbers.push_back(i);

		this->N = N;
		this->Q = Q;

		swap(numbers[0], numbers[numbers.size() - 1]);
		random_shuffle(numbers.begin() + 1, numbers.end());
		for (int i = 0; i < N; i++)
			a.push_back(numbers[i]);
		random_shuffle(numbers.begin() + 1, numbers.end());
		for (int i = 0; i < N; i++)
			b.push_back(numbers[i]);

		for (int i = 0; i < Q/3; i++)
			c.push_back(abs(rand()));
		for (int i = 0; i < Q/3; i++)
			c.push_back(abs(rand()) % (maxab + 1));
		while (c.size() < Q) {
			int va = a[rand() % a.size()];
			int vb = b[rand() % b.size()];
			c.push_back(va + vb);
		}
	}

	void random_tc(int N, int Q) { // N > Q
		this->N = N;
		this->Q = Q;

		vector<int> numbers;
		for (int i = 0; i < 50000; i++)
			numbers.push_back(i);
		random_shuffle(numbers.begin(), numbers.end());
		for (int i = 0; i < N; i++)
			a.push_back(numbers[i]);
		random_shuffle(numbers.begin(), numbers.end());
		for (int i = 0; i < N; i++)
			b.push_back(numbers[i]);

		unordered_set<int> used;
		for (int i = 0; i < Q; i++) {
			int va = a[rand() % a.size()];
			int vb = b[rand() % b.size()];
			used.insert(va + vb);
		}

		if (used.size() < Q)
			used.insert(0);

		while (used.size() < Q)
			used.insert(abs(rand()));

		for (int x : used)
			c.push_back(x);
	}

	void worst_tc() {
		N = 50000;
		for (int i = 0; i < 50000; i++)
			a.push_back(i), b.push_back(i);
		random_shuffle(a.begin(), a.end());
		random_shuffle(b.begin(), b.end());
		Q = 100000;
		for (int i = 0; i < 50000; i++)
			c.push_back(i), c.push_back(99998-i);
	}
};