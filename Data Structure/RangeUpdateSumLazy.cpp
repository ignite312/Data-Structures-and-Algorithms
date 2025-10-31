/*
Problem Name: Range Update Queries
Problem Link: https://cses.fi/problemset/task/1651/
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Segtree {
  // 0-based array indexing
  int n;
  vector<ll> tree, lazy;
  Segtree(int n) {
    this->n = n;
    tree.assign(4 * n, 0);
    lazy.assign(4 * n, 0);
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
  void push(int idx, int l, int r) {
    if (lazy[idx] == 0) return;
    int mid = (l + r) / 2;
    int left = idx * 2, right = idx * 2 + 1;

    tree[left] += (mid - l + 1) * lazy[idx];
    tree[right] += (r - mid) * lazy[idx];

    lazy[left] += lazy[idx];
    lazy[right] += lazy[idx];
    lazy[idx] = 0;
  }
  void update(int idx, int l, int r, int ql, int qr, ll val) {
    if (l > qr || r < ql) return;
    if (ql <= l && r <= qr) {
      tree[idx] += (r - l + 1) * val;
      lazy[idx] += val;
      return;
    }
    if (lazy[idx]) push(idx, l, r);
    int mid = (l + r) / 2;
    update(idx * 2, l, mid, ql, qr, val);
    update(idx * 2 + 1, mid + 1, r, ql, qr, val);
    tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
  }
  void update(int l, int r, ll val) {
    update(1, 0, n - 1, l, r, val);
  }
  ll query(int idx, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return 0;
    if (ql <= l && r <= qr) return tree[idx];
    if (lazy[idx]) push(idx, l, r);
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
  int tt;
  tt = 1;
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
        int i, j;
        ll value;
        cin >> i >> j >> value;
        st.update(--i, --j, value);
      } else {
        int i;
        cin >> i;
        cout << st.query(i - 1, i - 1) << "\n";
      }
    }
  }
  return 0;
}