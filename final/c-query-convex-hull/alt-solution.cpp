#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5, MAGIC = 80;

struct point {
  int x, y;
  point(int x = 0, int y = 0) : x(x), y(y) {}
  point operator+(point p) { return point(x+p.x, y+p.y); }
  point operator-(point p) { return point(x-p.x, y-p.y); }
  long long operator%(point p) { return 1LL * x * p.y - 1LL * y * p.x; }
  long long operator*(point p) { return 1LL * x * p.x + 1LL * y * p.y; }
};

int a[N];
int l[N], r[N];
point vp[N];
point rhull[N], lhull[N];
int nlhull, nrhull;
int ans[N];
vector<pair<int, int> > que[N];

int ccw(point a, point b, point c) {
  point ab = b - a, ac = c - a;
  long long crs = ab % ac;
  if (crs == 0) return 0;
  return crs > 0 ? 1 : -1;
}

int main() {
  int n, q;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", a+i);
    vp[i] = point(i, a[i]);
  }
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    scanf("%d %d", l+i, r+i);
    --l[i];
    int noblok = l[i]/MAGIC;
    que[noblok].emplace_back(r[i], i);
  }
  for (int blok = 0; blok * MAGIC < n; ++blok) {
    nrhull = 0;
    sort(que[blok].begin(), que[blok].end());
    int ir = (blok+1) * MAGIC;
    for (auto it : que[blok]) {
      int id = it.second;
      while (ir < r[id]) {
        while (nrhull >= 2 && ccw(rhull[nrhull-2], rhull[nrhull-1], vp[ir]) > 0) --nrhull;
        rhull[nrhull] = vp[ir];
        ++nrhull, ++ir;
      }
      int il = min((blok + 1) * MAGIC, r[id]);
      int offset = 0;
      nlhull = 0;
      while (il > l[id]) {
        --il;
        while (nlhull > 0 && (nlhull + nrhull-offset) >= 2) {
          point b = lhull[nlhull-1], c;
          if (nlhull > 1)
            c = lhull[nlhull-2];
          else
            c = rhull[offset];
          if (ccw(vp[il], b, c) > 0)
            --nlhull;
          else
            break;
        }
        if (nlhull == 0) {
          int le = offset, ri = nrhull-1;
          while (le < ri) {
            int mid = (le + ri) >> 1;
            if (ccw(vp[il], rhull[mid], rhull[mid+1]) > 0)
              le = mid+1;
            else
              ri = mid;
          }
          offset = le;
        }
        lhull[nlhull] = vp[il];
        ++nlhull;
      }
      ans[id] = nlhull + nrhull - offset;
    }
  }
  for (int i = 0; i < q; ++i)
    printf("%d\n", ans[i]);
  return 0;
}