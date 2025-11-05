// https://codeforces.com/contest/2000/problem/H
#include<bits/stdc++.h>
using namespace std;
const int N = 2000005;
int tree[N*4+5];
int n;

int merge(int x, int y) {
  return max(x, y);
}
void update(int i, int value, int node, int l, int r) {
  if(l == i && r == i) {
    tree[node] = value;
    return;
  }
  int mid = l + ((r-l) >> 1);
  if(i <= mid)update(i, value, (node << 1)+1, l, mid);
  else update(i, value, (node << 1)+2, mid+1, r);
  tree[node] = merge(tree[(node << 1)+1], tree[(node << 1)+2]);
}
void update(int i, int value) {
  update(i, value, 0, 0, N-1);
}
int query(int i, int j, int node, int l, int r) {
  if(l > j || r < i) return INT_MIN;
  if(l >= i && r <= j)return tree[node];
  int mid = l + ((r - l) >> 1);
  return merge(query(i, j, (node << 1)+1, l, mid), query(i, j, (node << 1)+2, mid+1, r));
}
int query(int i, int j) {
  return query(i, j, 0, 0, N-1);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  cin >> tt;
  while(tt--) {
    cin >> n;
    vector<int> v(n);
    set<int> st;
    for(int i = 0; i < n; i++) {
      cin >> v[i];
      st.insert(v[i]);
    }
    st.insert(0);
    v.push_back(0);
    sort(v.begin(), v.end());
    for(int i = 1; i < (int)v.size(); i++) {
      update(v[i-1]+1, v[i]-v[i-1]-1);
    }
    int q;
    cin >> q;
    while(q--) {
      char type;
      cin >> type;
      int x;
      cin >> x;
      if(type == '+') {
        auto it = st.upper_bound(x);
        if(it == st.end()) {
          it--;
          update(*it+1, x - *it-1);
        }else {
          auto next_it = it;
          it--;
          update(*it+1, x - *it - 1);
          update(x+1, (*next_it) - x - 1);
        }
        st.insert(x);
      }else if(type == '-') {
        auto it = st.lower_bound(x);
        auto pre_it = it;
        pre_it--;
        auto next_it = it;
        next_it++;
        update(*pre_it + 1, (*next_it - *pre_it-1));
        update(*it + 1, 0);
        st.erase(x);
      }else {
        int lo = 0, hi = N-1;
        int ans = -1;
        while(lo <= hi) {
          int mid  = lo + (hi - lo)/2;
          if(query(0, mid) >= x) {
            ans = mid;
            hi = mid - 1;
          }else lo = mid + 1;
        }
        if(ans == -1)cout << *st.rbegin() + 1 << " ";
        else cout << ans << " ";
      }
    }
    cout << "\n";
    for(auto x : st) {
      if(x < 2000000)update(x+1, 0);
    }
  }
  return 0;
}