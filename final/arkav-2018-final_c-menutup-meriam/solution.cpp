#include <bits/stdc++.h>

using namespace std;

int n,q,h[50000],block,chull[50000],lchull[50000],ans[50000];
tuple<int,int,int> queries[50000];

bool cmp(tuple<int,int,int> a, tuple<int,int,int> b) {
	if ((int) get<0>(a)/block == (int) get<0>(b)/block)
		return get<1>(a) < get<1>(b);
	return get<0>(a) < get<0>(b);
}

int ccw(int a, int b, int c) {
	long long u1 = b - a, v1 = c - b;
	long long u2 = h[b] - h[a], v2 = h[c] - h[b];
	long long x = 1LL*u1*v2 - 1LL*u2*v1;
	if (x > 0) return 1;
	else if (x == 0) return 0;
	return -1;
}

int do_plain(int a, int b) {
	int nchull = 0;
	for (int i = a; i <= b; i++) {
		for (;nchull >= 2 && ccw(chull[nchull-2], chull[nchull-1], i) == 1; nchull--);
		chull[nchull++] = i;
	}
	return nchull;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", h + i);
	block = (int) max(1.0, sqrt(n));
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		scanf("%d%d", &get<0>(queries[i]), &get<1>(queries[i]));
		get<0>(queries[i])--;
		get<1>(queries[i])--;
		get<2>(queries[i]) = i;
	}

	sort(queries, queries + q, cmp);
	int nchull = 0;
	int nlchull = 0;
	int rchull = -1;
	int lastblk = -1;
	int p = 0;
	int j = -1;
	for (int i = 0; i < q; i++) {
		int left, right, idx;
		tie(left, right, idx) = queries[i];
		if (left/block == right/block) {
			ans[idx] = do_plain(left, right);
			continue;
		}

		int lblk = left / block;
		// printf("%d) %d %d -> %d\n", idx, left, right, lblk);
		if (lblk != lastblk) nchull = 0, p = (lblk + 1) * block;
		lastblk = lblk;
		for (;p <= right; p++) {
			for (;nchull >= 2 && ccw(chull[nchull-2], chull[nchull-1], p) == 1; nchull--);
			chull[nchull++] = p;
		}

		int nlchull = 0;
		int rchull = 0;
		for (j = (lblk + 1) * block - 1; j >= left; j--) {
			while (nlchull > 0 && nlchull + nchull - rchull >= 2) {
				int a = nlchull == 1 ? chull[rchull] : lchull[nlchull-2];
				int b = lchull[nlchull - 1];
				int c = j;
				if (ccw(c,b,a) == 1) nlchull--;
				else break;
			}

			if (nlchull == 0) {
				int lo = rchull;
				int hi = nchull - 2;
				// printf("lo: %d, hi: %d\n", lo, hi);
				while (lo <= hi) {
					int mid = (lo+hi)/2;
					// printf("mid: %d ccw = %d\n", mid, ccw(j, chull[mid], chull[mid+1]));
					if (ccw(j, chull[mid], chull[mid+1]) == 1)
						lo = mid + 1, rchull = mid + 1;
					else
						hi = mid - 1;
				}
			}

			lchull[nlchull++] = j;
		}
		// printf("nchull: %d, lchull: %d, rchull: %d\n", nchull, nlchull, rchull);
		ans[idx] = nlchull + nchull - rchull;
	}

	for (int i = 0; i < q; i++)
		printf("%d\n", ans[i]);

	return 0;
}