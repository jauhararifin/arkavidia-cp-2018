#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int a[N];
long long s[N];

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    sort(a, a + n);
    vector<pair<int, int>> p;
    for (int i = 0; i < n; i++) {
      int j = i;
      while (j + 1 < n && a[j + 1] == a[j]) j++;
      p.emplace_back(a[j], j - i + 1);
      i = j;
    }
    for (int i = 0; i < p.size(); i++) {
      s[i] = 1LL * p[i].first * p[i].first * p[i].second;
      if (i) s[i] += s[i-1];
    }
    while (q--) {
      int x;
      scanf("%d", &x);
      int l = lower_bound(p.begin(), p.end(), make_pair(x, -1)) - p.begin();
      long long ans = (l? s[l-1] : 0);
      for (int i = l; i < p.size(); i++) {
        ans += (p[i].first % x) * (p[i].first % x) * p[i].second;
      }
      printf("%lld\n", ans);
    }
  }
  return 0;
}