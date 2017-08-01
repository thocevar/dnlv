#include <vector>
#include <queue>
using namespace std;

vector<int> reconstruct_distinct_nlogn(vector<int> d) {
	int n=d.size();
	vector<int> deg(n,0); // out degree
	vector<int> in[n], in_opt[n], out_opt[n];
	for (int i=0;i<n;i++) {
		for (int j=max(i-d[i]+1,0);j<=min(i+d[i]-1,n-1);j++) if (i!=j) {
			deg[j]++;
			in[i].push_back(j);
		}
		for (int j : {i-d[i],i+d[i]}) if (i!=j && 0<=j && j<n) {
			deg[i]++;
			out_opt[i].push_back(j);
			in_opt[j].push_back(i);
		}
	}
	vector<int> a(n,-1), emp;
	queue<int> q;
	int v=n-1;
	for (int i=0;i<n;i++) if (deg[i]==0) {
		q.push(i);
	}
	while (!q.empty()) {
		int x=q.front(); q.pop();
		a[x]=v--;
		for (int y : in[x]) {
			deg[y]--;
			if (deg[y]==0) q.push(y);
		}
		for (int y : in_opt[x]) {
			deg[y]-=out_opt[y].size();
			if (deg[y]==0) q.push(y);
		}
	}
	return a;
}
