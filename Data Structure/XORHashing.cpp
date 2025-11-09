// https://codeforces.com/contest/2014/problem/H
#include <bits/stdc++.h>
using namespace std;
#define ll long long

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct XORHash {
  vector<ll> pref;
  unordered_map<int, ll> hsh;

  XORHash(const vector<int> & arr) {
    int n = arr.size();
    pref.assign(n + 1, 0);

    for(int x: arr) {
      if (!hsh.count(x)) hsh[x] = rng();
    }
    for(int i = 0; i < n; i++) {
      pref[i + 1] = pref[i] ^ hsh[arr[i]];
    }
  }
  ll get(int l, int r) { // 0-based
    return pref[r + 1] ^ pref[l];
  }
  bool equal(int l1, int r1, int l2, int r2) { // 0-based
    return get(l1, r1) == get(l2, r2);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  cin >> tt;
  while(tt--) {
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    XORHash xh(arr);
    while(q--) {
      int l, r;
      cin >> l >> r;
      --l, --r;
      if(xh.get(l, r) == 0) {
        cout << "YES\n";
      }else cout << "NO\n";
    }
  }
  return 0;
}