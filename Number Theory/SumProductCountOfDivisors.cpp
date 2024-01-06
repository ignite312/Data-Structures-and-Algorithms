#include<bits/stdc++.h>
using namespace std;
const int M = 1e9 + 7;
#define ll long long

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
int geometricSeriesSum(int r, int n) {
    int nu = bigPow(r, n, M) - 1;
    int de = r - 1;
    de = bigPow(de, M-2, M);
    return nu*1LL*de % M;
}
/*
int arithmeticSeriesSum(int n) {
    return (n*1LL*(n+1) % M)*bigPow(2, M-2, M) % M;
}
*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        ll cnt = 1, sum = 1, prod = 1, num1 = 1, num2 = 1, pw = 1;
        bool ok = true;
        for(int i = 0; i < n; i++) {
            int x, k;
            cin >> x >> k;
            cnt = cnt * (k + 1) % M;
            sum = sum * geometricSeriesSum(x, k+1) % M;
            num1 = num1 * bigPow(x, k, M) % M;
            num2 = num2 * bigPow(x, k/2, M) % M;
            if(k % 2 != 0 && ok) {
                pw = (pw * (k+1)/2) % (M-1);
                ok = false;
            }else {
                pw = (pw * (k+1)) % (M-1);
            }
        }
        if(!ok)prod = bigPow(num1, pw, M);
        else prod = bigPow(num2, pw, M);
        cout << cnt << " " << sum << " " << prod << "\n";
    }
    return 0;
}
// https://cses.fi/problemset/task/2182/
