// https://codeforces.com/gym/106208/problem/B
#include<bits/stdc++.h>

using namespace std;
#define int long long
const int N = 200001;
const int mod = 1000000000;
vector < int > adj[N];
int kval[N], pval[N];
map < int, int > id;
vector < int > c_vals;
int c_sz;

struct PST {
  // 0 based indexing
  int data;
  PST * left, * right;

  int merge(int x, int y) {
    return x + y;
  }
  void build(vector < int > & a, int l, int r) {
    if (l == r) {
      data = a[l];
      return;
    }
    int mid = l + ((r - l) >> 1);
    left = new PST();
    right = new PST();
    left -> build(a, l, mid);
    right -> build(a, mid + 1, r);
    data = merge(left -> data, right -> data);
  }
  PST * update(int i, int value, int l, int r) {
    if (l > i || r < i) return this;
    if (l == i && r == i) {
      PST * rslt = new PST();
      rslt -> data = value;
      return rslt;
    }
    int mid = l + ((r - l) >> 1);
    PST * rslt = new PST();

    rslt -> left = left -> update(i, value, l, mid);
    rslt -> right = right -> update(i, value, mid + 1, r);
    rslt -> data = merge(rslt -> left -> data, rslt -> right -> data);

    return rslt;
  }
  int query(int i, int j, int l, int r) {
    if (l > j || r < i) return 0;
    if (l >= i && r <= j) return data;
    int mid = l + ((r - l) >> 1);
    return merge(left -> query(i, j, l, mid), right -> query(i, j, mid + 1, r));
  }
}* roots[N];

const int LOG = 18; // LOG = ceil(log2(N))
int up[N][LOG], depth[N]; // up[v][j] is the 2^j-th Anchestor of node v

void ancestor(int u, int p) {
  for (auto v: adj[u]) {
    if (v == p) continue;
    depth[v] = depth[u] + 1;
    up[v][0] = u;
    for (int j = 1; j < LOG; j++) up[v][j] = up[up[v][j - 1]][j - 1];
    ancestor(v, u);
  }
}
void dfs(int u, int p) {
  for (auto v: adj[u]) {
    if (v == p) continue;
    roots[v] = roots[u];
    int prev = roots[v] -> query(id[pval[v]], id[pval[v]], 0, c_sz - 1);
    roots[v] = roots[v] -> update(id[pval[v]], kval[v] + prev, 0, c_sz - 1);
    dfs(v, u);
  }
}
int getKthAncestor(int a, int k) {
  for (int i = LOG - 1; i >= 0; i--)
    if (k & (1 << i))
      a = up[a][i];
  return a;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  // cin >> tt;
  while (tt--) {
    int n, q;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
      int a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
    depth[1] = 0;
    ancestor(1, -1);
    for (int i = 1; i <= n; ++i) {
      cin >> kval[i] >> pval[i];
      c_vals.push_back(pval[i]);
    }
    sort(c_vals.begin(), c_vals.end());
    c_vals.erase(unique(c_vals.begin(), c_vals.end()), c_vals.end());
    c_sz = c_vals.size();
    for (int i = 0; i < c_sz; i++) {
      id[c_vals[i]] = i;
    }

    vector < int > v(c_sz, 0);
    roots[0] = new PST();
    roots[0] -> build(v, 0, c_sz - 1);
    roots[1] = roots[0];
    roots[1] = roots[1] -> update(id[pval[1]], kval[1], 0, c_sz - 1);
    dfs(1, 0);

    cin >> q;
    int ansPrev = 0;
    for (int i = 0; i < q; ++i) {
      int u, d, pl, pu;
      cin >> u >> d >> pl >> pu;
      u = (int)((u + ansPrev) % n) + 1;
      d = (int)((d + ansPrev) % n);
      pl = ((pl + ansPrev) % mod) + 1;
      pu = ((pu + ansPrev) % mod) + 1;
      if (pl > pu) swap(pl, pu);

      int targetDepth = depth[u] - d;
      if (targetDepth <= 0) {
        targetDepth = 0;
      }
      int upSteps = depth[u] - targetDepth;
      int anc = getKthAncestor(u, upSteps);
      int parentAnc = up[anc][0];

      int L = lower_bound(c_vals.begin(), c_vals.end(), pl) - c_vals.begin();
      int R = (upper_bound(c_vals.begin(), c_vals.end(), pu) - c_vals.begin()) - 1;

      if (L < 0) L = 0;
      if (R > c_sz - 1) R = c_sz - 1;

      int res = 0;
      if (L <= R) {
        res = roots[u] -> query(L, R, 0, c_sz - 1) - roots[parentAnc] -> query(L, R, 0, c_sz - 1);
      }
      cout << res << '\n';
      ansPrev = res;
    }
  }
  return 0;
}