// https://codeforces.com/gym/105811/problem/D

#include<bits/stdc++.h>
using namespace std;
#define ll long long
vector<pair<ll, ll>> v;
ll dp[200005];
ll n, d;

ll solve(int idx) {
    if(idx >= n) return 0;

    if(dp[idx] != -1)return dp[idx];

    ll ans = solve(idx+1);
    int next_idx = lower_bound(v.begin(), v.end(), make_pair(v[idx].first + d, 0LL)) - v.begin();
    ans = max(ans, solve(next_idx) + v[idx].second);
    return dp[idx] = ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    while(tt--) {
        cin >> n >> d;
        for (int i = 0; i < n; i++) {
            ll x;
            ll p;
            cin >> x >> p;
            v.push_back(make_pair(x, p));
        }
        sort(v.begin(), v.end());

        /*
        vector<ll> dp(n, 0);
        dp[0] = v[0].second;

        for (int i = 1; i < n; i++) {
            dp[i] = dp[i - 1];
 
            int ind = lower_bound(v.begin(), v.end(), make_pair(v[i].first - d + 1, 0LL)) - v.begin() - 1;
            if (ind >= 0) {
                dp[i] = max(dp[i], dp[ind] + v[i].second);
            } else {
                dp[i] = max(dp[i], v[i].second);
            }
        }
        cout << dp[n - 1] << '\n';
        */
        memset(dp, -1, sizeof(dp));
        cout << solve(0);
    }
    return 0;
}