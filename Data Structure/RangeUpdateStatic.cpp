// https://cses.fi/problemset/task/1648/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200001;

struct Segtree {
  // 0-based array indexing
  int n;
  vector<ll> tree;
  Segtree(int n) {
    this->n = n;
    tree.assign(4 * n, 0);
  }
  void build(vector<ll> &a, int idx, int l, int r) {
    if (l == r) {
      tree[idx] = a[l];
      return;
    }
    int mid = (l + r) / 2;
    build(a, idx * 2, l, mid);
    build(a, idx * 2 + 1, mid + 1, r);
    tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
  }
  void build(vector<ll> &a) {
    build(a, 1, 0, n - 1);
  }
  void update(int idx, int l, int r, int pos, ll val) {
    if (l == r) {
      tree[idx] = val; // increment or set
      return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(idx * 2, l, mid, pos, val);
    else update(idx * 2 + 1, mid + 1, r, pos, val);
    tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
  }
  void update(int pos, ll val) {
    update(1, 0, n - 1, pos, val);
  }
  ll query(int idx, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return 0;
    if (ql <= l && r <= qr) return tree[idx];
    int mid = (l + r) / 2;
    return query(idx * 2, l, mid, ql, qr) +
           query(idx * 2 + 1, mid + 1, r, ql, qr);
  }
  ll query(int l, int r) {
    return query(1, 0, n - 1, l, r);
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
    vector<ll> a(n);
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