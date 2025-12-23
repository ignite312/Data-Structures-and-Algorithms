// https://codeforces.com/contest/600/submission/227278225
// https://codeforces.com/blog/entry/44351
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100001;
int color[N], subtree[N], cnt[N];
ll t_ans[N], ans[N];
vector<int> adj[N], a[N];

void dfs(int u, int p) {
  subtree[u] = 1;
  for(auto v : adj[u]) {
    if(v == p)continue;
    dfs(v, u);
    subtree[u]+=subtree[v];
  }
}
void update(int &mx_cnt, int u, int x) {
  t_ans[cnt[color[u]]] -= color[u];
  cnt[color[u]] +=x;
  t_ans[cnt[color[u]]] += color[u];
  mx_cnt = max(mx_cnt, cnt[color[u]]);
}
int smallToLarge(int u, int p, bool keep) {
  int mx_cnt = 0, mx_subtree = -1, bigchild = -1;
  for(auto v : adj[u]) {
    if(v == p)continue;
    if(subtree[v] > mx_subtree) {
      mx_subtree = subtree[v];
      bigchild = v;
    }
   }
  for(auto v : adj[u])
    if(v != p && v != bigchild)
      smallToLarge(v, u, 0);

  if(bigchild != -1) {
    mx_cnt = max(mx_cnt, smallToLarge(bigchild, u, 1));
    swap(a[bigchild], a[u]);
  }

  a[u].push_back(u);
  update(mx_cnt, u, 1);

  for(auto v : adj[u]) {
    if(v != p && v != bigchild) {
      for(auto ele : a[v]) {
        update(mx_cnt, ele, 1);
        a[u].push_back(ele);
      }
    }
  }
  ans[u] = t_ans[mx_cnt];
  if(!keep)for(auto ele : a[u])update(mx_cnt, ele, -1);
  return mx_cnt;
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
        for(int i = 1; i <= n; i++) {
          cin >> color[i];
        }
        for(int i = 0; i < n-1; i++) {
          int u, v;
          cin >> u >> v;;
          adj[u].push_back(v);
          adj[v].push_back(u);
        }
        dfs(1, -1);
        smallToLarge(1, -1, 0);
        for(int i = 1; i <= n; i++)cout << ans[i] << " ";
    }
    return 0;
}