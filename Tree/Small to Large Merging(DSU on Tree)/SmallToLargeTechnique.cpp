#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5 + 1;
int color[N+1], subtree[N+1], cnt[N+1];
ll t_ans[N+1], ans[N+1];
vector<int> G[N+1], v[N+1];

void dfs(int node, int p) {
  subtree[node] = 1;
  for(auto child : G[node]) {
    if(child == p)continue;
    dfs(child, node);
    subtree[node]+=subtree[child];
  }
}

void update(int &mx_cnt, int node, int x) {
  t_ans[cnt[color[node]]] -= color[node];
  cnt[color[node]] +=x;
  t_ans[cnt[color[node]]] += color[node];
  mx_cnt = max(mx_cnt, cnt[color[node]]);
}

int smallToLarge(int node, int p, bool keep) {
  int mx_cnt = 0, mx_subtree = -1, bigchild = -1;
  for(auto child : G[node]) {
    if(child == p)continue;
    if(subtree[child] > mx_subtree) {
      mx_subtree = subtree[child];
      bigchild = child;
    }
   }

  for(auto child : G[node])
    if(child != p && child != bigchild)
      smallToLarge(child, node, 0);

  if(bigchild != -1) {
    mx_cnt = max(mx_cnt, smallToLarge(bigchild, node, 1));
    swap(v[bigchild], v[node]);
  }

  v[node].push_back(node);
  update(mx_cnt, node, 1);

  for(auto child : G[node]) {
    if(child != p && child != bigchild) {
      for(auto ele : v[child]) {
        update(mx_cnt, ele, 1);
        v[node].push_back(ele);
      }
    }
  }

  ans[node] = t_ans[mx_cnt];
  if(!keep)for(auto ele : v[node])update(mx_cnt, ele, -1);
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
          G[u].push_back(v);
          G[v].push_back(u);
        }
        dfs(1, -1);
        smallToLarge(1, -1, 0);
        for(int i = 1; i <= n; i++)cout << ans[i] << " ";
    }
    return 0;
}
// https://codeforces.com/contest/600/submission/227278225
// https://codeforces.com/blog/entry/44351