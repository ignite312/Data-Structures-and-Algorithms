// https://www.hackerrank.com/contests/srbd-code-contest-2025-round-1/challenges/martian-kaif
#include<bits/stdc++.h>
using namespace std;
#define ll long long

struct SCC {
    // 1-base indexing
    // 1 2 // 2 1 // 1 3 // 2 4
    int n;
    vector<vector<int>> adj, radj;
    vector<int> todo, comps, id;
    vector<bool> vis;
    void init(int _n) {
        n = _n;
        adj.resize(n+1), radj.resize(n+1), id.assign(n+1, -1), vis.resize(n+1);
    }
    void build(int x, int y) {adj[x].push_back(y), radj[y].push_back(x);}
    void dfs(int x) {
        vis[x] = 1;
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
        int c_id = 0;
        for(auto x : todo) if(id[x] == -1) {
            ++c_id;
            dfs2(x, c_id);
            comps.push_back(c_id); // store the unique ids
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
        SCC scc;
        scc.init(n);
        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            scc.build(u, v);
        }
        scc.gen();
        int n_n = scc.comps.size();
        vector<int> c_size(n_n+1);
        for(int i = 1; i <= n; i++) {
            c_size[scc.id[i]]++;
        }

        /***SCC to DAG***/
        vector<vector<int>> dag(n_n+1);
        for(int u = 1; u <= n; u++) {
            for(auto v : scc.adj[u]) {
                int cu = scc.id[u], cv = scc.id[v];
                if(cu != cv) dag[cu].push_back(cv);
            }
        }
        for(int i = 1; i <= n_n; i++) {
            sort(dag[i].begin(), dag[i].end());
            dag[i].erase(unique(dag[i].begin(), dag[i].end()), dag[i].end());
        }

        for(auto x : scc.comps) {
            for(int j = 1; j <= 1; j++) {
                dp[x][j] = c_size[x];
            }
        }
        for(int i = 2; i <= k; i++) {
            for(auto u : scc.comps) {
                dp[u][i] = 0;
                for (auto v : dag[u]) {
                    dp[u][i] = max(dp[u][i], dp[v][i-1] + c_size[u]);
                }
            }
        }
        ll ans = 0;
        for(auto u : scc.comps) {
            for(int j = 1; j <= k; j++) {
                ans = max(ans, dp[u][j]);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}