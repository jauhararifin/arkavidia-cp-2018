#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
const int MAGIC = 450;

int a[N], dp[MAGIC];

int solve(int l, int r) {
  int bl = l / MAGIC;
  int br = r / MAGIC;
  if (bl == br) {
    int ans = a[l];
    for (int i = l; i <= r; i++) ans &= a[i];
    return ans;
    
  } else if (bl + 1 == br) {
    return solve(l, br * MAGIC - 1) & solve(br * MAGIC, r);
    
  } else {
    int ret = a[l];
    for (int i = bl + 1; i < br; i++) ret &= dp[i];
    return ret & solve(l, (bl + 1) * MAGIC - 1) & solve(br * MAGIC, r);
    
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    for (int i = 0; i < n; i += MAGIC) {
      int b = i / MAGIC;
      dp[b] = a[i];
      for (int j = 0; j < MAGIC && i + j < n; j++) {
        dp[b] = (dp[b] & a[i + j]);
      }
    }
    
    int q;
    scanf("%d", &q);
    while (q--) {
      int l, r;
      scanf("%d %d", &l, &r);
      l--; r--;
      printf("%d\n", solve(l, r));
    }
  }
  return 0;
}

