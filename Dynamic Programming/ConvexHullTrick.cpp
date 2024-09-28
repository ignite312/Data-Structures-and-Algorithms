/*
Problem Name: Z - Frog 3
Problem Link: https://atcoder.jp/contests/dp/tasks/dp_z
Idea: Convex Hull Trick
Complexity:
Resource: https://codeforces.com/blog/entry/63823
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 1;
#define ll long long
ll dp[N];
/*
dp[i] = min(dp[i], dp[j] + (hi - hj)^2 + c) for all j < i
Expanding the expression:
dp[j] + (hi - hj)^2 + c
= [c + hi^2] - 2hj * hi + dp[j] + hj^2

Here:
[c + hi^2] is constant with respect to j.
We define:
  m = -2hj  (slope),
  x = hi    (the current value we're querying),
  c = dp[j] + hj^2  (the intercept),
So we are minimizing an expression of the form:
y = mx + c
*/
struct Line {
    // m = slope, c = intercept
    ll m, c;
    Line(ll a, ll b) : m(a), c(b) {}
};
struct CHT {
    // SayeefMahmud
    vector<Line> lines;

    bool bad(Line l1, Line l2, Line l3) {
        __int128 a = (__int128)(l2.c - l1.c) * (l2.m - l3.m);
        __int128 b = (__int128)(l3.c - l2.c) * (l1.m - l2.m);
        return a >= b;
    }
    void add(Line line) {
        lines.push_back(line);
        int sz = lines.size();
        while (sz >= 3 && bad(lines[sz - 3], lines[sz - 2], lines[sz - 1])) {
            lines.erase(lines.end() - 2);
            sz--;
        }
    }
    ll query(ll x) {
        int l = 0, r = lines.size() - 1;
        ll ans = LLONG_MAX;
        while (l <= r) {
            int mid1 = l + (r - l) / 3;
            int mid2 = r - (r - l) / 3;
            ans = min(ans, min(lines[mid1].m * x + lines[mid1].c, lines[mid2].m * x + lines[mid2].c));
            if (lines[mid1].m * x + lines[mid1].c <= lines[mid2].m * x + lines[mid2].c) {
                r = mid2 - 1;
            } else {
                l = mid1 + 1;
            }
        }
        return ans;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        int n;
        ll c;
        cin >> n >> c;
        ll h1;
        cin >> h1;
        dp[1] = 0;
        CHT ch;
        ch.add(Line(-2*h1, dp[1] + h1*h1)) ;
        for(int i = 2; i <= n; i++) {
            ll hi;
            cin >> hi;
            dp[i] = c + hi*hi + ch.query(hi);
            ch.add(Line(-2*hi, dp[i] + hi*hi));
        }
        cout << dp[n] << "\n";
    }
    return 0;
}
