#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;

int bigMod(int base, ll power, const int M) {
    if(power == 0)return 1;
    int p = bigMod(base, power/2, M) % M;
    if(power % 2 == 0)return p*1LL*p % M;
    return (p*1LL*p % M) * (base % M) % M;
}
// 127657753 137
const int M1 = 1000000009, M2 = 987654319;
const int p1 = 31, p2 = 277;
int ip1, ip2;
vector<pair<int, int>> p_ip1(N+5), p_ip2(N+5);
void init() {
    p_ip1[0] = p_ip2[0] = {1, 1};
    for(int i = 1; i < N; i++) {
        p_ip1[i].first = p_ip1[i-1].first *1LL* p1 % M1;
        p_ip2[i].first = p_ip2[i-1].first *1LL* p2 % M2;
    }
    ip1 = bigMod(p1, M1-2, M1);
    ip2 = bigMod(p2, M2-2, M2);
    for(int i = 1; i < N; i++) {
        p_ip1[i].second = p_ip1[i-1].second *1LL* ip1 % M1;
        p_ip2[i].second = p_ip2[i-1].second *1LL* ip2 % M2;
    }
}
struct Hashing {
    int n;
    string s;
    vector<pair<int, int>> hsh;
    Hashing(string ss) {
        s = ss;
        n = (int)s.length();
        hsh.emplace_back(0, 0);
        for(int i = 0; i < n; i++) {
            pair<int, int> t_hsh;
            t_hsh.first = (hsh[i].first + p_ip1[i].first*1LL*(s[i]-'a') % M1) % M1;
            t_hsh.second = (hsh[i].second + p_ip2[i].first*1LL*s[i] % M2) % M2;
            hsh.emplace_back(t_hsh);
        }
    }
    pair<int, int> get_hsh(int l, int r) {
        pair<int, int> ans;
        ans.first = (hsh[r].first - hsh[l-1].first + M1)*1LL*p_ip1[l-1].second % M1;
        ans.second = (hsh[r].second - hsh[l-1].second + M2)*1LL*p_ip2[l-1].second % M2;
        return ans;
    }
    pair<int, int> get_hsh() {return get_hsh(1, n);}
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    int n;
    while(cin >> n) {
        string t, b;
        cin >> t >> b;
        Hashing h(b);
        auto hsh = Hashing(t).get_hsh();
        for(int i = 1; i <= (int)b.length() - n + 1; i++) {
            if(h.get_hsh(i, i+n-1) == hsh) {
                cout << i-1 << "\n";
            }
        }cout << "\n";
    }
}
// https://www.spoj.com/problems/NHAY/
