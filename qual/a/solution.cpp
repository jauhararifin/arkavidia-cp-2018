#include <bits/stdc++.h>

using namespace std;

int t,n,m,x;
long long sum;

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		m = 2000000000;
		sum = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			m = min(x, m);
			sum += x;
		}
		printf("%lld\n", sum - (long long) m * (long long) n);
	}
	return 0;
}