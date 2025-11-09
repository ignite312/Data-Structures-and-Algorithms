/*
Problem Name: String Matching
Problem Link: https://cses.fi/problemset/task/1753/
Practice Problem: https://cses.fi/problemset/task/2107/
Practice Problem: https://codeforces.com/contest/126/problem/B
*/
#include<bits/stdc++.h>
using namespace std;

// pi[i] = the length of the longest proper prefix of the substring
// s[0 ... i] which is also a suffix of this substring, TC: O(n)
vector<int> prefix_function(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i-1];
    while (j > 0 && s[i] != s[j])
      j = pi[j-1];
    if (s[i] == s[j])
      j++;
    pi[i] = j;
  }
  return pi;
}
// z[i] = length of the longest substring starting at position i that matches the prefix of s.
// z[0] = 0, TC: O(n)
vector<int> z_function(string s) {
  int n = s.size();
  vector<int> z(n);
  int l = 0, r = 0;
  for(int i = 1; i < n; i++) {
    if(i < r) {
      z[i] = min(r - i, z[i - l]);
    }
    while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    if(i + z[i] > r) {
      l = i;
      r = i + z[i];
    }
  }
  return z;
}
vector<int> count_occ_pfx(vector<int> &pi) {
  int n = pi.size();
  vector<int> ans(n + 1); // ans[i] = count total i length prefix 
  for (int i = 0; i < n; i++)
    ans[pi[i]]++;
  for (int i = n-1; i > 0; i--)
    ans[pi[i-1]] += ans[i];
  for (int i = 0; i <= n; i++)
    ans[i]++;
  return ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  // cin >> tt;
  while(tt--) {
    string s;
    cin >> s;
    string t;
    cin >> t;
    string z = t + "#" + s;
    int n = s.size(), m = t.size();
    auto pi = z_function(z);
    int ans = 0;
    for(int i = m+1; i < z.size(); i++) {
      if(pi[i] == m) {
        ans++;
      }
    }
    cout << ans << "\n";
  }
  return 0;
}