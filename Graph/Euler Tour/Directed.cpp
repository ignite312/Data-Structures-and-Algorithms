/*
Problem Name: Teleporters Path
Problem Link: https://cses.fi/problemset/task/1693/
Idea: Euler Trail in Directed graph (Hierholzer’s Algorithm)
Complexity: O(E)
Resource: https://usaco.guide/adv/eulerian-tours?lang=cpp
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 100001;
vector<int> adj[N];
int in[N], out[N];
vector<int> euler_trail;
 
void dfs(int u) {
    while(!adj[u].empty()) {
        int v = adj[u].back();
        adj[u].pop_back();
        dfs(v);
    }
    euler_trail.push_back(u);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        int n, m;
        cin >> n >> m;
        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            out[u]++, in[v]++;        
        }
        /*
        Directed Graphs:
        Euler Circuit: All vertices must have equal in-degree and out-degree.
        Euler Trail: Exactly two vertices can have a difference of one between their in-degree and out-degree.
        */
        for(int i = 1; i <= n; i++) {
            if((i == 1 && out[1]-in[1] != 1) || 
                (i == n && in[n]-out[n] != 1) ||
                (i > 1 && i < n && out[i] != in[i])) {
                cout << "IMPOSSIBLE\n";
                return 0;
            }
        }
        dfs(1);
        reverse(euler_trail.begin(), euler_trail.end());
        if(euler_trail.size() - 1 !=  m || euler_trail.back() != n) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        for(auto x : euler_trail) {cout << x << " ";}
    }
    return 0;
}