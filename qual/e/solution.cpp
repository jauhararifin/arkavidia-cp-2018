#include <bits/stdc++.h>

using namespace std;

const int N = 2e6 + 5;
const int MAX = 1e6;

long long sum2[N], sum[N], cnt[N];
long long ans[N];

long long find(long long* a, int l, int r) {
  if (l > r) return 0;
  return a[r] - (l == 0? 0 : a[l - 1]);
}

int main() {
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
  for (int x = 1; x <= MAX; x++) {
    for (int i = 0; i <= MAX; i += x) {
      ans[x] += find(sum2, i, i + x - 1) - 2 * find(sum, i, i + x - 1) * x + find(cnt, i, i + x - 1) * x * x;
    }
  }
  while (q--) {
    int x;
    scanf("%d", &x);
    printf("%lld\n", ans[x]);
  }
  return 0;
}
