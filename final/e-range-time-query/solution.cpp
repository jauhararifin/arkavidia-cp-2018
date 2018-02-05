// Complexity : O(N*log(N) + Q*log^2(N))
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

struct line {
  int m, c;
  line(int m = 0, int c = 0) : m(m), c(c) {}
  long long get(int x) {
    return 1LL * m * x + c;
  }
  bool operator<(line l) {
    if (m != l.m)
      return m < l.m;
    return c < l.c;
  }
};

int n, q;
int a[N], b[N];
vector<line> convex[N << 2];

bool isBad(line & prev, line & cur, line & next) {
  return 1LL * (prev.m - cur.m) * (next.c - cur.c) <= 1LL * (cur.m - next.m) * (cur.c - prev.c);
}

void build(int id = 1, int l = 0, int r = n) {
  if (r-l < 2) {
    convex[id].push_back(line(b[l], a[l]));
    return;
  }
  int mid = (l + r) >> 1, il = id << 1, ir = il | 1;
  build(il, l, mid);
  build(ir, mid, r);
  int jl = 0, jr = 0;
  while (jl < convex[il].size() || jr < convex[ir].size()) {
    line now;
    if (jl == convex[il].size())
      now = convex[ir][jr++];
    else if (jr == convex[ir].size())
      now = convex[il][jl++];
    else if (convex[il][jl] < convex[ir][jr])
      now = convex[il][jl++];
    else
      now = convex[ir][jr++];
    while (convex[id].size() >= 1 && convex[id].back().m == now.m)
      convex[id].pop_back();
    int sz;
    while ((sz = convex[id].size()) >= 2 && isBad(convex[id][sz-2], convex[id][sz-1], now))
      convex[id].pop_back();
    convex[id].push_back(now);
  }
}

long long get(int x, int y, int t, int id = 1, int l = 0, int r = n) {
  if (x >= r || l >= y) return 0;
  if (x <= l && r <= y) {
    int le = 0, ri = (int)convex[id].size()-1;
    while (le < ri) {
      int mid = (le + ri) >> 1;
      if (convex[id][mid+1].get(t) >= convex[id][mid].get(t))
        le = mid+1;
      else
        ri = mid;
    }
    return convex[id][le].get(t);
  }
  int mid = (l + r) >> 1, il = id << 1, ir = il | 1;
  return max(get(x, y, t, il, l, mid), get(x, y, t, ir, mid, r));
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d %d", a+i, b+i);
  build();
  scanf("%d", &q);
  while (q--) {
    int l, r, t;
    scanf("%d %d %d", &l, &r, &t);
    --l;
    printf("%lld\n", get(l, r, t));
  }
  return 0;
}