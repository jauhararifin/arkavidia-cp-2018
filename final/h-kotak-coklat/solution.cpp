#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

vector<pair<int, int>> all;

int id(int x, int y) {
  return lower_bound(all.begin(), all.end(), make_pair(x, y)) - all.begin();
}

struct segtree {
  segtree() {
    x.resize(all.size() << 2);
    y.resize(all.size() << 2);
    a.resize(all.size() << 2);
    build(1, 0, all.size() - 1);
  }
  void build(int p, int l, int r) {
    x[p].resize(r - l + 1);
    y[p].resize(r - l + 1);
    a[p].resize(r - l + 1);
    for (int i = l; i <= r; i++) {
      x[p][i-l] = all[i].first;
      y[p][i-l] = all[i].second;
      a[p][i-l] = 0;
    }
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(p + p, l, mid);
    build(p + p + 1, mid + 1, r);
  }
  void add_bit(int p, int i, int val) {
    for (; i < x[p].size(); i |= i + 1) {
      a[p][i] += val;
    }
  }
  int find_bit(int p, int i) {
    int ret = 0;
    for (; i >= 0; i = (i & (i + 1)) - 1) {
      ret += a[p][i];
    }
    return ret;
  }
  int find_bit(int p, int l, int r) {
    return find_bit(p, r) - find_bit(p, l - 1);
  }

  void update(int at, int val) {
    update(1, 0, all.size() - 1, at, val);
  }
  void update(int p, int l, int r, int at, int val) {
    add_bit(p, at - l, val);
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (at <= mid) {
      update(p + p, l, mid, at, val);
    } else {
      update(p + p + 1, mid + 1, r, at, val);
    } 
  }

  int find(int p1, int q1, int p2, int q2) {
    return find(1, 0, all.size() - 1, p1, p2, q1, q2);
  }
  int find(int p, int l, int r, int p1, int p2, int q1, int q2) {
    if (x[p].back() < p1 || p2 < x[p][0]) return 0;
    if (p1 <= x[p][0] && x[p].back() <= p2) {
      int rig = upper_bound(y[p].begin(), y[p].end(), q2) - y[p].begin() - 1;
      int lef = lower_bound(y[p].begin(), y[p].end(), q1) - y[p].begin();
      return find_bit(p, lef, rig);
    }
    int mid = (l + r) >> 1;
    return find(p + p, l, mid, p1, p2, q1, q2) + find(p + p + 1, mid + 1, r, p1, p2, q1, q2);
  }
  vector<vector<int>> x, y, a;
};

int t[N], p1[N], q1[N], p2[N], q2[N];

int main() {
  int n, q;
  scanf("%d %d", &n, &q);
  for (int i = 0; i < q; i++) {
    scanf("%d", t + i);
    if (t[i] <= 2) {
      scanf("%d %d", p1 + i, q1 + i);
      all.emplace_back(p1[i], q1[i]);
    } else {
      scanf("%d %d %d %d", p1 + i, q1 + i, p2 + i, q2 + i);
      all.emplace_back(p1[i], q1[i]);
      all.emplace_back(p2[i], q2[i]);
    }
  }
  sort(all.begin(), all.end());
  all.resize(distance(all.begin(), unique(all.begin(), all.end())));
  segtree seg;
  for (int i = 0; i < q; i++) {
    int at = id(p1[i], q1[i]);
    if (t[i] == 1) {
      seg.update(at, 1);
    } else if (t[i] == 2) {
      seg.update(at, -1);
    } else {
      printf("%d\n", seg.find(p1[i], q1[i], p2[i], q2[i]));
    }
  }
  return 0;
}