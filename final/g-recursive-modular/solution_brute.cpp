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

inline long long add(long long a, long long b) {
  a += b;
  if (a >= mod) a -= mod;
  return a;
}

int main() {
  long long p, q, a0;
  long long an;
  scanf("%lld %lld %lld", &p, &q, &a0);
  scanf("%lld %lld", &mod, &an);
  long long now = a0;
  long long ans = -1;
  for (int i = 0; i <= mod; ++i) {
    if (now == an) {
      ans = i;
      break;
    }
    now = add(largemul(now, p), q);
  }
  printf("%lld\n", ans);
  return 0;
}