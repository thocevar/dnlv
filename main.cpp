#include <cassert>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#include "distinct_nlogn.h"
#include "distinct_n2.h"
#include "distinct_n.h"
#include "repeated.h"

typedef vector<int> (*ReconFunc) (vector<int>);

vector<int> distances(vector<int> a) {
	vector<int> x;
	int n=a.size();
	for (int j=0;j<n;j++) {
		int k=n;
		for (int d=1;d<=n-1;d++) {
			if (j+d<n && a[j+d]>a[j]) { k=d; break; }
			if (j-d>=0 && a[j-d]>a[j]) { k=d; break; }
		}
		x.push_back(k);
	}
	return x;
}

void test_distinct_random(ReconFunc reconstruct_distinct, int n) {
	for (int it=1;;it++) {
		vector<int> a;
		for (int i=0;i<n;i++) a.push_back(i);
		random_shuffle(a.begin(),a.end());
		vector<int> da = distances(a);
		vector<int> b = reconstruct_distinct(da);
		vector<int> db = distances(b);
		assert(da==db);
		if (it%1000==0) cout << it << endl;
	}
}

set<vector<int> > s;

void test_distinct_all(ReconFunc reconstruct_distinct) {
	for (int n=1;;n++) {
		cout << n;
		vector<int> a;
		for (int i=0;i<n;i++) a.push_back(i);
		s.clear();
		do {
			vector<int> da = distances(a);
			if (s.count(da)) continue;
			else s.insert(da);
			vector<int> b = reconstruct_distinct(da);
			vector<int> db = distances(b);
			assert(da==db);
		} while (next_permutation(a.begin(),a.end()));
		cout << " OK" << endl;
	}
}

void test_repeated_random(ReconFunc reconstruct_repeated, int n, int k) {
	for (int it=1;;it++) {
		vector<int> a;
		for (int i=0;i<n;i++) a.push_back(rand()%k);
		vector<int> da = distances(a);
		vector<int> b = reconstruct_repeated(da);
		vector<int> db = distances(b);
		assert(da==db);
		if (it%1000==0) cout << it << endl;
	}
}

vector<int> a;
void gen(ReconFunc reconstruct, int n, int i=0, char v=0, int k=0, int all=0) {
	if (all==n) {
		vector<int> da = distances(a);
		if (s.count(da)) return;
		else s.insert(da);
		vector<int> b = reconstruct(da);
		vector<int> db = distances(b);
		assert(da==db);
	} else {
		if (i==n) {
			if (k>0) gen(reconstruct,n,0,v+1,0,all);
		} else {
			if (a[i]==-1) {
				a[i]=v;
				gen(reconstruct,n,i+1,v,k+1,all+1);
				a[i]=-1;
			}
			gen(reconstruct,n,i+1,v,k,all);
		}
	}
}

void test_repeated_all(ReconFunc reconstruct_repeated) {
	for (int n=1;;n++) {
		cout << n;
		a = vector<int>(n,-1);
		s.clear();
		gen(reconstruct_repeated,n);
		cout << " OK" << endl;
	}
}

int main() {
	//test_distinct_random(reconstruct_distinct_nlogn, 100);
	//test_distinct_all(reconstruct_distinct_nlogn);
	//test_distinct_random(reconstruct_distinct_n2, 100);
	//test_distinct_all(reconstruct_distinct_n2);
	//test_distinct_random(reconstruct_distinct_n, 100);
	test_distinct_all(reconstruct_distinct_n);
	//test_repeated_random(reconstruct_repeated, 100, 30);
	//test_repeated_all(reconstruct_repeated);
	return 0;
}
