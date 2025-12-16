// https://codeforces.com/contest/321/problem/C

#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100001;
vector<int> adj[N];
int n;
int subtree[N];
bool visited[N];
char _rank[N];
char current = 'A';

int getSubtree(int u, int p) {
    subtree[u] = 1;
    for(auto v : adj[u]) {
        if(!visited[v] && v != p) {
            getSubtree(v, u);
            subtree[u]+=subtree[v];
        }
    }
    return subtree[u];
}
int getCentroid(int u, int p, int desired) {
    for(auto v : adj[u])
        if(!visited[v] && v != p && subtree[v] > desired)
            return getCentroid(v, u, desired);
    return u;
}
void centroidDecomposition(int u, char RNK) {
    int centroid = getCentroid(u, -1, getSubtree(u, -1) >> 1);
    visited[centroid] = true;
    _rank[centroid] = RNK;
    for(auto v : adj[centroid])if(!visited[v])centroidDecomposition(v, RNK+1);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        cin >> n;
        for(int i = 0; i < n-1; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        centroidDecomposition(1, 'A');
        for(int i = 1; i <= n; i++) {
            cout << _rank[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}