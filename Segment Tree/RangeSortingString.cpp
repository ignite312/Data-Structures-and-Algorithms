#include<bits/stdc++.h>
using namespace std;
const int N = (1e5)*4;
int tree[N+5][26], lazy[N+5][26];
string s;

void print(int node, int l, int r, int ch) {
    if(lazy[node][ch] != -1) {
        tree[node][ch] = lazy[node][ch]*(r-l+1);
        if(l != r) {
            lazy[node*2+1][ch] = lazy[node][ch];
            lazy[node*2+2][ch] = lazy[node][ch];
        }
        lazy[node][ch] = -1;
    }
    if(l == r) {
        if(tree[node][ch] == 1) {
            s[l] = ch + 'a';
        }
        return;
    }
    int mid = l + (r - l)/2;
    print(node*2+1, l, mid, ch);
    print(node*2+2, mid+1, r, ch);
}
void build(int node, int l, int r, int ch) {
  lazy[node][ch] = -1;
  if(l == r) {
    tree[node][ch] = (ch == (s[l] - 'a'));
    return;
  }
  int mid = l + (r - l)/2;
  build(node*2+1, l, mid, ch);
  build(node*2+2, mid + 1, r, ch);
  tree[node][ch] = tree[node*2+1][ch] + tree[node*2+2][ch]; 
}
void update(int node, int l, int r, int i, int j, int ch, int value) {
    if(lazy[node][ch] != -1) {
        tree[node][ch] = lazy[node][ch]*(r-l+1);
        if(l != r) {
            lazy[node*2+1][ch] = lazy[node][ch];
            lazy[node*2+2][ch] = lazy[node][ch];
        }
        lazy[node][ch] = -1;
    }
    if(r < i || l > j)return;
    if(l >= i && r <= j) {
        tree[node][ch] = value*(r-l+1);
        if(l != r) {
            lazy[node*2+1][ch] = value;
            lazy[node*2+2][ch] = value;
        }
        return;
    }
    int mid = l + (r-l)/2;
    update(node*2+1, l, mid, i, j, ch, value);
    update(node*2+2, mid+1, r, i, j, ch, value);
    tree[node][ch] = tree[node*2+1][ch] + tree[node*2+2][ch];
}
int query(int node, int l, int r, int i, int j, int ch) {
    if(lazy[node][ch] != -1) {
        tree[node][ch] = lazy[node][ch]*(r-l+1);
        if(l != r) {
            lazy[node*2+1][ch] = lazy[node][ch];
            lazy[node*2+2][ch] = lazy[node][ch];
        }
        lazy[node][ch] = -1;
    }
    if(r < i || l > j) return 0;
    if(l >= i && r <= j) return tree[node][ch];
    int mid = l + (r-l)/2;
    return query(node*2+1, l, mid, i, j, ch) + query(node*2+2, mid+1, r, i, j, ch);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  while(tt--) {
    int n, q;
    cin >> n >> q;
    cin >> s;
    for(int i = 0; i < 26; i++) {
        build(0, 0, n-1, i);
    }
    while(q--) {
      int l, r, type;
      cin >> l >> r >> type;
      l--, r--;
      vector<int> cnt(26, 0);
      for(int i = 0; i < 26; i++) {
        cnt[i] = query(0, 0, n-1, l, r, i);
        update(0, 0, n-1, l, r, i, 0);
      }
      if(type == 1) {
        for(int i = 0; i < 26; i++) {
            int r = l + cnt[i] - 1;
            update(0, 0, n-1, l, r, i, 1);
            l = r + 1;
        }
      }else {
        for(int i = 25; i >= 0; i--) {
            int r = l + cnt[i] - 1;
            update(0, 0, n-1, l, r, i, 1);
            l = r + 1;
        }
      }
    }
    for(int i = 0; i < 26; i++) print(0, 0, n-1, i);
    cout << s << '\n';
  }
  return 0;
}
// https://codeforces.com/contest/558/submission/201116864
