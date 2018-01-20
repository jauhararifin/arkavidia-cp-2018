// Complexity: O((N+M)^4)
#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const int N = 333;
const ld EPS = 1e-9;

struct point {
  ld x, y;
  point(ld x = 0, ld y = 0) : x(x), y(y) {}
  point operator+(point p) { return point(x+p.x, y+p.y); }
  point operator-(point p) { return point(x-p.x, y-p.y); }
  point operator*(ld s) { return point(x*s, y*s); }
  point operator/(ld s) { return point(x/s, y/s); }
  ld operator%(point p) { return x * p.y - y * p.x; }
  ld operator*(point p) { return x * p.x + y * p.y; }
};

ld dist2(point a, point b) {
  point ab = b-a;
  return ab * ab;
}

point circumCenter(point &a, point &b, point &c) {
  point bb = b - a, cc = c - a;
  ld db = bb * bb, dc = cc * cc, d = 2 * (bb % cc);
  return a - point(bb.y*dc-cc.y*db, cc.x*db-bb.x*dc) / d;
}

point vp[N+N];

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
      int x, y;
      scanf("%d %d", &x, &y);
      vp[i] = point(x, y); // putih
    }
    for (int i = 0; i < m; ++i) {
      int x, y;
      scanf("%d %d", &x, &y);
      vp[n+i] = point(x, y); // hitam
    }
    int all = n + m;
    int ans = min(n, m);
    for (int i = 0; i < all; ++i) {
      for (int j = i+1; j < all; ++j) {
        point center = (vp[i] + vp[j])/2.0;
        ld R2 = dist2(center, vp[i]);
        int cnt = 0;
        for (int l = 0; l < all; ++l) {
          if (l == i || l == j) continue;
          ld d2 = dist2(center, vp[l]);
          if (l >= n)
            cnt += (d2 + EPS < R2);
          else
            cnt += (R2 + EPS < d2);
        }
        ans = min(ans, cnt);        
      }
    }
    for (int i = 0; i < all; ++i) {
      for (int j = i+1; j < all; ++j) {
        for (int k = j+1; k < all; ++k) {
          point center = circumCenter(vp[i], vp[j], vp[k]);
          ld R2 = dist2(center, vp[i]);
          int cnt = 0;
          for (int l = 0; l < all; ++l) {
            if (l == i || l == j || l == k) continue;
            ld d2 = dist2(center, vp[l]);
            if (l >= n)
              cnt += (d2 + EPS < R2);
            else
              cnt += (R2 + EPS < d2);
          }
          ans = min(ans, cnt);
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}