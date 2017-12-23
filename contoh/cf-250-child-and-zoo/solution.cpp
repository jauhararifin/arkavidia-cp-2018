#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> par, size;

inline void initSet(int n) {
  par.resize(n);
  for (int i = 0; i < n; i++) par[i] = i;
  size.assign(n, 1);
}

inline int find(int x) {
  if (par[x] != x) par[x] = find(par[x]);
  return par[x];
}

inline void merge(int x, int y) {
  if (size[x] < size[y]) {
    par[x] = y;
    size[y] += size[x];
  } else {
    par[y] = x;
    size[x] += size[y];
  }
}

bool cmp(const pair<int, pair<int, int>> &a, const pair<int, pair<int, int>> &b) {
  return a.first > b.first;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m; cin >> n >> m;
  initSet(n);
  vector<int> w(n);
  for (int i = 0; i < n; i++) cin >> w[i];
  vector<pair<int, pair<int, int>>> e(m);
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    e[i] = {min(w[u], w[v]), {u, v}};
  }
  long long total = 0;
  sort(begin(e), end(e), cmp);
  for (int i = 0; i < m; i++) {
    int w = e[i].first, u = e[i].second.first, v = e[i].second.second;
    u = find(u); v = find(v);
    if (u == v) continue;
    total += 2LL * size[u] * size[v] * w;
    merge(u, v);
  }
  cout << fixed << setprecision(8) << total/((double)n*(n-1)) << endl;
  return 0;
}
