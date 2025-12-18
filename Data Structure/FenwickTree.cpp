// https://cses.fi/problemset/task/1648/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct FenwickTree {
  // 0-based array indexing
  vector<ll> bit;
  int n;
  
  FenwickTree(int n) {
    this -> n = n;
    bit.assign(n, 0);
  }
  ll sum(int r) {
    ll ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      ret += bit[r];
    return ret;
  }
  ll sum(int l, int r) {
    return sum(r) - sum(l - 1);
  }
  void add(int idx, ll delta) {
    for (; idx < n; idx = idx | (idx + 1))
      bit[idx] += delta;
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
    FenwickTree ft(n);
    for(int i = 0; i < n; i++) {
        ft.add(i, -ft.sum(i, i) + a[i]);
    }
    while (q--) {
      int type;
      cin >> type;
      if (type == 1) {
        int s;
        ll x;
        cin >> s >> x;
        --s;
        ft.add(s, -ft.sum(s, s) + x);
        a[s] = x;
      } else {
        int l, r;
        cin >> l >> r;
        --l;
        --r;
        cout << ft.sum(l, r) << "\n";
      }
    }
  }
  return 0;
}