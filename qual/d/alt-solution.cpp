#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int a[N], dp[N];

int main() {
  int t;
  scanf("%d", &t);
  assert(1 <= t && t <= 20);
  while (t--) {
    int n, k;
    scanf("%d %d", &n, &k);
    assert(1 <= k && k <= n && n <= int(1e5));
    for (int i = 1; i <= n; ++i)
      scanf("%d", a+i);
    sort(a+1, a+n+1);
    int ans = a[n] - a[1];
    dp[0] = 0;
    for (int i = 1; i <= n-k; ++i) {
      dp[i] = dp[i-1];
      if (i-k >= 0)
        dp[i] = max(dp[i], dp[i-k] + a[i+1] - a[i]);
    }
    printf("%d\n", ans - dp[n-k]);
  }
  return 0;
}