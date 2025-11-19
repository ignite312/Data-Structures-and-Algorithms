#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mod = 998244353;
const int N = 5e5 + 1;
int fact[N];

void calculate() {
    fact[0] = fact[1] = 1;
    for(int i  = 2; i < N; i++) {
        fact[i] = fact[i-1]*1LL*i % mod;
    }
}
// O(log(power))
int bigPow(ll base, ll power, const int mod) {
    int ans = 1 % mod;
    base %= mod;
    if (base < 0) base += mod;
    while (power) {
        if (power & 1) ans = (ll) ans * base % mod;
        base = (ll) base * base % mod;
        power >>= 1;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    calculate();
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        vector<int> cnt(26);
        int n = 0;
        for(int i = 0; i < 26; i++) {
            cin >> cnt[i];
            n+=cnt[i];
        }
        int odd = (n+1)/2, even = n/2;
        vector<ll> dp(odd+1);
        dp[0] = 1; // Number of ways to select total char equal i

        for(int i = 0; i < 26; i++) {
            if(cnt[i] == 0)continue;

            for(int j = odd; j >= 0; j--) {
                if(j + cnt[i] <= odd) {
                    dp[j+cnt[i]] = (dp[j] + dp[j+cnt[i]]) % mod;
                }
            }
        }

        ll ans = (((dp[odd]*fact[odd]) % mod)*fact[even]) % mod;
        for(int i = 0; i < 26; i++) {
            ans = (ans *1LL* bigPow(fact[cnt[i]], mod-2, mod)) % mod;
        }
        cout << ans << "\n";
    }
    return 0;
}