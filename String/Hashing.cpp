// https://codeforces.com/contest/1951/problem/E

#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000000;

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
    pair<int, int> hashes[N+1];
    void BuildHash(string &s) {
        n = (int)s.length();
        hashes[0] = {0, 0};
        for(int i = 0; i < n; i++) {
            pair<int, int> t_hash;
            t_hash.first = (hashes[i].first + 1LL*p_ip1[i].first * s[i] % M1) % M1;
            t_hash.second = (hashes[i].second + 1LL*p_ip2[i].first * s[i] % M2) % M2;
            hashes[i+1] = {t_hash.first, t_hash.second};
        }
    }
    pair<int, int> get_hash(int l, int r) {
        pair<int, int> ans;
        ans.first = 1LL*(hashes[r].first - hashes[l-1].first + M1) * p_ip1[l-1].second % M1;
        ans.second = 1LL*(hashes[r].second - hashes[l-1].second + M2) * p_ip2[l-1].second % M2;
        return ans;
    }
    pair<int, int> get_hash() {return get_hash(1, n);}
}h, rh;

// 1-base indexing
bool isPalindrome(int i, int j, int n) {
    return h.get_hash(i, j) == rh.get_hash(n - j + 1, n - (i - 1));
}

void solve() {
    string s, rs, _s;
    cin >> s;

    int n = s.size();
    rs = s;
    _s = s;
    sort(_s.begin(), _s.end());
    reverse(rs.begin(), rs.end());
    h.BuildHash(s), rh.BuildHash(rs);

    if(_s.front() == _s.back())cout << "NO\n";
    else if(!isPalindrome(1, n, n))cout << "YES\n1\n" << s.substr(0, n) << "\n";
    else {
        for(int i = 0; i < n; i++) {
            if(!isPalindrome(1, i+1, n) && !isPalindrome(i+1+1, n, n)) {
                cout << "YES\n2\n" << s.substr(0, i+1) << " " << s.substr(i+1, n-(i+1)) << "\n";
                return;
            }
        }
        cout << "NO\n";
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        solve();
    }
    return 0;
}