#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 1;
int values[N+1], subtree[N+1], parent[N+1], depth[N+1];
int heavy[N+1], head[N+1], id[N+1];
vector<int> G[N+1];
 
struct Segtree {
    int size;
    vector<int> tree;
 
    void init(int n) {
        size = 1;
        while(size < n) size = size << 1;
        tree.assign(2*size - 1, 0);
    }
    int merge(int x, int y) {
        return max(x, y);
    }
    void build(vector<int> &a, int node, int l, int r) {
        if(l == r) {
            tree[node] = a[l];
            return;
        }
        int mid = l + (r - l)/2;
        build(a, node*2+1, l, mid);
        build(a, node*2+2, mid+1, r);
        tree[node] = merge(tree[node*2+1], tree[node*2+2]);
    }
    void build(vector<int> &a) {
        build(a, 0, 0, size-1);
    }
    void update(int i, int value, int node, int l, int r) {
        if(l == i && r == i) {
            tree[node] = value;
            return;
        }
        int mid = l + (r-l)/2;
        if(i <= mid)update(i, value, node*2+1, l, mid);
        else update(i, value, node*2+2, mid+1, r);
        tree[node] = merge(tree[node*2+1], tree[node*2+2]);
    }
    void update(int i, int value) {
        update(i, value, 0, 0, size-1);
    }
    int query(int i, int j, int node, int l, int r) {
        if(l > j || r < i) return INT_MIN;
        if(l >= i && r <= j)return tree[node];
        int mid = l + (r - l)/2;
        int ans1 = query(i, j, node*2+1, l, mid);
        int ans2 = query(i, j, node*2+2, mid+1, r);
        return merge(ans1, ans2);
    }
    int query(int i, int j) {
        return query(i, j, 0, 0, size-1);
    }
} st;
void dfs(int node, int par) {
  subtree[node] = 1;
  int mx = 0;
  for(auto child : G[node]) {
    if(child == par)continue;
    parent[child] = node;
    depth[child] = depth[node]+1;
    dfs(child, node);
    subtree[child]+=subtree[node];
    if(subtree[child] > mx) {
      mx = subtree[child];
      heavy[node] = child;
    }
  }
}
int idx;
void HLD(int node, int h) {
  head[node] = h;
  id[node] = idx++;
  if(heavy[node])HLD(heavy[node], h);
  for(auto child : G[node]) {
    if(child != parent[node] && child != heavy[node]) {
      HLD(child, child);
    }
  }
}
int path(int x, int y) {
  int ans = 0;
  while(head[x] != head[y]) {
    if(depth[head[x]] > depth[head[y]]) swap(x, y);
    ans = max(ans, st.query(id[head[y]], id[y]));
    y = parent[head[y]];
  }
  if(depth[x] > depth[y])swap(x, y);
  ans = max(ans, st.query(id[x], id[y]));
  return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        int n, q;
        cin >> n >> q;
        for(int i = 0; i < n; i++)cin >> values[i];
        for(int i = 0; i < n-1; i++) {
          int u, v;
          cin >> u >> v;
          G[u].push_back(v);
          G[v].push_back(u);
        }
        dfs(1, -1);
        HLD(1, 1);
        vector<int> a(n);
        for(int i = 0; i < n; i++)a[id[i+1]] = values[i];
        st.init(n), st.build(a);
        while(q--) {
          int type;
          cin >> type;
          if(type == 1) {
            int s, x;
            cin >> s >> x;
            st.update(id[s], x);
          }else {
            int a, b;
            cin >> a >> b;
            cout << path(a, b) << " ";
          }
        }
    }
    return 0;
}
// https://cses.fi/problemset/task/2134/
