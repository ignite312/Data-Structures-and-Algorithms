/*
Problem Name: Round Trip
Problem Link: https://cses.fi/problemset/task/1669/
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 100001;
vector<int> adj[N];
bool vis[N], cycle_found;
int parent[N], en, st;

void dfs(int u, int p) {
    vis[u] = true;
    for (auto v : adj[u]) {
        if (v == p)
            continue;
        if (!vis[v]) {
            parent[v] = u;
            dfs(v, u);
        } else {
            if (!cycle_found)
                en = u, st = v;
            cycle_found = true;
            return;
        }
    }
}
void checkCycle(int n) {
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            parent[i] = -1;
            dfs(i, -1);
        }
    }
    if (!cycle_found) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    vector<int> path = {st, en};
    for (int j = en; parent[j] != st; j = parent[j])
        path.push_back(parent[j]);
    path.push_back(st);

    cout << path.size() << "\n";
    for (int i = path.size() - 1; i >= 0; i--)
        cout << path[i] << " ";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    while (tt--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        checkCycle(n);
    }
    return 0;
}