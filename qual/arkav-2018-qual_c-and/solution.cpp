#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int rmq[N][20];

int solve(int l, int r) {
  int g = __builtin_clz(r - l + 1) ^ 31;
  return rmq[l][g] & rmq[r-(1<<g)+1][g];
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &rmq[i][0]);
    for (int j = 1; (1 << j) <= n; j++) {
      for (int i = 0; i + (1 << j) <= n; i++) {
        rmq[i][j] = (rmq[i][j-1] & rmq[i+(1<<(j-1))][j-1]);
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
