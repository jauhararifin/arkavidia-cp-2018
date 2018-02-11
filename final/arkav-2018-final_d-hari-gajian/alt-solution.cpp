#include <bits/stdc++.h>

using namespace std;

const int N = 5005;
const int mod = 1e9 + 7;

vector<int> edge[N];
// last - sum
int dp[N][N];
int sub[N];

void dfs(int now) {
  sub[now] = 1;
  for (auto it : edge[now]) {
    dfs(it);
    sub[now] += sub[it];
  }
}

void add(int& at, int val) {
  at += val;
  if (at >= mod) at -= mod;
}

int main() {
  int n, x;
  scanf("%d %d", &n, &x);
  for (int i = 1; i < n; i++) {
    int v;
    scanf("%d", &v);
    edge[v].push_back(i);
  }
  dfs(0);
  
  dp[0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j + sub[i] <= x; j++) {
      add(dp[i][j + sub[i]], dp[i][j]);
    }
    for (int j = 0; j <= x; j++) {
      add(dp[i + 1][j], dp[i][j]);
    }
  } 
  cout << dp[n][x] << endl;
  return 0;
}