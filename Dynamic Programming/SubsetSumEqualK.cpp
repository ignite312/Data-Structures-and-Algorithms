// https://codeforces.com/gym/105327/problem/K
#include<bits/stdc++.h>
using namespace std;

set<int> isSubsetSum(vector<int> &a, int n, int target) {
    set<int> indices;
    vector<vector<int>> dp(n+1, vector<int> (target+1, false));
    dp[0][0] = true;
    for (int i = 1; i <= n; i++) {
        for (int sum = 1; sum <= target; sum++) {
              dp[i][sum] = dp[i - 1][sum];
              if(sum >= a[i])dp[i][sum] |= dp[i - 1][sum - a[i]];
        }
    }
    if (!dp[n][target]) return {};
    int i = n, j = target;
    while (i > 0 && j > 0) {
        if (!dp[i - 1][j]) {
            indices.insert(i);
            j -= a[i];
        }
        i--;
    }
    return indices;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        vector<int> v(n + 1);
        int target = 0;
        for (int i = 1; i <= n; i++) {
            cin >> v[i];
            target += v[i];
        }
        if(target % 2 != 0) {
          cout << "-1" << "\n";
          return 0;
        }
        target /= 2;
        set<int> indices = isSubsetSum(v, n, target);
        if (indices.empty()) {
          cout << "-1" << "\n";
          return 0;
        }
        vector<int> alice, bob;
        for(int i = 1; i <= n; i++) {
          auto it = indices.find(i);
          if(it == indices.end()) {
            bob.push_back(v[i]);
          }else alice.push_back(v[i]);
        }
        int sum1 = 0, sum2 = 0;
        while(alice.size() || bob.size()) {
            if(sum1 <= sum2) {
                sum1+=alice.front();
                cout << alice.front() << " ";
                alice.erase(alice.begin());
            }
            else {
                sum2+=bob.front();
                cout << bob.front() << " ";
                bob.erase(bob.begin());
            }
        }
        cout << "\n";
    }
    return 0;
}