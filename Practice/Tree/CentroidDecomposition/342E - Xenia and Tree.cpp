#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5 + 1;
const int INF = 1e9;
vector<int> adj[N];
vector<array<int, 2>> anchestors[N];
int n;
int subtree[N];
bool visited[N];
int min_dist[N];
 
int get_subtree(int u, int p) {
    subtree[u] = 1;
    for(auto v : adj[u]) {
        if(!visited[v] && v != p) {
            get_subtree(v, u);
            subtree[u]+=subtree[v];
        }
    }
    return subtree[u];
}
int get_centroid(int u, int p, int desired) {
    for(auto v : adj[u])
        if(!visited[v] && v != p && subtree[v] > desired)
            return get_centroid(v, u, desired);
    return u;
}
void get_distance(int u, int centroid, int p, int cur_dist) {
    for(auto v : adj[u]) {
        if(!visited[v] && v != p) {
            cur_dist++;
            get_distance(v, centroid, u, cur_dist);
            cur_dist--;
        }
    }
    anchestors[u].push_back({centroid, cur_dist});
}
void build_centroid_decomp(int u) { 
    int centroid = get_centroid(u, -1, get_subtree(u, -1) >> 1);
    visited[centroid] = true;
    for(auto v : adj[centroid]) {
        if(!visited[v]) {
            get_distance(v, centroid, -1, 1);
        }
    }
    for(auto v : adj[centroid])if(!visited[v])build_centroid_decomp(v);
}
void paint(int u) {
    for(auto [anchestor, dist] : anchestors[u]) {
        min_dist[anchestor] = min(min_dist[anchestor], dist);
    }
    min_dist[u] = 0;
}
int query(int u) {
    int ans = min_dist[u];
    for(auto [anchestor, dist] : anchestors[u]) {
        ans = min(ans, dist + min_dist[anchestor]);
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        int q;
        cin >> n >> q;
        for(int i = 0; i < n-1; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        build_centroid_decomp(1);
        for(int i = 1; i <= n; i++)min_dist[i] = INF;
        paint(1);
        while(q--) {
            int type, node;
            cin >> type >> node;
            if(type == 1) {
                paint(node);
            }else {
                cout << query(node) << "\n";
            }
        }
    }
    return 0;
}