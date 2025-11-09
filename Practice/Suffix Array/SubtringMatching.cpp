// https://codeforces.com/gym/105973/problem/H
#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {
  string s;
  vector<int> sa, lcp;

  SuffixArray(const string & str) {
    s = str;
    sa = build_suffix_array(s);
    lcp = build_lcp_array(s, sa);
  }
  vector<int> build_suffix_array(const string & s) {
    int n = s.size(), alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);

    for(int i = 0; i < n; i++) cnt[s[i]]++;
    for(int i = 1; i < alphabet; i++) cnt[i] += cnt[i - 1];
    for(int i = 0; i < n; i++) p[--cnt[s[i]]] = i;

    c[p[0]] = 0;
    int classes = 1;
    for(int i = 1; i < n; i++) {
      if(s[p[i]] != s[p[i - 1]]) classes++;
      c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for(int h = 0; (1 << h) < n; ++h) {
      for(int i = 0; i < n; i++) {
        pn[i] = p[i] - (1 << h);
        if(pn[i] < 0) pn[i] += n;
      }

      fill(cnt.begin(), cnt.begin() + classes, 0);
      for(int i = 0; i < n; i++) cnt[c[pn[i]]]++;
      for(int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
      for(int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];

      cn[p[0]] = 0;
      classes = 1;
      for(int i = 1; i < n; i++) {
        pair<int, int> cur = { c[p[i]], c[(p[i] + (1 << h)) % n] };
        pair<int, int> prev = { c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]
        };
        if(cur != prev) classes++;
        cn[p[i]] = classes - 1;
      }
      c.swap(cn);
    }
    return p;
  }
  vector<int> build_lcp_array(const string & s, const vector<int> &sa) {
    int n = s.size();
    vector<int> rank(n), lcp(n);
    for(int i = 0; i < n; i++) rank[sa[i]] = i;
    int h = 0;
    for(int i = 0; i < n; i++) {
      if(rank[i] > 0) {
        int j = sa[rank[i] - 1];
        while(i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
        lcp[rank[i]] = h;
        if(h > 0) h--;
      }
    }
    return lcp;
  }
};

template<typename T>
  struct SparseTable {
    // 0-based
    vector<vector<T>> st;
    vector<int> log;
    SparseTable(int n) {
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
      if(R < L) return 0;
      int j = log[R - L + 1];
      return fn(st[L][j], st[R - (1 << j) + 1][j]);
    }
  };

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  cin >> tt;
  while(tt--) {
    int n, m, q;
    cin >> n >> m >> q;
    string a, b;
    cin >> a >> b;
    string s = a + "$" + b + "$";

    SuffixArray SA(s);
    auto &sa = SA.sa;
    auto &lcp = SA.lcp;

    int sz = sa.size();
    vector<int> up(sz, 0), down(sz + 1, 0);
    int l = n + 1, r = sz - 1;

    for(int i = 1; i < sz; i++) {
      if(sa[i] < n)
        up[i] = i;
      else
        up[i] = up[i - 1];
    }
    for(int i = sz - 1; i >= 0; i--) {
      if(sa[i] < n)
        down[i] = i;
      else
        down[i] = down[i + 1];
    }

    SparseTable<int> ST(sz);
    ST.build(lcp);
    vector<int> dp(m + 1, 0);

    for(int i = 0; i < sz; i++) {
      if(sa[i] >= l && sa[i] <= r) {
        dp[sa[i] - (n + 1)] = max(ST.query(up[i] + 1, i), ST.query(i + 1, down[i]));
      }
    }

    SparseTable<int> mx(m + 1);
    mx.build(dp);
    while (q--) {
      int l, r;
      cin >> l >> r;
      --l, --r;
      int lo = 0, hi = (r - l + 1);
      int ans = 0;
      while(lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int x = mx.query(l, r - mid + 1);
        if(x >= mid) {
          ans = mid;
          lo = mid + 1;
        } else {
          hi = mid - 1;
        }
      }
      cout << ans << "\n";
    }
  }
  return 0;
}