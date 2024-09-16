// Pigeonhole Principle
#include<bits/stdc++.h>
using namespace std;

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
        set<int> not_used;
        for(int i = 0; i < n; i++) {
          not_used.insert(i);
        }
        vector<pair<int, int>> ans;
        for(int i = n-1; i >= 1; i--) {
          vector<int> mod(i, -1);
          for(auto id : not_used) {
            if(mod[v[id] % i] != -1) {
              ans.push_back({id+1, mod[v[id] % i]+1});
              not_used.erase(not_used.find(id));
              break;
            }
            mod[v[id] % i] = id;
          }
        }
        reverse(ans.begin(), ans.end());
        cout << "Yes\n";
        for(auto [x, y] : ans) {cout << x << " " << y << "\n";}
    }
    return 0;
}