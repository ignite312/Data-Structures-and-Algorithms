// https://atcoder.jp/contests/abc354/tasks/abc354_e
#include<bits/stdc++.h>
using namespace std;
const int N = 19;
int n;
int a[N], b[N], dp[1 << N];

int solve(int mask) {
    if (mask == 0)return 0;
    
    if (dp[mask] != -1)return dp[mask];

    dp[mask] = 0; 

    for (int i = 0; i < n; ++i) {
        if (!(mask & (1 << i))) continue;
        for (int j = i + 1; j < n; ++j) {
            if (!(mask & (1 << j))) continue; 
            if (a[i] == a[j] || b[i] == b[j]) {
                int new_mask = mask & ~(1 << i) & ~(1 << j);
                if (solve(new_mask) == 0) {
                    dp[mask] = 1; 
                    return dp[mask];
                }
            }
        }
    }

    return dp[mask];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    memset(dp, -1, sizeof(dp));
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> a[i] >> b[i];
        }
        int _mask = (1 << n) - 1;
        int ans = solve(_mask);

        if (ans == 1)cout << "Takahashi\n";
        else cout << "Aoki" << "\n";
    }
    return 0;
}