// https://codeforces.com/gym/105873/problem/I
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_multiset = tree<
    T,
    null_type,
    less_equal<T>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

const int N = 1e5 + 1;
int topic[N];
vector<int> adj[N];
vector<ordered_multiset <int>> s(N);
int n, k;
map<int, vector<pair<int, int>>> mp;
map<pair<int, int>, int> id;
int ans[N];
 
void dfs(int u, int p) {
  s[u].insert(topic[u]);
  for (auto v: adj[u]) {
    if (v == p)  continue;
    dfs(v, u);
    if (s[u].size() < s[v].size()) {
      s[u].swap(s[v]);
    }
    for (auto x: s[v]) {
      s[u].insert(x);
    }
  }
  for(auto pr : mp[u]) {
    int x = pr.first;
    int idx = pr.second;
    int z1 = s[u].order_of_key(x+1);
    int z2 = s[u].order_of_key(x);
    ans[idx] = (z1-z2);
  }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++) {
          cin >> topic[i];
        }
        for(int i = 0; i < n-1; i++) {
          int u, v;
          cin >> u >> v;;
          adj[u].push_back(v);
        }
        for(int i = 1; i <= k; i++) {
            int x, y;
            cin >> x >> y;
            id[{x, y}] = i;
            mp[x].push_back({y, i});
        }
        dfs(1, -1);
        for(int i = 1; i <= k; i++) {
            cout << ans[i] << "\n";
        }
    }
    return 0;
}