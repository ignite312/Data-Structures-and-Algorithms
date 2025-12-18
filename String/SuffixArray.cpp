// https://codeforces.com/edu/course/2/lesson/2/4/practice/contest/269119/problem/A
// Finding Patterns: https://cses.fi/problemset/task/2102/ 
// Counting Patterns: https://cses.fi/problemset/task/2103
// Pattern Lowest Positions: https://cses.fi/problemset/task/2104/
// Distinct Substrings: https://cses.fi/problemset/task/2105/
// kth smallest distinct substrings after lexicographical order: https://cses.fi/problemset/task/2108/
// kth smallest non distinct substrings after lexicographical order: https://cses.fi/problemset/task/2109/
// number of distinct substrings of every length 1 to n: https://cses.fi/problemset/task/2110/
// longest common prefix of suffix starting at i in string b with any suffix in string a: https://codeforces.com/gym/105973/problem/H
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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  // cin >> tt;
  while(tt--) {
    string s;
    cin >> s;
    s += "$";
    int n = s.size();
    SuffixArray SA(s);
    for(auto x : SA.sa) {
        cout << x << " ";
    }
    cout << "\n";
    for(int i = 1; i < n; i++) {
        cout << SA.lcp[i] << " ";
    }
  }
  return 0;
}