#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const long long inf = 2e18;

long long bit[N];
int a[N];

void update(int i, long long val) {
  for (; i < N; i |= i + 1) bit[i] = min(bit[i], val);
}

long long find(int i) {
  long long ret = inf;
  for (; i >= 0; i = (i & (i + 1)) - 1) ret = min(ret, bit[i]);
  return ret;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    fill(bit, bit + N, inf);

    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    sort(a + 1, a + 1 + n);
    update(k, -a[1]);
    for (int i = 0; i + k <= n; i++) {
      long long now = find(i) + a[i] - a[i + 1];
      update(i + k, now);
    }
    printf("%lld\n", find(n) + a[n]);
  }
  return 0;
}
