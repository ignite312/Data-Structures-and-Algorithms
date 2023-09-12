#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<int> G[N + 5];
bool vis[N + 5], cycle_found;
int parent[N + 5], en, st;

void dfs(int vertex, int par) {
    vis[vertex] = true;
    for (auto child : G[vertex]) {
        if(par == child) continue;
        if(!vis[child]) {
            parent[child] = vertex;
            dfs(child, vertex);
        }else {
            if(!cycle_found) en = vertex, st = child;
            cycle_found = true;
            return;
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    while(tt--) {
        int n, m;
        cin >> n >> m;
        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        for(int i = 1; i <= n; i++) {
            if (!vis[i]) {
                parent[i] = -1;
                dfs(i, -1);
            }
        }
        if(!cycle_found) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        vector<int> ans;
        ans.push_back(st);
        ans.push_back(en);
        int j = en;
        while(parent[j] != st) {
            ans.push_back(parent[j]);
            j = parent[j];
        }
        ans.push_back(st);
        cout << ans.size() << "\n";
        for(int i = ans.size() - 1; i >= 0; i--)cout << ans[i] << " ";
    }
    return 0;
}
// https://cses.fi/problemset/task/1669/
