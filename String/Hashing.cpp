#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5e6 + 1;

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
/* 
1000000009 31 For Lower Case
1000000009 53 For Upper n Lower Case
*/
const int M1 = 127657753, M2 = 987654319;
const int p1 = 137, p2 = 277;
int ip1, ip2;
pair<int, int> p_ip1[N+1], p_ip2[N+1];
void init() {
    p_ip1[0] = p_ip2[0] = {1, 1};
    for(int i = 1; i < N; i++) {
        p_ip1[i].first = 1LL*p_ip1[i-1].first * p1 % M1;
        p_ip2[i].first = 1LL*p_ip2[i-1].first * p2 % M2;
    }
    ip1 = bigPow(p1, M1-2, M1);
    ip2 = bigPow(p2, M2-2, M2);
    for(int i = 1; i < N; i++) {
        p_ip1[i].second = 1LL*p_ip1[i-1].second * ip1 % M1;
        p_ip2[i].second = 1LL*p_ip2[i-1].second * ip2 % M2;
    }
}
struct Hashing {
    int n;
    pair<int, int> hashs[N+1];
    void BuildHash(string &s) {
        n = (int)s.length();
        hashs[0] = {0, 0};
        for(int i = 0; i < n; i++) {
            pair<int, int> t_hash;
            t_hash.first = (hashs[i].first + 1LL*p_ip1[i].first * s[i] % M1) % M1;
            t_hash.second = (hashs[i].second + 1LL*p_ip2[i].first * s[i] % M2) % M2;
            hashs[i+1] = {t_hash.first, t_hash.second};
        }
    }
    pair<int, int> get_hash(int l, int r) {
        pair<int, int> ans;
        ans.first = 1LL*(hashs[r].first - hashs[l-1].first + M1) * p_ip1[l-1].second % M1;
        ans.second = 1LL*(hashs[r].second - hashs[l-1].second + M2) * p_ip2[l-1].second % M2;
        return ans;
    }
    pair<int, int> get_hash() {return get_hash(1, n);}
}h, r_h;
bool isPalindrom(int i, int j, int n) {
    return h.get_hash(i, j) == r_h.get_hash(n - j + 1, n - (i - 1));
}

int n;
vector<int> dp(N+1, -1);
int find(int r) {
    if(r < 1)return 0;
    if(dp[r] != -1)return dp[r];
    if(!isPalindrom(1, r, n))return 0;
    return dp[r] = find(r/2) + 1;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    int tt;
    tt = 1;
    while(tt--) {
        string s, r_s;
        cin >> s;
        n = s.length();
        r_s = s;
        reverse(r_s.begin(), r_s.end());
        h.BuildHash(s), r_h.BuildHash(r_s);
        int ans = 0;
        dp[1] = 1;
        for(int i = 1; i <= n; i++)ans+=find(i);
        cout << ans << "\n";
    }
    return 0;
}
// https://codeforces.com/contest/7/submission/219550474
