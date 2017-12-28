#include <bits/stdc++.h>

using namespace std;

const int N = 4e5 + 500;
const int MAX = 2e5 + 1;

long long sum2[N], sum[N], cnt[N];
long long ans[N];

long long find(long long* a, int l, int r) {
  if (l > r) return 0;
  return a[r] - (l == 0? 0 : a[l - 1]);
}

long long solve(int x) {
  long long ret = 0;
  for (int i = 0; i <= MAX; i += x) {
    ret += find(sum2, i, i + x - 1) - 2 * find(sum, i, i + x - 1) * i + find(cnt, i, i + x - 1) * i * i;
  }
  return ret;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    memset(sum2, 0, sizeof(sum2));
    memset(sum, 0, sizeof(sum));
    memset(cnt, 0, sizeof(cnt));
    memset(ans, 0, sizeof(ans));

    int n, q;
    scanf("%d %d", &n, &q);
    while (n--) {
      int v;
      scanf("%d", &v);
      cnt[v] += 1;
      sum[v] += v;
      sum2[v] += 1LL * v * v;
    }
    for (int i = 1; i < N; i++) {
      cnt[i] += cnt[i-1];
      sum[i] += sum[i-1];
      sum2[i] += sum2[i-1];
    }
    while (q--) {
      int x;
      scanf("%d", &x);
      if (x > MAX) x = MAX;
      printf("%lld\n", solve(x));
    }
  }
  return 0;
}
