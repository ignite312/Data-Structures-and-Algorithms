// https://codeforces.com/contest/2146/problem/E
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Segtree {
  // 0-base array indexing
  int n;
  vector<ll> tree, lazy;

  Segtree(int n) {
    this->n = n;
    tree.assign(4 * n, LLONG_MIN);
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
    tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1]);
  }
  void build(vector<ll> &a) {
    build(a, 1, 0, n - 1);
  }
  void push(int idx, int l, int r) {
    if (lazy[idx] != 0) {
      tree[idx] += lazy[idx];
      if (l != r) {
        lazy[2 * idx] += lazy[idx];
        lazy[2 * idx + 1] += lazy[idx];
      }
      lazy[idx] = 0;
    }
  }
  void update(int idx, int l, int r, int ql, int qr, ll val) {
    push(idx, l, r);
    if (l > qr || r < ql) return;
    if (ql <= l && r <= qr) {
      lazy[idx] += val;
      push(idx, l, r);
      return;
    }
    int mid = (l + r) / 2;
    update(idx * 2, l, mid, ql, qr, val);
    update(idx * 2 + 1, mid + 1, r, ql, qr, val);
    tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1]);
  }
  void update(int l, int r, ll val) {
    update(1, 0, n - 1, l, r, val);
  }
  ll query(int idx, int l, int r, int ql, int qr) {
    push(idx, l, r);
    if (l > qr || r < ql) return LLONG_MIN;
    if (ql <= l && r <= qr) return tree[idx];
    int mid = (l + r) / 2;
    return max(query(idx * 2, l, mid, ql, qr),
     query(idx * 2 + 1, mid + 1, r, ql, qr));
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
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    vector<ll> a(n), v(n + 1, 0);
    for (int i = 0; i < n; i++) cin >> a[i];
    Segtree st(n + 1);
    st.build(v);
    for (int i = 0; i < n; i++) {
      st.update(a[i], a[i], -st.query(a[i], a[i]));
      if (a[i] > 0) st.update(0, a[i] - 1, 1);
      cout << st.query(0, n) << " ";
    }
    cout << "\n";
  }
  return 0;
}