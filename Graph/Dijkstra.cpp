#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5+1;
const ll INF = LLONG_MAX;
vector<pair<int, ll>> G[N+1];
vector<bool> vis(N+1);
vector<ll> dist(N+1, INF);

void dijkstra(int source) {
    set<pair<ll, int>> st;
    st.insert({0, source});
    dist[source] = 0;
    while(st.size() > 0) {
        auto node = *st.begin();
        int curr_node = node.second;
        st.erase(st.begin());
        if(vis[curr_node])continue;
        vis[curr_node] = true;
        for(auto child : G[curr_node]) {
            int child_node = child.first;
            ll wt = child.second;
            if(dist[curr_node] + wt  < dist[child_node]) {
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
    for(int i = 1; i <= m; i++) {
        int u, v;
        ll wt;
        cin >> u >> v >> wt;
        G[u].push_back({v, wt});
    }
    dijkstra(1);
    for(int i = 1; i <= n; i++)cout << dist[i] << " ";
  }
}
