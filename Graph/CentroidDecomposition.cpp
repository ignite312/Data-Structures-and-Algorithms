#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e5 + 1;
vector<int> G[N+1];
int n, k;
int subtree[N+1], cnt[N+1], mx_depth;
bool visited[N+1];
ll ans;
 
int getSubtree(int node, int parent) {
    subtree[node] = 1;
    for(auto child : G[node])
        if(!visited[child] && child != parent)
            subtree[node]+=getSubtree(child, node);
    return subtree[node];
}
int getCentroid(int node, int parent, int desired) {
    for(auto child : G[node])
        if(!visited[child] && child != parent && subtree[child] > desired)
            return getCentroid(child, node, desired);
    return node;
}
void compute(int node, int parent, bool filling, int depth) {
    if(depth > k)return;
    mx_depth = max(mx_depth, depth);
    if(filling)cnt[depth]++;
    else ans+=cnt[k - depth]*1LL;
    for(auto child : G[node])if(!visited[child] && child != parent)compute(child, node, filling, depth+1);
}
void centroidDecomposition(int node) {
    int centroid = getCentroid(node, -1, getSubtree(node, -1) >> 1);
    visited[centroid] = true;
    mx_depth = 0;
    for(auto child : G[centroid]) {
        if(!visited[child]) {
            compute(child, centroid, false, 1);
            compute(child, centroid, true, 1);
        }
    }
    for(int i = 1; i <= mx_depth; i++)cnt[i] = 0;
    for(auto child : G[centroid])if(!visited[child])centroidDecomposition(child);
}
int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        scanf("%d %d", &n, &k);
        // cin >> n >> k;
        for(int i = 0; i < n-1; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            // cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        cnt[0] = 1;
        centroidDecomposition(1);
        printf("%lld\n", ans);
        // cout << ans << "\n";
    }
    return 0;
}
// https://cses.fi/problemset/task/2080/
