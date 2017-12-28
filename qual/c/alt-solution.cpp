#include <bits/stdc++.h>
using namespace std;
const int N = 2e5;
const int M = 30;
int pref[N + 5][M];
int main(){
  int t;
  scanf("%d", &t);
  while(t--){
    int n, q;
    scanf("%d%d", &n, &q);
    memset(pref, 0, sizeof pref);
    for(int i = 1; i <= n; ++i){
      int x;
      scanf("%d", &x);
      for(int j = 0;j < M; ++j){
        pref[i][j] = pref[i - 1][j];
        if((1 << j) & x){
          pref[i][j]++;
        }
      }
    }

    while(q--){
      int l, r;
      scanf("%d%d", &l, &r);
      int selisih = r - l + 1;
      int res = 0;
      for(int i = 0;i < M; ++i){
        if(pref[r][i] - pref[l - 1][i] == selisih) res += (1 << i);
      }
      printf("%d\n", res);
    }
  }
  return 0;
}