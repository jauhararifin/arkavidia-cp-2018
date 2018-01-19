#include <bits/stdc++.h>

using namespace std;

int t,n,p[50000];

int main() {
	ios::sync_with_stdio(0);
	cin>>t;
	while (t--) {
		cin>>n;
		vector<pair<string,int> > v;
		for (int i = 0; i < n; i++) {
			string x,y; cin>>x>>y;
			string a,b;
			for (int j = 0; i < 100; i++) {
				if (j < 100-x.length()) a += "0";
				else a += x[j + 100 - x.length()];
				if (j < 100-y.length()) b += "0";
				else b += y[j + 100 - y.length()];
			}
			v.push_back(make_pair(max(a,b),i));
		}
		sort(v.begin(), v.end());
		for (int i = 0; i < n; i++)
			p[v[i].second] = i + 1;
		for (int i =  0; i < n; i++)
			cout<<p[i]<<"\n";
	}
	return 0;
}