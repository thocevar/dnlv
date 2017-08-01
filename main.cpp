#include <cassert>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#include "distinct_nlogn.h"
#include "distinct_n2.h"
#include "distinct_n.h"

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

void test_distinct_random(vector<int> (*reconstruct_distinct) (vector<int>), int n) {
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

void test_distinct_all(vector<int> (*reconstruct_distinct) (vector<int>)) {
	for (int n=1;;n++) {
		cout << n;
		vector<int> a;
		for (int i=0;i<n;i++) a.push_back(i);
		set<vector<int> > s;
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

int main() {
	//test_distinct_random(reconstruct_distinct_nlogn, 100);
	//test_distinct_all(reconstruct_distinct_nlogn);
	//test_distinct_random(reconstruct_distinct_n2, 100);
	//test_distinct_all(reconstruct_distinct_n2);
	//test_distinct_random(reconstruct_distinct_n, 100);
	test_distinct_all(reconstruct_distinct_n);
	return 0;
}
