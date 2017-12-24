#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

int a[N];

int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; i++) scanf("%d", a + i);
  
  int q;
  scanf("%d", &q);
  while (q--) {
    int l, r;
    scanf("%d %d", &l, &r);
    l--; r--;
    int ans = a[l];
    for (int i = l; i <= r; i++) ans &= a[i];
    printf("%d\n", ans);
  }
  return 0;
}

