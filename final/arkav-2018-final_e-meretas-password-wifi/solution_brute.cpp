// Complexity: O(QN)
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int a[N], b[N];

int main() {
  int n, q;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d %d", a+i, b+i);
  scanf("%d", &q);
  while (q--) {
    int l, r, t;
    scanf("%d %d %d", &l, &r, &t);
    --l;
    long long ans = 0;
    for (int i = l; i < r; ++i) {
      ans = max(ans, 1LL * b[i] * t + a[i]);
    }
    printf("%lld\n", ans);
  }
  return 0;
}