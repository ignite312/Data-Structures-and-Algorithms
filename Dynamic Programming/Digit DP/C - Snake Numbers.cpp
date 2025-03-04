// https://atcoder.jp/contests/abc387/tasks/abc387_c
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll dp[20][10][2];
 
ll f(int idx, int first_digit, int tight, string &number, int n) {
    if(idx == n)return 1;
    if(dp[idx][first_digit][tight] != -1)return dp[idx][first_digit][tight];
 
    int lb = 0;
    int up = (tight ? number[idx] - '0' : 9);
    ll ans = 0;
    for(int digit = lb; digit <= up; digit++) {
        if(first_digit != 0 && digit >= first_digit)continue;
        int z = first_digit;
        if(digit != 0 && first_digit == 0)z = digit;
        ans = ans + f(idx+1, z, tight & (digit == up), number, n);
    }
    return dp[idx][first_digit][tight] = ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    while(tt--) {
        string a, b;
        ll x;
        cin >> x;
        x--;
        a = to_string(x);
        cin >> b;
        int ln_a = (ll)a.length();
        int ln_b = (ll)b.length();
        memset(dp, -1, sizeof(dp));
        ll ans = f(0, 0, 1, b, ln_b);
        memset(dp, -1, sizeof(dp));
        cout << ans - f(0, 0, 1, a, ln_a) << "\n";
    }
    return 0;
}