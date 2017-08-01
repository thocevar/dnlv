#include <vector>
#include <queue>
using namespace std;

namespace RR {
	vector<int> deg; // out degree (all)
	vector<int> deg_opt; // optional out degree
	vector<vector<int> > in, out, in_opt, out_opt;

	void pop(int x) {
		for (int y : in[x]) {
			deg[y]--;
		}
		for (int y : in_opt[x]) {
			deg[y]-=out_opt[y].size();
			deg_opt[y]=0;
		}
	}

	int vis[100];
	int check(int x) {
		vis[x]=1;
		if (deg_opt[x]>0) return 0;
		for (int y : out[x]) {
			if (!vis[y] && !check(y)) return 0;
		}
		return 1;
	}

	vector<int> reconstruct(vector<int> d) {
		int n=d.size();
		deg=vector<int>(n,0);
		deg_opt=vector<int>(n,0);
		in=vector<vector<int> >(n);
		out=vector<vector<int> >(n);
		in_opt=vector<vector<int> >(n);
		out_opt=vector<vector<int> >(n);
		for (int i=0;i<n;i++) {
			for (int j=max(i-d[i]+1,0);j<=min(i+d[i]-1,n-1);j++) if (i!=j) {
				deg[j]++;
				out[j].push_back(i);
				in[i].push_back(j);
			}
			for (int j : {i-d[i],i+d[i]}) if (i!=j && 0<=j && j<n) {
				deg[i]++;
				deg_opt[i]++;
				out_opt[i].push_back(j);
				in_opt[j].push_back(i);
			}
		}
		vector<int> a(n,-1);
		vector<int> q;
		int v=n-1,todo=n;
		while (todo>0) {
			q.clear();
			for (int i=0;i<n;i++) if (a[i]==-1) {
				for (int j=0;j<n;j++) vis[j]=0;
				if (check(i)) q.push_back(i);
			}
			for (int x : q) {
				a[x]=v;
				pop(x);
			}
			v--;
			todo-=q.size();
		}
		return a;
	}
}

vector<int> reconstruct_repeated(vector<int> d) {
	return RR::reconstruct(d);
}
