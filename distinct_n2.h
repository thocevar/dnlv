#include <vector>
#include <algorithm>
using namespace std;

namespace RDN2 {
	int n;
	vector<int> D, A;

	bool check(int k, int l, int r) {
		if (k<l || r<k) return false;
		for (int x=l;x<=r;x++) if (x!=k) {
			if (abs(k-x)<D[x]) return false;
		}
		return true;
	}

	void closed(int i, int j, int a, int b) {
		if (i>j) return;
		int r=-1;
		for (int k=i;k<=j;k++) {
			if (k+D[k]==j+1) { r=k; break; }
		}
		int l=-1;
		for (int k=j;k>=i;k--) {
			if (k-D[k]==i-1) { l=k; break; }
		}
		int m=1;
		if (check(l,i,j)) m=l;
		else if (check(r,i,j)) m=r;
		if (m!=-1) {
			A[m]=b;
			closed(i,m-1,a,a+(m-i)-1);
			closed(m+1,j,a+(m-i),b-1);
		}
	}

	void halfl(int i, int a, int b) {
		if (i<=0) return;
		int m=-1;
		for (int j=0;j<i;j++) {
			if (j+D[j]==i) { m=j; break; }
		}
		if (check(m,0,i-1)) {
			A[m]=b;
			halfl(m,a,a+m-1);
			closed(m+1,i-1,a+m,b-1);
		}
	}

	void halfr(int i, int a, int b) {
		if (i>=n-1) return;
		int m=-1;
		for (int j=n-1;j>i;j--) {
			if (j-D[j]==i) { m=j; break; }
		}
		if (check(m,i+1,n-1)) {
			A[m]=b;
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
			halfl(m,a,a+m-1);
			halfr(m,a+m,b-1);
		}
	}
}

vector<int> reconstruct_distinct_n2(vector<int> d) {
	RDN2::n=d.size();
	RDN2::D=d;
	RDN2::A=vector<int>(RDN2::n);
	RDN2::open(0,RDN2::n-1);
	return RDN2::A;
}
