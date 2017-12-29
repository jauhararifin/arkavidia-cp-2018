#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

long long sum2[N], sum[N], cnt[N];
long long ans[N];

long long get(long long * a, int l, int r) {
  if (r >= N) r = N-1;
  if (l < 0) l = 0;
  return a[r] - a[l];
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, q;
    scanf("%d %d", &n, &q);
    memset(cnt, 0, sizeof cnt);
    memset(sum, 0, sizeof sum);
    memset(sum2, 0, sizeof sum2);
    for (int i = 0; i < n; ++i) {
      int x;
      scanf("%d", &x);
      cnt[x] += 1;
      sum[x] += x;
      sum2[x] += 1LL * x * x;
    }
    for (int i = 1; i < N; ++i) {
      cnt[i] += cnt[i-1];
      sum[i] += sum[i-1];
      sum2[i] += sum2[i-1];
    }
    memset(ans, -1, sizeof ans);
    while (q--) {
      int x;
      scanf("%d", &x);
      x = min(x, N-1);
      if (ans[x] == -1) {
        ans[x] = 0;
        for (int i = 0; i < N; i += x) {
          ans[x] += get(sum2, i-1, i+x-1) - 2LL * get(sum, i-1, i+x-1) * i + 1LL * i * i * get(cnt, i-1, i+x-1);
        }
      }
      printf("%lld\n", ans[x]);
    }
  }

  return 0;
}