// Complexity: O(NK)
#include <bits/stdc++.h>

using namespace std;

const int N = 5050, mod = 1e9 + 7;

vector<int> child[N];
int sz[N], dp[N][N];

void getSize(int v) {
  sz[v] = 1;
  for (int u : child[v]) {
    getSize(u);
    sz[v] += sz[u];
  }
}

int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; ++i)
    child[i].clear();
  for (int i = 1; i < n; ++i) {
    int p;
    scanf("%d", &p);
    child[p].push_back(i);
  }
  getSize(0);
  dp[0][0] = 1;
  for (int i = 0; i < n; ++i) {
    dp[i][0] = 1;
    for (int j = 1; j <= k; ++j) {
      dp[i][j] = 0;
      if (i)
        dp[i][j] = dp[i-1][j];
      if (j-sz[i] >= 0) {
        dp[i][j] += dp[i][j-sz[i]];
        if (dp[i][j] >= mod) dp[i][j] -= mod;
      }
    }
  }
  printf("%d\n", dp[n-1][k]);
  return 0;
}