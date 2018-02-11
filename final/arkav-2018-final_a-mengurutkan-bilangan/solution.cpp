#include <bits/stdc++.h>

using namespace std;

int t,n,p[50000];

bool cmp(const string& a, const string& b) {
	if (a.length() < b.length()) return 1;
	else if (a.length() > b.length()) return 0;
	return a < b;
}

bool cmp2(const pair<string,int>& a, const pair<string,int>& b) {
	if (a.first == b.first) return a.second < b.second;
	return cmp(a.first, b.first);
}

int main() {
	ios::sync_with_stdio(0);
	cin>>n;
	vector<pair<string,int> > v;
	for (int i = 0; i < n; i++) {
		string x,y; cin>>x>>y;
		if (cmp(x,y))
			v.push_back(make_pair(y,i));
		else
			v.push_back(make_pair(x,i));
	}
	sort(v.begin(), v.end(), cmp2);
	for (int i = 0; i < n; i++)
		p[v[i].second] = i + 1;
	for (int i =  0; i < n; i++)
		cout<<p[i]<<"\n";
	return 0;
}