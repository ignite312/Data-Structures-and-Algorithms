#include<bits/stdc++.h>
using namespace std;
#define ll long long


struct RMQ {
    // 0-base indexing
  int n, logN;
  vector<vector<int>> st;
  vector<int> lg;
 
  void init(const vector<int>& array) {
    n = array.size();
    logN = ceil(log2(n));
    st.resize(logN, vector<int>(n));
    lg.resize(n + 1);
 
    lg[1] = 0;
    for (int i = 2; i <= n; i++)
      lg[i] = lg[i / 2] + 1;
 
    copy(array.begin(), array.end(), st[0].begin());
 
    for (int i = 1; i < logN; i++) {
      for (int j = 0; j + (1 << i) <= n; j++) {
        st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  int query(int L, int R) {
    int i = lg[R - L + 1];
    return min(st[i][L], st[i][R - (1 << i) + 1]);
  }
} ST;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        vector<int> v(n);
        for(int i = 0; i < n; i++) {
            cin >> v[i];
        }
        ST.init(v);
        cout << ST.query(0, 3) << "\n";
    }
    return 0;
}