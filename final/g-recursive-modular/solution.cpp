// Complexity: O(sqrt(mod))
#include <bits/stdc++.h>

using namespace std;

long long mod;

inline long long largemul(long long a, long long b) {
  if (max(a, b) <= 1000000000)
    return a * b % mod;
  long long r = 0;
  for (; b; b >>= 1) {
    if (b & 1) {
      r += a;
      if (r >= mod) r -= mod;
    }
    a += a;
    if (a >= mod) a -= mod;
  }
  return r;
}

inline long long powmod(long long b, long long p) {
  long long r = 1;
  for (; p; p >>= 1, b = largemul(b, b))
    if (p & 1) r = largemul(r, b);
  return r;
}

inline long long add(long long a, long long b) {
  a += b;
  if (a >= mod) a -= mod;
  return a;
}

struct matrix {
  long long m[2][2];
  matrix() {
    memset(m, 0, sizeof m);
  }
  matrix operator+(matrix other) {
    matrix res;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        res.m[i][j] = m[i][j] + other.m[i][j];
        if (res.m[i][j] >= mod)
          res.m[i][j] -= mod;
      }
    }
    return res;
  }
  matrix operator*(matrix other) {
    matrix res;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        res.m[i][j] = add(largemul(m[i][0], other.m[0][j]), largemul(m[i][1], other.m[1][j])); 
      }
    }
    return res;
  }
  matrix operator^(long long p) {
    matrix res;
    matrix base = *this;
    for (int i = 0; i < 2; ++i)
      res.m[i][i] = 1;
    for (; p; p >>= 1, base = base * base)
      if (p & 1)
        res = res * base;
    return res;
  }
};


int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    long long p, q, a0;
    long long an;
    scanf("%lld %lld %lld", &p, &q, &a0);
    scanf("%lld %lld", &mod, &an);
    p %= mod;
    if (p < 0) p += mod;
    q %= mod;
    if (q < 0) q += mod;
    a0 %= mod;
    if (a0 < 0) a0 += mod;
    an %= mod;
    if (an < 0) an += mod;
    long long sq = sqrt(mod) + 1;
    map<long long, int> mp;
    long long now = a0;
    for (int i = 0; i < sq; ++i) {
      if (mp.find(now) == mp.end()) {
        mp[now] = i;
      }
      now = add(largemul(now, p), q);
    }
    matrix mat;
    mat.m[0][0] = p;
    mat.m[0][1] = q;
    mat.m[1][0] = 0;
    mat.m[1][1] = 1;
    long long ans = mod + 1;
    mat = mat^sq;
    matrix cur;
    for (int i = 0; i < 2; ++i)
      for (int j = 0; j < 2; ++j)
        cur.m[i][j] = (i == j);
    for (int i = 0; i < sq; ++i) {
      long long a = cur.m[0][0], b = (an + mod - cur.m[0][1]) % mod;
      if (a == 0) {
        if (b == 0)
          ans = min(ans, i * sq);
      }
      else {
        b = largemul(b, powmod(a, mod-2));
        auto it = mp.find(b);
        if (it != mp.end())
          ans = min(ans, sq * i + it->second);
      }
      cur = cur * mat;
    }
    if (ans > mod) ans = -1;
    printf("%lld\n", ans);
  }
  return 0;
}