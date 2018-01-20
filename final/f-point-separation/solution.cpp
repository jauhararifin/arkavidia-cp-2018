// Complexity: O((N+M)^3 log(N+M))
#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld EPS = 1e-9;
const int N = 333; 

struct point {
  ld x, y;
  point(ld x = 0, ld y = 0) : x(x), y(y) {}
  point operator+(point p) { return point(x+p.x, y+p.y); }
  point operator-(point p) { return point(x-p.x, y-p.y); }
  point operator*(ld s) { return point(x*s, y*s); }
  point operator/(ld s) { return point(x/s, y/s); }
  ld operator%(point p) { return x * p.y - y * p.x; }
  ld operator*(point p) { return x * p.x + y * p.y; }
  bool operator<(point p) { return fabs(x - p.x) > EPS ? x < p.x : y < p.y; }
  bool operator==(point p) { return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS; }
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

// return 1 = ccw, 0 = colinear, -1 = cw
int ccw(point p, point q, point r) {
  point pq = q - p, pr = r-p;
  ld crs = pq % pr;
  if (fabs(crs) < EPS) return 0;
  return crs > 0 ? 1 : -1;
}

point vp[N+N], centers[N+N];
int addBlack[N+N], addWhite[N+N];
int idx[N+N];
point pivot;
bool cmpCenter(int il, int ir) {
  int dir = ccw(pivot, centers[il], centers[ir]);
  return dir < 0;
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    vp[i] = point(x, y);
  }
  for (int i = 0; i < m; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    vp[n+i] = point(x, y);
  }
  int ans = min(n, m);
  int all = n + m;
  for (int i = 0; i < all; ++i) {
    for (int j = i+1; j < all; ++j) {
      int sisa = 0, rmBlack = 0, rmWhite = 0;
      for (int k = 0, p = 0; k < all; ++k) {
        if (i == k || j == k) continue;
        int dir = ccw(vp[i], vp[j], vp[k]);
        if (dir == 0) {
          point ki = vp[i]-vp[k], kj = vp[j]-vp[k];
          if (ki * kj < 0) // check if vp[k] is between vp[i] and vp[j]
            rmBlack += k >= n; // black should be removed
          else
            rmWhite += k < n; // white should be removed
          continue;
        }
        else if (k < n) 
          rmWhite += dir < 0; // white is removed if outside
        else 
          rmBlack += dir > 0; // black is removed if inside
        centers[k] = circumCenter(vp[i], vp[j], vp[k]);
        idx[sisa++] = k;
      }
      pivot = vp[i];
      sort(idx, idx+sisa, cmpCenter);
      for (int k = 0; k <= sisa; ++k) {
        addBlack[k] = addWhite[k] = 0;
      }
      point pnow;
      int cntCenter = 0;
      for (int k = 0; k < sisa; ++k) {
        int id = idx[k];
        if (cntCenter == 0 || !(pnow == centers[id]))
          pnow = centers[id], ++cntCenter;
        int dir = ccw(vp[i], vp[j], vp[id]);
        if (id < n) {
          if (dir > 0)
            ++addWhite[cntCenter];
          else
            --addWhite[cntCenter-1];
        }
        else {
          if (dir > 0)
            --addBlack[cntCenter-1];
          else
            ++addBlack[cntCenter];
        }
      }
      ans = min(ans, rmBlack + rmWhite);
      for (int k = 0; k <= cntCenter; ++k) {
        rmBlack += addBlack[k];
        rmWhite += addWhite[k];
        ans = min(ans, rmBlack + rmWhite);
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}