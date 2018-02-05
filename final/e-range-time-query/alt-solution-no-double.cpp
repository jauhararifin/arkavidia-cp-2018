#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const double eps = 1e-7;
const long long inf = 1e18;

inline long long fpb(long long a, long long b) {
  return b == 0? a : fpb(b, a % b);
}

struct frac {
  frac() : a(0), b(1) {}
  frac(long long a, long long b) {
    a = abs(a);
    b = abs(b);
    long long g = fpb(a, b);
    a /= g;
    b /= g;
    this->a = a;
    this->b = b;
  }
  bool operator<(frac f) const {
    return a * f.b < b * f.a;
  }
  bool operator==(frac f) const {
    return a * f.b == b * f.a;
  }
  bool operator<=(frac c) const {
    return *this < c || *this == c;
  }
  long long a, b;   // a / b
};

frac cut(int a, int b, int c, int d) {
  return frac(d - b, a - c);
}

struct segtree {
  segtree(vector<pair<int, int>> ori) : ori(ori), n(ori.size()) {
    num.resize(n << 2);
    sorted.resize(n << 2);
    build(1, 0, n - 1);
  }
  void build(int p, int l, int r) {
    vector<pair<int, int>> grad;    // gradien - constant
    for (int i = l; i <= r; i++) {
      grad.emplace_back(ori[i].second, ori[i].first);
    }
    sort(grad.begin(), grad.end());
    for (int i = 0; i < grad.size(); i++) {
      while (i + 1 < grad.size() && grad[i + 1].first == grad[i].first) i++;
      while (!num[p].empty() && cut(grad[i].first, grad[i].second, get<2>(num[p].back()), get<1>(num[p].back())) <= get<0>(num[p].back())) {
        num[p].pop_back();
      }
      if (num[p].empty()) {
        num[p].emplace_back(frac(0, 1), grad[i].second, grad[i].first);
      } else {
        frac at = cut(grad[i].first, grad[i].second, get<2>(num[p].back()), get<1>(num[p].back()));
        num[p].emplace_back(at, grad[i].second, grad[i].first);
      }
    }
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(p + p, l, mid);
    build(p + p + 1, mid + 1, r);
  }
  long long find(int p, int l, int r, int ll, int rr, long long t) {
    if (ll <= l && r <= rr) {
      int it = lower_bound(num[p].begin(), num[p].end(), make_tuple(frac(t, 1), inf, inf)) - num[p].begin() - 1;
      return get<1>(num[p][it]) + t * get<2>(num[p][it]);
    }
    if (r < ll || rr < l) return 0;
    int mid = (l + r) >> 1;
    return max(find(p + p, l, mid, ll, rr, t), find(p + p + 1, mid + 1, r, ll, rr, t));
  }
  long long find(int l, int r, long long t) {
    return find(1, 0, n - 1, l, r, t);
  }

  vector<pair<int, int>> ori;               // (a, b) = a + bt
  vector<vector<tuple<frac, int, int>>> num;        // x ketemu, a, b
  vector<vector<pair<int, int>>> sorted;
  int n; 
};

int main() {
  vector<pair<int, int>> ori;
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    ori.emplace_back(a, b);
  }
  segtree seg(ori);

  int q;
  scanf("%d", &q);
  while (q--) {
    int l, r, t;
    scanf("%d %d %d", &l, &r, &t);
    l--; r--;
    printf("%lld\n", seg.find(l, r, t));
  }
  return 0;
}