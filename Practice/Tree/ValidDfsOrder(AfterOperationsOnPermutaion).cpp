/*
https://codeforces.com/contest/2002/problem/D2
Checking a permutation is valid dfs order or not
*/
#include<bits/stdc++.h>
using namespace std;

const int N = 300001;
int parent[N], p[N], idx[N], siz[N];
set<int> idx_child[N];

int check(int u) {
  if(idx_child[u].empty()) return 1;

  int left = *idx_child[u].begin();
  int right = *--idx_child[u].end();
  return idx[u] < left && (right + siz[p[right]] <= idx[u] + siz[u]);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        int n, q;
        cin >> n >> q;
        for(int i = 1; i <= n; i++) {
          idx_child[i].clear();
          siz[i] = 1;
        }
        for(int v = 2; v <= n; v++) {
          cin >> parent[v];
        }
        for(int i = n; i >= 1; i--) {
          siz[parent[i]] += siz[i];
        }
        for(int i = 1; i <= n; i++) {
          cin >> p[i];
          idx[p[i]] = i;
          idx_child[parent[p[i]]].insert(i);
        }
        int valid = 0;
        for(int i = 1; i <= n; i++) {
          valid+=check(i);
        }
        while(q--) {
          int i, j;
          cin >> i >> j;
          int a = p[i], b = p[j];
          set<int> st = {a, b, parent[a], parent[b]};
          for(auto x : st) {
            valid-=check(x);
          }
          idx_child[parent[a]].erase(i), idx_child[parent[b]].erase(j);
          swap(p[i], p[j]), swap(idx[a], idx[b]);
          idx_child[parent[a]].insert(j), idx_child[parent[b]].insert(i);
          for(auto x : st) {
            valid+=check(x);
          }
          cout << (valid == n ? "YES\n" : "NO\n");
        }
    }
    return 0;
}