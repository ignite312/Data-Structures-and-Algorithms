/*
https://codeforces.com/contest/1929/problem/D
AC: https://codeforces.com/contest/1929/submission/248276098
dp[u][0] =  The number of possible ways so that the subtree rooted at node u has no pairs with a ancestor-descendant relationships.
dp[u][1] =  The number of possible ways so that the subtree rooted at node u has exactly one ancestor-descendant relationship.
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int M = 998244353;
const int N = 3e5 + 1;
vector<int> adj[N+1];
ll dp[N+1][2];

void f(int u, int p) {
    dp[u][0] = 1;
    dp[u][1] = 0;
    for(auto v : adj[u]) {
        if(v == p)continue;
        f(v, u);
        dp[u][0] = (dp[u][0] * (1 + dp[v][0])) % M;
        dp[u][1] = (dp[u][1] + (dp[v][0] + dp[v][1]) % M) % M;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie();
    int tt;
    cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        for(int i = 0; i <= n; i++) {
            adj[i].clear();
        }
        for(int i = 0; i < n-1; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        f(1, -1);
        cout << ((dp[1][0] + dp[1][1] + 1) % M) << "\n";
    }
}