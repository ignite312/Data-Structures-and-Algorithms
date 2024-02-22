#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int M = 1e9 + 7;
const int N = 2000+1;
ll dp[N+1][N+1][2];
int m, d, n;
string a, b, s;


ll f(int idx = 0, ll rem = 0, int small = 0) {
    if(idx == n) return (rem == 0);
    if(dp[idx][rem][small] != -1)return dp[idx][rem][small];

    ll x = 0;
    if(idx & 1) {
        if(small) x+=f(idx+1, (rem*10 + d) % m, 1);
        else {
            if(d < s[idx] - '0')x+=f(idx+1, (rem*10 + d) % m, 1);
            else if(d == s[idx] - '0')x+=f(idx+1, (rem*10 + d) % m, 0);
        }
    }else {
        if(small) {
            for(int i = 0; i <= 9; i++)
                if(i != d)x = (x + f(idx+1, (rem*10 + i) % m, 1)) % M;
        }else {
            for(int i = 0; i < s[idx] - '0'; i++) {
                if(idx == 0 && i == 0)continue;
                if(i != d)x = (x + f(idx+1, (rem*10 + i) % m, 1)) % M;
            }
            if(s[idx] - '0' != d && !(s[idx] - '0' == 0 && idx == 0)) x = (x + f(idx+1, (rem*10 + s[idx]-'0') % m, 0)) % M;
        }
    }
    x = x % M;
    return dp[idx][rem][small] = x;
}

ll init(string &c) {
    memset(dp, -1, sizeof(dp));
    s = c;
    return f();
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        ll ans = 0;
        cin >> m >> d;
        cin >> a >> b;
        n = (int)b.size();
        ans += init(b);
        ans -= init(a);
        ans = (ans + M) % M;
        bool ok = true;
        ll rem = 0;
        for(int i = 0; i < n; i++) {
            if((i&1) && a[i]-'0' != d || 
                (i&1)^1 && a[i]-'0' == d)ok = false;
            rem = (rem*10 + a[i]-'0') % m;
        }
        if(rem)ok = false;
        if(ok) ans = (ans + 1) % M;
        cout << ans << "\n";
    }
    return 0;
}

// https://codeforces.com/contest/628/submission/244917995