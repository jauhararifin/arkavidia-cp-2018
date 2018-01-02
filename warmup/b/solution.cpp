#include <bits/stdc++.h>

using namespace std;

int t;
long long fibo[1001];

int main() {
	fibo[1] = fibo[2] = 1;
	for (int i = 3; i <= 1000; i++)
		fibo[i] = ((fibo[i-1] % 1000000007) + (fibo[i-2] % 1000000007)) % 1000000007;
	scanf("%d", &t);
	while (t--) {
		int n; scanf("%d", &n);
		printf("%lld\n", fibo[n] % 1000000007);
	}
	return 0;
}