#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "r");
  FILE *con = fopen(argv[3], "r");

  double out_ans;
  fscanf(out, "%lf", &out_ans);

  double con_ans;
  fscanf(con, "%lf", &con_ans);

  fclose(in); fclose(out); fclose(con);

  if (fabs(out_ans - con_ans) < 1e-4 || fabs(out_ans - con_ans) / out_ans < 1e-4) {
    puts("AC");
  } else {
    puts("WA");
  }
  return 0;
}
