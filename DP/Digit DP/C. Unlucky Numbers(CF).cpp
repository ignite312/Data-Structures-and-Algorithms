#include<bits/stdc++.h>
using namespace std;
string a, b;
int dp[20][10][10][4];
string ans[10];

int f(int idx, int lo, int hi, string s, int tight, bool is_started) {
    if(a[idx] == '\0') {
        ans[hi-lo] = s;
        return hi - lo;
    }
    if(dp[idx][lo][hi][tight] != -1)return dp[idx][lo][hi][tight];

    char st, en;
    if(tight == 0) st = a[idx], en = b[idx];
    else if(tight == 1) st = a[idx], en = '9';
    else if(tight == 2) st = '0', en = b[idx];
    else st = '0', en = '9';
    int t_ans = 9, t_lo = lo;
    for(char i = st; i <= en; i++) {
        if(is_started || i != '0')is_started = true, t_lo = min(lo, i-'0');
        if(i == st) {
            if(tight == 0 && st != en) t_ans = min(t_ans, f(idx+1, t_lo, max(hi, i-'0'), s+i, 1, is_started));
            t_ans = min(t_ans, f(idx+1, t_lo, max(hi, i-'0'), s+i, tight, is_started));
        }else if(i == en) {
            if(tight == 0) t_ans = min(t_ans, f(idx+1, t_lo, max(hi, i-'0'), s+i, 2, is_started));
            t_ans = min(t_ans, f(idx+1, t_lo, max(hi, i-'0'), s+i, tight, is_started));
        }else t_ans = min(t_ans, f(idx+1, t_lo, max(hi, i-'0'), s+i, 3, is_started));
    }
    return dp[idx][lo][hi][tight] = t_ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        cin >> a >> b;
        if((int)a.size() != b.size()) {
            a = string((int)b.size() - (int)a.size(), '0') + a;
        }
        memset(dp, -1, sizeof(dp));
        string t = ans[f(0, 9, 0, "", 0, false)];
        while(t.front() == '0' && t.size())
            t.erase(t.begin());
        cout << t << "\n";
    }
    return 0;
}

// https://codeforces.com/contest/1808/submission/247666995