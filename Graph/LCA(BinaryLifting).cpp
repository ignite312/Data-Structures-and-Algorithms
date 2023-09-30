#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;
const int LOG = 14;
vector<int> G[N+5];
int up[N+5][LOG], depth[N+5];

void ancestor(int vertex) {
	for(auto child : G[vertex]) {
		depth[child] = depth[vertex] + 1;
		up[child][0] = vertex;
		for(int j = 1; j < LOG; j++)up[child][j] = up[up[child][j-1]][j-1];
		ancestor(child);
	}
}
int get_lca(int a, int b) {
	if(depth[a] < depth[b])swap(a, b);
	int k = depth[a] - depth[b];
	for(int i = LOG-1; i >= 0; i--)
		if(k & (1 << i))
			a = up[a][i];

	if(a == b)
		return a;

    for(int i = LOG-1; i >= 0; i--) {
    	if(up[a][i] != up[b][i]) {
    		a = up[a][i];
    		b = up[b][i];
    	}
    }
    return up[a][0];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        for(int i = 0; i < n; i++) {
        	int x;
        	cin >> x;
        	for(int j = 0; j < x; j++) {
        		int u;
        		cin >> u;
        		G[i].push_back(u);
        	}
        }
        ancestor(0);
        int q;
        cin >> q;
        while(q--) {
        	int a, b;
        	cin >> a >> b;
        	cout << get_lca(a, b) << "\n";
        }
    }
    return 0;
}
//https://www.spoj.com/problems/LCASQ/
