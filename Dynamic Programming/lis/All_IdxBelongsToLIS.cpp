// https://atcoder.jp/contests/abc354/tasks/abc354_f

#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int INF = 1e9+10;
int n, mx;

// Complexity: O(nlog(n))
vector<int> lis(int n, vector<int> &a) {
    vector<int> d(n+1, INF), max_end(n);
    d[0] = -INF;
    for(int i = 0; i < n; i++) {
        int idx = lower_bound(d.begin(), d.end(), a[i]) - d.begin();
        d[idx] = a[i];
        max_end[i] = idx;
    }
    for(int i = 1; i <= n; i++)if(d[i] < INF)mx = i;
    return max_end;
}

vector<int> lds(int n, vector<int> &a) {
    for(int i = 0; i < n; i++)a[i]*=-1;
    vector<int> d(n+1, INF), max_end(n);
    d[0] = -INF;
    for(int i = n-1; i >= 0; i--) {
        int idx = lower_bound(d.begin(), d.end(), a[i]) - d.begin();
        d[idx] = a[i];
        max_end[i] = idx;
    }
    return max_end;
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
        for(int i = 0; i < n; i++) {
            cin >> v[i];
        }
        vector<int> _lis = lis(n, v);
        vector<int> _lds = lds(n, v);
        vector<int> ans;
        for(int i = 0; i < n; i++) {
          if(_lds[i] + _lis[i] - 1 == mx) {
            ans.push_back(i+1);
          }
        }
        cout << ans.size() << "\n";
        for(int i = 0; i < (int)ans.size();  i++) {
          cout << ans[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}