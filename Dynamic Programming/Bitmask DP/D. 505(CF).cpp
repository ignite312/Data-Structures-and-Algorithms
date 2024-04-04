/*
https://codeforces.com/contest/1391/problem/D
*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e6+1;
int a[N+1], n, m, dp[N+1][(1 << 3) + 1];

int f(int i, int mask) {
    if(i == m-1) {
        return dp[i][mask] = __builtin_popcount(a[i] ^ mask);
    }
    if(dp[i][mask] != -1) return dp[i][mask];

    int cost = INT_MAX;
    for(int next_mask = 0; next_mask < (1 << n); next_mask++) {
        bool ok = true;
        int x;
        if(1 < n) {
            x = ((mask & (1 << 0)) != 0) + ((mask & (1 << 1)) != 0) + ((next_mask & (1 << 0)) != 0) + ((next_mask & (1 << 1)) != 0);
            ok &= (x % 2);
        }
        if(2 < n) {
            x = ((mask & (1 << 1)) != 0) + ((mask & (1 << 2)) != 0) + ((next_mask & (1 << 1)) != 0) + ((next_mask & (1 << 2)) != 0);
            ok &= (x % 2);
        }
        if(ok) cost = min(cost, f(i+1, next_mask));
    }
    if(cost != INT_MAX)cost += __builtin_popcount(a[i] ^ mask);
    return dp[i][mask] = cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        cin >> n >> m;
        vector<string> s(n);
        for(int i = 0; i < n; i++) {
            cin >> s[i];
        }
        if(n > 3 && m > 3) {
            cout << "-1" << "\n";
            return 0;
        }
        if(n > m) {
            for(int i = 0; i < n; i++) {
                int x = 0;
                for(int j = 0; j < m; j++) {
                    if(s[i][j] == '1') x+=(1 << j);
                }
                a[i] = x;
            }
            swap(n, m);
        }else {
            for(int j = 0; j < m; j++) {
                int x = 0;
                for(int i = 0; i < n; i++) {
                    if(s[i][j] == '1') x+=(1 << i);
                }
                a[j] = x;

            }
        }
        int ans = INT_MAX;
        memset(dp, -1, sizeof(dp));
        for(int i = 0; i < (1 << n); i++) {
            ans = min(ans, f(0, i));
        }
        cout << ans << "\n";
    }
    return 0;
}

// https://codeforces.com/contest/1391/submission/244596368