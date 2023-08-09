#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 500 + 5;
const ll INF = LLONG_MAX;
ll dist[N+5][N+5];
int n, m;

void init() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            dist[i][j] = INF;
        }
        dist[i][i] = 0;
    }
}
void floydWarshall() {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                } 
            }
        }
    }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  while(tt--) {
    int q;
    cin >> n >> m >> q;
    init();
    for(int i = 1; i <= m; i++) {
        int u, v;
        ll wt;
        cin >> u >> v >> wt;
        --u, --v;
        dist[u][v] = min(dist[u][v], wt);
        dist[v][u] = min(dist[v][u], wt);
    }
    floydWarshall();
    while(q--) {
        int st, en;
        cin >> st >> en;
        --st, --en;
        if(dist[st][en] != INF)cout << dist[st][en] << "\n";
        else cout << "-1" << "\n";
    }
  }
}
// https://cses.fi/problemset/task/1672
