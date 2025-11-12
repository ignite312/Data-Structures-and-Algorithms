// https://www.hackerrank.com/contests/srbd-code-contest-2025-round-1/challenges/martian-kaif
#include<bits/stdc++.h>
using namespace std;
#define ll long long

struct SCC {
    // 1-base indexing
    // 1 2 // 2 1 // 1 3 // 2 4 -> why radj
    int n;
    int c_id; // unique id starting from 1
    vector<vector<int>> adj, radj;
    vector<int> todo, id;
    vector<bool> vis;
    SCC(int _n) : n(_n) {
        c_id = 0;
        adj.resize(n+1), radj.resize(n+1), id.assign(n+1, -1), vis.resize(n+1);
    }
    void build(int x, int y) { adj[x].push_back(y), radj[y].push_back(x); }
    void dfs(int x) {
        vis[x] = true;
        for(auto y : adj[x]) if (!vis[y]) dfs(y);
        todo.push_back(x);
    }
    void dfs2(int u, int c_id) {
        id[u] = c_id;
        for(auto v : radj[u]) if(id[v] == -1) dfs2(v, c_id);
    }
    void gen() {
        for(int i = 1; i <= n; i++) if (!vis[i]) dfs(i);
        reverse(todo.begin(), todo.end());
        for(auto x : todo) if(id[x] == -1) {
            ++c_id;
            dfs2(x, c_id);
        }
    }
};

ll dp[200001][129];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        int n, m, k;
        cin >> n >> m >> k;
        SCC scc(n);
        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            scc.build(u, v);
        }
        scc.gen();
        int total_comps = scc.c_id;
        vector<int> c_size(total_comps+1);
        for(int i = 1; i <= n; i++) {
            c_size[scc.id[i]]++;
        }
        // SCC to DAG...
        vector<vector<int>> dag(total_comps+1);
        for(int u = 1; u <= n; u++) {
            for(auto v : scc.adj[u]) {
                int cu = scc.id[u], cv = scc.id[v];
                if(cu != cv) dag[cu].push_back(cv);
            }
        }
        for(int i = 1; i <= total_comps; i++) {
            sort(dag[i].begin(), dag[i].end());
            dag[i].erase(unique(dag[i].begin(), dag[i].end()), dag[i].end());
        }
        // ...End
        for(int id = 1; id <= total_comps; id++) {
            for(int j = 1; j <= 1; j++) {
                dp[id][j] = c_size[id];
            }
        }
        for(int i = 2; i <= k; i++) {
            for(int u = 1; u <= total_comps; u++) {
                dp[u][i] = 0;
                for (auto v : dag[u]) {
                    dp[u][i] = max(dp[u][i], dp[v][i-1] + c_size[u]);
                }
            }
        }
        ll ans = 0;
        for(int u = 1; u <= total_comps; u++) {
            for(int j = 1; j <= k; j++) {
                ans = max(ans, dp[u][j]);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}