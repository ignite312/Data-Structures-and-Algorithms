#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e5 + 5;
vector<int> G[N+5];
ll prefix[N+5], arr[N+5], values[N+5];
int st[N+5], en[N+5];
int Time = 0;


ll lazy[N*4+5], tree[N*4+5];
void build(int node, int l, int r) {
    if(l == r) {
        tree[node] = arr[l];
        return;
    }
    int mid = l + (r - l)/2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    tree[node] = tree[node*2] + tree[node*2+1];
}
void update(int node, int l, int r, int i, int j, ll value) {
    if(lazy[node] != 0) {
        tree[node] += (r-l+1)*lazy[node];
        if(l != r) {
            lazy[node*2]+=lazy[node];
            lazy[node*2+1]+=lazy[node]; 
        }
        lazy[node] = 0;
    }
    if(l > j || r < i)return;
    if(l >= i && r <= j) {
        tree[node] += (r-l+1)*value;
        if(l != r) {
            lazy[node*2]+= value;
            lazy[node*2+1]+=value; 
        }
        return;
    }
    int mid = l + (r - l)/2;
    update(node*2, l, mid, i, j, value);
    update(node*2+1, mid+1, r, i, j, value);
    tree[node] = tree[node*2] + tree[node*2+1];
}
ll sum(int node, int l, int r, int i, int j) {
    if(lazy[node] != 0) {
        tree[node] += (r-l+1)*lazy[node];
        if(l != r) {
            lazy[node*2]+=lazy[node];
            lazy[node*2+1]+=lazy[node]; 
        }
        lazy[node] = 0;
    }
    if(l > j || r < i)return 0;
    if(l >= i && r <= j) return tree[node];
    int mid = l + (r - l)/2;
    return sum(node*2, l, mid, i, j) + sum(node*2+1, mid+1, r, i, j);
}
void dfs(int vertex, int parent) {
	st[vertex] = ++Time;
	for(auto child : G[vertex]) {
		if(child == parent)continue;
		prefix[child]+=prefix[vertex];
		dfs(child, vertex);
	}
	en[vertex] = Time;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        int n, q;
        cin >> n >> q;
        for(int i = 1; i<= n; i++) {
        	cin >> prefix[i];
        	values[i] = prefix[i];
        }
        for(int i = 0; i < n-1; i++) {
        	int u, v;
        	cin >> u >> v;
        	G[u].push_back(v);
        	G[v].push_back(u);
        }
        dfs(1, -1);
        for(int i = 1; i <= n; i++)arr[st[i]] = prefix[i];
        build(1, 1, n);
        while(q--) {
        	int type;
        	cin >> type;
        	if(type == 1) {
        		int s;
        		ll x;
        		cin >> s >> x;
        		update(1, 1, n, st[s], en[s], x - values[s]);
        		values[s] = x;
        	}else {
        		int s;
        		cin >> s;
        		cout << sum(1, 1, n, st[s], st[s]) << "\n";
        	}
        }
    }
    return 0;
}
// 
