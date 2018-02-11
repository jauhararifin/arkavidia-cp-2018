/**
 *
 * Boleh diubah: Nambah function, nambah include, nambah variabel.
 *
 */

#include <cstdio>
#include <bits/stdc++.h>
using namespace std;
struct AVL{
    int size, heig;
    int val;
    int idx;
    int jumlah;
    AVL *l;
		AVL *r;
    AVL(){}
    AVL(int va, int id){val = va;jumlah = va;idx = id;size=1;heig=1;l=NULL;r =NULL;}
   
};
int SIZ(AVL *now)
{
	if(now==NULL) return 0;
	return now->size;
}
int height(AVL *now)
{
	if(now==NULL) return 0;
	return now->heig;
}
int getbal(AVL *now)
{
	if(now==NULL) return 0;
	return height(now->l) - height(now->r);
}
int getjumlah(AVL *a)
{
	if(a==NULL) return 0;
	return a->jumlah;
}
AVL *rotateright(AVL *&now)
{
	AVL *tmp = now->l;
	AVL *T = tmp->r;
	now->l = T;
	tmp->r = now;
	now->size = SIZ(now->l) + SIZ(now->r) + 1;
	tmp->size = SIZ(tmp->l) + SIZ(tmp->r) + 1;
	now->heig = max(height(now->l), height(now->r))+1;
	tmp->heig = max(height(tmp->l), height(tmp->r))+1;
	now->jumlah = getjumlah(now->l) + getjumlah(now->r) + now->val;
	tmp->jumlah = getjumlah(tmp->l) + getjumlah(tmp->r) + tmp->val;
	return tmp;
}
AVL *rotateleft(AVL *&now)
{
	//return now;
	AVL *tmp = now->r;
	AVL *T = tmp->l;
	now->r = T;
	tmp->l = now;
	now->size = SIZ(now->l) + SIZ(now->r) + 1;
	tmp->size = SIZ(tmp->l) + SIZ(tmp->r) + 1;
	now->heig = max(height(now->l), height(now->r))+1;
	tmp->heig = max(height(tmp->l), height(tmp->r))+1;
	now->jumlah = getjumlah(now->l) + getjumlah(now->r) + now->val;
	tmp->jumlah = getjumlah(tmp->l) + getjumlah(tmp->r) + tmp->val;
	return tmp;
}
AVL *insert(AVL *&now, int ke, int va)
{
	if(now==NULL) return new AVL(va, ke);
	else if(ke > now->idx) now->r = insert(now->r, ke,va);
	else if(ke < now->idx) now->l = insert(now->l, ke,va);
	else now->val = va;
	now->heig = max(height(now->l), height(now->r)) + 1;
	now->size = SIZ(now->l) + SIZ(now->r) + 1;
	now->jumlah = getjumlah(now->l) + getjumlah(now->r) + now->val;
	int bal = getbal(now);
	if(bal==2)
	{
		if(getbal(now->l)==-1) now->l = rotateleft(now->l);
		return rotateright(now);
	}
	else if(bal==-2)
	{
		if(getbal(now->r)==1) now->r = rotateright(now->r);
		return rotateleft(now);
	}
	return now;
}
int N,M;
struct POI{
	AVL *dalem;
	POI *l, *r;
	POI(){}
}*tree;
void init(int R, int C) {
	tree = NULL;
	N = R;
	M = C;
}
inline int conv2(AVL *a)
{
	if(a==NULL) return 0;
	return a->val;
}
inline int segquery2(int kiri, int kanan, int l, int r, AVL *now)
{
	if(now==NULL) return 0;
	if(kiri>=l && kanan<=r) return now->jumlah;
	else if(kiri>r || kanan<l) return 0;
	int ans = segquery2(kiri,now->idx - 1,l,r,now->l) + segquery2(now->idx + 1, kanan, l,r,now->r);
	if(now->idx >=l && now->idx <=r) ans += now->val;
	return ans;
}
inline void segupdate(int kiri, int kanan, int target, int Q, int K, POI *&now)
{
	//printf("%d %d\n", kiri, kanan);
	if(now==NULL) now = new POI();
	if(kiri==kanan && kanan==target) 
	{
		now->dalem = insert(now->dalem, Q,K);
		return; 
	}
	int m = (kiri+kanan)>>1;
	if(target<=m) 
	{
		segupdate(kiri,m, target, Q, K, now->l);
		if(now->r==NULL) now->r = new POI();
	}
	else 
	{
		segupdate(m+1,kanan, target, Q, K,now->r);
		if(now->l==NULL) now->l = new POI();
	}
	now->dalem = insert(now->dalem,Q, segquery2(0,M-1,Q,Q,now->l->dalem) + segquery2(0,M-1,Q, Q, now->r->dalem));
}
void update(int P, int Q, int K) {
	segupdate(0,N-1,P,Q,K,tree);
	return;	
}
inline int segquery(int kiri, int kanan, int r1, int c1, int r2, int c2, POI *now)
{
	if(now==NULL) return 0;
	if(kiri>=r1 && kanan<=r2) return segquery2(0,M-1,c1,c2,now->dalem);
	else if(kiri>r2 || kanan<r1) return 0;
	int m = (kiri+kanan)>>1;
	return segquery(kiri,m,r1,c1,r2,c2,now->l) + segquery(m+1,kanan, r1,c1,r2,c2,now->r);
}
int calculate(int P, int Q, int U, int V) {
	return segquery(0,N-1,min(P,U),min(Q,V),max(P,U),max(Q,V),tree);
}

/**
 *
 * Mulai sini DILARANG diubah.
 *
 */

int main()
{
	int R,Q;
	scanf("%d %d",&R,&Q);
	init(R,R);
	for (int i = 0; i < Q; ++i)
	{
		int op;
		scanf("%d",&op);
		if (op == 1 || op == 2) // update
		{
			int x,y;
			scanf("%d %d",&x,&y);
			x--;y--;
			update(x,y,op&1);
		}
		else if (op == 3)
		{
			int a,b,c,d;
			scanf("%d %d %d %d",&a,&b,&c,&d);
			a--; b--; c--; d--;
			printf("%d\n",calculate(a,b,c,d));
		}
	}
	return 0;
}

