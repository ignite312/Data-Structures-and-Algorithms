/*
https://codeforces.com/contest/2002/problem/D1
Checking a permutation is valid dfs order or not
Prac: https://codeforces.com/contest/2002/problem/D2
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 65535+1;
vector<int> adj[N];
int pos[N];

bool cmp(int a, int b) {
    return pos[a] < pos[b];
}
void dfs(int v, int& counter, bool& flag, const vector<int>& p) {
    counter++;
    if(counter == p.size()) {
        flag = true;
        return;
    }
    sort(adj[v].begin(), adj[v].end(), cmp);
    for(int u : adj[v]) {
        if(u == p[counter]) {
            dfs(u, counter, flag, p);
            if(flag) return;
        }
    }
}
bool check(vector<int>& p) {
    int counter = 0;
    bool flag = false;
    dfs(p[0], counter, flag, p);
    return flag;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while (tt--) {
        int n, q;
        cin >> n >> q;
        for(int i = 0; i <= n; i++) {
            adj[i].clear();
        }

        for(int i = 2; i <= n; i++) {
            int x;
            cin >> x;
            adj[x].push_back(i);
        }
        vector<int> p(n);
        for(int i = 0; i < n; i++) {
            cin >> p[i];
            pos[p[i]] = i;
        }
        while(q--) {
            int u, v;
            cin >> u >> v;
            swap(pos[p[u - 1]], pos[p[v - 1]]);
            swap(p[u - 1], p[v - 1]);
            cout << (check(p) ? "YES\n" : "NO\n");
        }
    }
    return 0;
}