#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

long long a[N];

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) scanf("%lld", a + i);
    while (q--) {
      int x;
      scanf("%d", &x);
      long long ans = 0;
      for (int i = 0; i < n; i++) {
        ans += (a[i] % x) * (a[i] % x);
      }
      printf("%lld\n", ans);
    }
  }
  return 0;
}