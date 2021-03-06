#include <bits/stdc++.h>

using namespace std;

const int N = 4e5 + 500;
const int MAX = 2e5 + 1;
const int MAGIC = 450;

long long sum2[N], sum[N], cnt[N];
long long ans[N];
int a[N], n;

long long find(long long* a, int l, int r) {
  if (l > r) return 0;
  return a[r] - (l == 0? 0 : a[l - 1]);
}

long long solve(int x) {
  if (ans[x] != -1) return ans[x];
  ans[x] = 0;
  if (x < MAGIC) {
    for (int i = 0; i < n; i++) {
      ans[x] += (a[i] % x) * (a[i] % x);
    }
  } else {
    for (int i = 0; i <= MAX; i += x) {
      ans[x] += find(sum2, i, i + x - 1) - 2 * find(sum, i, i + x - 1) * i + find(cnt, i, i + x - 1) * i * i;
    }
  }
  return ans[x];
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    memset(sum2, 0, sizeof(sum2));
    memset(sum, 0, sizeof(sum));
    memset(cnt, 0, sizeof(cnt));
    memset(ans, 0, sizeof(ans));

    int q;
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
      int v;
      scanf("%d", &v);
      cnt[v] += 1;
      sum[v] += v;
      sum2[v] += 1LL * v * v;
      a[i] = v;
    }
    for (int i = 1; i < N; i++) {
      cnt[i] += cnt[i-1];
      sum[i] += sum[i-1];
      sum2[i] += sum2[i-1];
    }
    memset(ans, -1, sizeof(ans));
    while (q--) {
      int x;
      scanf("%d", &x);
      if (x > MAX) x = MAX;
      printf("%lld\n", solve(x));
    }
  }
  return 0;
}
