// https://cses.fi/problemset/task/1647/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

template<typename T>
  struct SparseTable {
    vector<vector<T>> st;
    vector<int> log;
    SparseTable(int n) { // 0-based array
      int maxLog = log2(n) + 1;
      st.assign(n, vector<T> (maxLog));
      log.assign(n + 1, 0);
      for(int i = 2; i <= n; i++) {
        log[i] = log[i / 2] + 1;
      }
    }
    void build(vector<T> & arr) {
      int n = arr.size();
      int maxLog = log2(n) + 1;
      for(int i = 0; i < n; i++) { st[i][0] = arr[i]; }
      for(int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; i + (1 << j) <= n; i++) {
          st[i][j] = fn(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
      }
    }
    // Idempotent: min/max/gcd/lcm/AND/OR
    inline T fn(T a, T b) { return min(a, b); }
    inline T query(int L, int R) { // 0-based
      int j = log[R - L + 1];
      return fn(st[L][j], st[R - (1 << j) + 1][j]);
    }
  };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        int n, q;
        cin >> n >> q;
        vector<int> v(n);
        SparseTable<int> MN(n);
        for(int i = 0; i < n; i++) {
            cin >> v[i];
        }
        MN.build(v);
        while(q--) {
            int l, r;
            cin >> l >> r;
            cout << MN.query(--l, --r) << "\n";
        }
    }
    return 0;
}