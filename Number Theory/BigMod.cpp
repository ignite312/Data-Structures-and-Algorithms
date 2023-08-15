#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M = 1000003;
const int N = 1e6+5;
vector<ll> fact(N+5);

int bigMod(ll base, ll power, const int M) {
    if(power == 0)return 1;
    int p = bigMod(base, power/2, M) % M;
    if(power % 2 == 0)return p*1LL*p % M;
    return (p*1LL*p % M) * (base % M) % M;
}
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
    fact[0] = 1;
    for (int i = 1; i <= N; ++i) {
        fact[i] = (ll)fact[i-1]*i % M;
    }
    int tt, cs = 1;
    cin >> tt;
    while(tt--) {
        int n, r;
        cin >> n >> r;
        int z = (ll)fact[r]*fact[n-r] % M;
        cout << "Case " << cs++ << ": ";
        cout << (ll)fact[n] * bigMod(z, M-2, M) % M << "\n";
    }
}
// https://lightoj.com/problem/combinations
