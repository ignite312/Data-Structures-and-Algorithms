// https://codeforces.com/problemset/problem/1525/D

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt = 1;
    // cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        vector<int> v(n), b;
        
        for (int i = 0; i < n; i++) {
            cin >> v[i];
            if (v[i] == 1) {
                b.push_back(i);
            }
        }        
        int k = b.size();
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INT_MAX));
        dp[0][0] = 0;
        // dp[i][j] = total j chair occupied using first i chair
        for (int i = 1; i <= n; i++) {
            vector<int> tmp = dp[i-1];
            for (int j = 1; j <= k; j++) {  
                if (v[i-1] == 0 && dp[i-1][j-1] != INT_MAX) {
                    tmp[j] = min(tmp[j], dp[i-1][j-1] + abs((i-1) - b[j-1]));
                }
            }
            dp[i] = tmp;
        }
        
        cout << dp[n][k] << "\n";
    }
    return 0;
}
