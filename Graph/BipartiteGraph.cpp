#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
vector<int> G[N + 5];
bool vis[N + 5], is_bipartite;
int color[N + 5];

void dfs(int vertex) {
    vis[vertex] = true;
    for (auto child : G[vertex]) {
        if (!vis[child]) {
            color[child] = color[vertex] ^ 1;
            dfs(child);
        } else {
            if (color[vertex] == color[child])is_bipartite = true;
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    cin >> tt;
    while (tt--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        vector<int> ans;
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                color[i] = 0;
                dfs(i);
            }
        }
        if (is_bipartite) cout << "IMPOSSIBLE\n";
        else {
            for (int i = 1; i <= n; i++) {
                if (color[i]) cout << "1 ";
                else cout << "2 ";
            }
        }
    }
    return 0;
}
