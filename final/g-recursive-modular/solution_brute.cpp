#include <bits/stdc++.h>

using namespace std;

long long mod;

inline long long largemul(long long a, long long b) {
  long long r = a * b % mod;
  if (r < 0) r += mod;
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