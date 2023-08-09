#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5+1;
const ll INF = LLONG_MAX;
vector<pair<int, int>> G[N+1];
bool vis[N+1];
int parent[N+1];
vector<ll> dist(N+1, INF);

void dijkstra(int source) {
    set<pair<ll, int>> st;
    st.insert({0, source});
    dist[source] = 0;
    while (!st.empty()) {
        auto node = *st.begin();
        int curr_node = node.second;
        ll curr_dist = node.first;
        st.erase(st.begin());
        if (vis[curr_node]) continue;
        vis[curr_node] = true;
        for (auto child : G[curr_node]) {
            int child_node = child.first;
            ll wt = child.second;
            if (dist[curr_node] + wt < dist[child_node]) {
                parent[child_node] = curr_node;
                dist[child_node] = dist[curr_node] + wt;
                st.insert({dist[child_node], child_node});
            }
        }
    }
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    while(tt--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int u, v, wt;
            cin >> u >> v >> wt;
            G[u].push_back({v, wt});
            G[v].push_back({u, wt});
        }
        dijkstra(1);
        if(dist[n] == INF)cout << "-1" << "\n";
        else {
            vector<int> ans;
            int now = n;
            while(now != 1) {
                ans.push_back(now);
                now = parent[now];
            }
            ans.push_back(1);
            reverse(ans.begin(), ans.end());
            for (auto ele : ans)cout << ele << " ";
        }
    }
    return 0;
}
// https://codeforces.com/contest/20/submission/217857087
