#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

// Treap
struct item;
typedef item * pitem;
struct item {
  int prior, cnt;
  pair<int, int> key;
  pitem l, r;
  item() {}
  item(pair<int, int> key, int prior) : cnt(1), key(key), prior(prior), l(NULL), r(NULL) {}
};
int cnt(pitem t) {
  return t ? t->cnt : 0;
}
void upd_cnt(pitem t) {
  if (!t) return;
  t->cnt = 1 + cnt(t->l) + cnt(t->r);
}
void split(pitem t, pair<int, int> key, pitem & l, pitem & r) {
  if (!t)
    l = r = NULL;
  else if (t->key < key)
    split(t->r, key, t->r, r), l = t;
  else
    split(t->l, key, l, t->l), r = t;
  upd_cnt(l);
  upd_cnt(r);
}
void merge(pitem & t, pitem l, pitem r) {
  if (!l || !r)
    t = l ? l : r;
  else if (l->prior > r->prior)
    merge(l->r, l->r, r), t = l;
  else
    merge(r->l, l, r->l), t = r;
  upd_cnt(t);
}
void insert(pitem & t, pitem it) {
  if (!t)
    t = it;
  else if (it->prior > t->prior)
    split(t, it->key, it->l, it->r), t = it;
  else
    insert(t->key < it->key ? t->r : t->l, it);
  upd_cnt(t);
}
void erase(pitem & t, pair<int, int> key) {
  if (!t)
    return;
  else if (t->key == key)
    merge(t, t->l, t->r);
  else
    erase(t->key < key ? t->r : t->l, key);
  upd_cnt(t);
}

// Segment Tree
pitem seg[N << 2];
int t[N], xa[N], ya[N], xb[N], yb[N];
vector<int> vx;
void add(int x, int y, int id = 1, int l = 0, int r = vx.size()) {
  insert(seg[id], new item({y, x}, rand() * rand()));
  if (r-l < 2)
    return;
  int mid = (l + r) >> 1, il = id << 1, ir = il | 1;
  if (x < mid)
    add(x, y, il, l, mid);
  else
    add(x, y, ir, mid, r);
}
void remove(int x, int y, int id = 1, int l = 0, int r = vx.size()) {
  erase(seg[id], {y, x});
  if (r-l < 2)
    return;
  int mid = (l + r) >> 1, il = id << 1, ir = il | 1;
  if (x < mid)
    remove(x, y, il, l, mid);
  else
    remove(x, y, ir, mid, r);
}
int get(int le, int ri, int down, int up, int id = 1, int l = 0, int r = vx.size()) {
  if (le >= r || l >= ri) return 0;
  if (le <= l && r <= ri) {
    pitem t1, t2;
    split(seg[id], {down, -1}, t1, seg[id]);
    split(seg[id], {up, -1}, seg[id], t2);
    int ret = cnt(seg[id]);
    merge(seg[id], t1, seg[id]);
    merge(seg[id], seg[id], t2);
    return ret;
  }
  int mid = (l + r) >> 1, il = id << 1, ir = il | 1;
  return get(le, ri, down, up, il, l, mid) + get(le, ri, down, up, ir, mid, r);
}

int main() {
  srand(time(0));
  int n, q;
  scanf("%d %d", &n, &q);
  for (int i = 0; i < q; ++i) {
    scanf("%d %d %d", t+i, xa+i, ya+i);
    vx.push_back(xa[i]);
    if (t[i] == 3) {
      scanf("%d %d", xb+i, yb+i);
      vx.push_back(xb[i]);
      if (xa[i] > xb[i]) swap(xa[i], xb[i]);
      if (ya[i] > yb[i]) swap(ya[i], yb[i]);
    }
  }
  sort(vx.begin(), vx.end());
  vx.erase(unique(vx.begin(), vx.end()), vx.end());
  for (int i = 0; i < q; ++i) {
    xa[i] = lower_bound(vx.begin(), vx.end(), xa[i]) - vx.begin();
    if (t[i] == 3)
      xb[i] = lower_bound(vx.begin(), vx.end(), xb[i]) - vx.begin();
  }
  for (int i = 0; i < q; ++i) {
    if (t[i] == 1)
      add(xa[i], ya[i]);
    else if (t[i] == 2)
      remove(xa[i], ya[i]);
    else
      printf("%d\n", get(xa[i], xb[i]+1, ya[i], yb[i]+1));
  }
  return 0;
}