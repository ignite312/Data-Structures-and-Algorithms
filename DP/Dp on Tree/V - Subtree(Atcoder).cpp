/*
https://atcoder.jp/contests/dp/tasks/dp_v
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5 + 1;
const int M = 1e9+7;
vector<int> adj[N+1];
ll dp[N+1][2];

void dfs(int u, int p) {
    dp[u][0] = 1;
    dp[u][1] = 1;
    for(auto v : adj[u]) {
        if(v == p)continue;
        dfs(v, u);
        dp[u][0] = dp[u][0]*((dp[v][0] + dp[v][1]) % M) % M;
        dp[u][1] = dp[u][1]*dp[v][0] % M;
    }
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
        for(int i = 0; i < n-1; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(1, -1);
        cout << (dp[1][0] + dp[1][1]) % M << "\n";
    }
    return 0;
}