// https://cses.fi/problemset/task/1648/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Segtree {
    // 0-based array indexing
    int n;
    vector<ll> tree;
    Segtree(int n = 0) : n(n), tree(4*n, 0) {}
    ll merge(ll x, ll y) { return x + y; } // Associative: SUM\MIN\MAX\GCD\LCM\OR\AND\XOR
    void build(vector<int> &a) {
        for (int i = 0; i < n; i++) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; i--) 
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
    }
    void update(int pos, ll val) {
        for (tree[pos += n] = val; pos > 1; pos >>= 1) // increment or set
            tree[pos >> 1] = merge(tree[pos], tree[pos ^ 1]);
    }
    ll query(int l, int r) {
        ll res = 0; // identity
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res = merge(res, tree[l++]);
            if (!(r & 1)) res = merge(res, tree[r--]);
        }
        return res;
    }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt = 1;
  // cin >> tt;
  while (tt--) {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    Segtree st(n);
    st.build(a);
    while (q--) {
      int type;
      cin >> type;
      if (type == 1) {
        int s;
        ll x;
        cin >> s >> x;
        --s;
        st.update(s, x);
        a[s] = x;
      } else {
        int l, r;
        cin >> l >> r;
        --l; --r;
        cout << st.query(l, r) << "\n";
      }
    }
  }
  return 0;
}