// https://www.spoj.com/problems/JHNSN/

#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = LLONG_MAX;
const int N = 100+1;

struct Edge {
    int u, v;
    ll wt;
    Edge(){}
    Edge(int u, int v, ll wt) : u(u), v(v), wt(wt){}
};
bool bellmanFord(int st, int n, vector<Edge> &edges, vector<ll> &dist) {
    dist[st] = 0;
    for(int i = 0; i <= n; i++) {
        bool ok = false;
        for(auto ed: edges) {
            if(dist[ed.u] < INF) {
                if(dist[ed.u] + ed.wt < dist[ed.v]) {
                    dist[ed.v] = dist[ed.u] + ed.wt;
                    ok = true;
                }
            }
        }
        if(!ok)return true;
    }
    return false;
}
vector<ll> dijkstra(int source, int n, vector<Edge> &edges, const vector<pair<ll, int>> G[]) {
    set<pair<ll, int>> st;
    vector<ll> dist(n+1, INF);
    vector<bool> vis(n+1, false);
    st.insert({0, source});
    dist[source] = 0;
    while(!st.empty()) {
        auto node = *st.begin();
        st.erase(st.begin());
        int curr_node = node.second;
        ll curr_dist = node.first;
        if(vis[curr_node])continue;
        vis[curr_node] = true;
        for(auto child : G[curr_node]) {
            int child_node = child.first;
            ll child_dist = child.second;
            if(dist[curr_node] + child_dist < dist[child_node]) {
                dist[child_node] = dist[curr_node] + child_dist;
                st.insert({dist[child_node], child_node});
            }
        }
    }
    return dist;
}
ll ans[N+1][N+1];
bool johnson(vector<Edge> &edges, int n) {
    for(int i = 1; i <= n; i++)edges.emplace_back(0, i, 0);
    vector<ll> h(n+1, INF);
    if(!bellmanFord(0, n, edges, h))return false;
    cout << "yes\n\n";
    for(int i = 1; i <= n; i++){cout << h[i] << " ";}
        cout << h[0] << "\n\n";
    for(int i = 1; i <= n; i++)edges.pop_back();
    vector<pair<ll, int>> G[n+1];
    for(auto ed : edges) {G[ed.u].emplace_back(ed.v, ed.wt + h[ed.u] - h[ed.v]);}
    for(int i = 1; i <= n; i++) {
        vector<ll> dist = dijkstra(i, n, edges, G);
        for(int j = 1; j <= n; j++) {
            if(dist[j] < INF) dist[j] -= h[i] - h[j];
            ans[i][j] = dist[j];
        }
    }
    return true;
}
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt, cs = 1;
  cin >> tt;
  while(tt--) {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges;
    for(int i = 0; i < m; i++) {
        int u, v;
        ll wt;
        cin >> u >> v >> wt;
        edges.emplace_back(u, v, wt);
    }
    cout << "graph " << cs++ << ' ';
    int ok = johnson(edges, n);
    if(!ok){
      cout << "no\n";
      continue;
    }
    for (int i = 1; i <= n; i++){
      for (int j = 1; j <= n; j++){
        if(j > 1) cout << ' ';
        if(ans[i][j] < INF) cout << ans[i][j];
        else cout << "#";
      }
      cout << '\n';
    }
  }
  return 0;
}