#include <vector>
#include <stack>
using namespace std;

namespace RDN {
	typedef pair<int,int> PII;

	int n;
	vector<int> D, A;

	vector<int> f,g;
	vector<vector<int> > Cl,Cr;

	void init() {
		// f
		f = vector<int>(n);
		stack<PII> s;  // {x,x+D[x]}
		for (int k=0;k<n;k++) {
			while (!s.empty() && s.top().second<=k) s.pop();
			if (s.empty()) f[k]=-1;
			else f[k]=s.top().first;
			while (!s.empty() && k+D[k]>=s.top().second) s.pop();
			s.push({k,k+D[k]});
		}
		// g
		g = vector<int>(n);
		s = stack<PII>();  // {x,x-D[x]}
		for (int k=n-1;k>=0;k--) {
			while (!s.empty() && s.top().second>=k) s.pop();
			if (s.empty()) g[k]=n;
			else g[k]=s.top().first;
			while (!s.empty() && k-D[k]<=s.top().second) s.pop();
			s.push({k,k-D[k]});
		}
		// Cl
		Cl = vector<vector<int> >(n);
		for (int k=0;k<n;k++) {
			if (0<=k-D[k]) Cl[k-D[k]].push_back(k);
		}
		// Cr
		Cr = vector<vector<int> >(n);
		for (int k=n-1;k>=0;k--) {
			if (k+D[k]<n) Cr[k+D[k]].push_back(k);
		}
	}

	bool check(int k, int l, int r) {
		if (k<l || r<k) return false;
		if (l<=f[k]) return false;
		if (g[k]<=r) return false;
		return true;
	}

	void split(int m, int l, int r) {
		if (max(l-1,0)<=m-D[m]) Cl[m-D[m]].pop_back();
		if (m+D[m]<=min(r+1,n-1)) Cr[m+D[m]].pop_back();
	}

	void closed(int i, int j, int a, int b) {
		if (i>j) return;
		int r=-1;
		if (!Cr[j+1].empty()) r=Cr[j+1].back();
		int l=-1;
		if (!Cl[i-1].empty()) l=Cl[i-1].back();
		int m=1;
		if (check(l,i,j)) m=l;
		else if (check(r,i,j)) m=r;
		if (m!=-1) {
			A[m]=b;
			split(m,i,j);
			closed(i,m-1,a,a+(m-i)-1);
			closed(m+1,j,a+(m-i),b-1);
		}
	}

	void halfl(int i, int a, int b) {
		if (i<=0) return;
		int m=-1;
		if (!Cr[i].empty()) m=Cr[i].back();
		if (check(m,0,i-1)) {
			A[m]=b;
			split(m,0,i-1);
			halfl(m,a,a+m-1);
			closed(m+1,i-1,a+m,b-1);
		}
	}

	void halfr(int i, int a, int b) {
		if (i>=n-1) return;
		int m=-1;
		if (!Cl[i].empty()) m=Cl[i].back();
		if (check(m,i+1,n-1)) {
			A[m]=b;
			split(m,i+1,n-1);
			halfr(m,a,a+(n-m-1)-1);
			closed(i+1,m-1,a+(n-m-1),b-1);
		}
	}

	void open(int a, int b) {
		int m=-1;
		for (int i=0;i<n;i++) {
			if (D[i]>=n) m=i;
		}
		if (check(m,0,n-1)) {
			A[m]=b;
			split(m,0,n-1);
			halfl(m,a,a+m-1);
			halfr(m,a+m,b-1);
		}
	}
}

vector<int> reconstruct_distinct_n(vector<int> d) {
	RDN::n=d.size();
	RDN::D=d;
	RDN::A=vector<int>(RDN::n);
	RDN::init();
	RDN::open(0,RDN::n-1);
	return RDN::A;
}
