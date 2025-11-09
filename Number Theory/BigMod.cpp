// https://cses.fi/problemset/task/1079/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000001;
const int mod = 1e9 + 7;
ll fact[N];
 
// O(log(p))
int bigPow(ll b, ll p, const int mod) {
    int ans = 1 % mod;
    b %= mod;
    if(b < 0) b += mod;
    while(p) {
        if(p & 1) ans = (ll) ans * b % mod;
        b = (ll) b * b % mod;
        p >>= 1;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    fact[0] = fact[1] = 1;
    for(int i = 2; i < N; i++) {
        fact[i] = (fact[i-1]*i) % mod;
    }
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        int n, r;
        cin >> n >> r;
        ll denominator = fact[r]*fact[n-r] % mod;
        denominator = bigPow(denominator, mod-2, mod);
        cout << fact[n] * denominator % mod << "\n";
    }
    return 0;
}