#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e6 + 1;

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
} h;

// Custom Hash For Unordered Map Pair
struct custom_hash {
    const int RANDOM = (ll)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now()
                                                                    .time_since_epoch()
                                                                    .count();
    static unsigned ll hash_f(unsigned ll x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    static unsigned hash_combine(unsigned a, unsigned b) {
        return a * 31 + b;
    }
    int operator()(int x) const { return hash_f(x) ^ RANDOM; }
    int operator()(pair<int, int> x) const {
        return hash_combine(x.first, x.second) ^ RANDOM;
    }
};
/*
struct c_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        vector<string> d(n);
        unordered_map<pair<int, int>, int, custom_hash> id;

        int node = 1;
        for(int i = 0; i < n; i++) {
            string s;
            cin >> s;
            d[i] = s;
            h.BuildHash(s);
            for(int j = 1; j <= (int)s.length(); j++) {
                auto v = h.get_hash(1, j);
                if(!id[v])id[v] = node++;
            }
        }
        vector<vector<int>> adj(node+1);
        for(int i = 0; i < n; i++) {
            h.BuildHash(d[i]);
            for(int j = 2; j <= (int)d[i].length(); j++) {
                auto v = h.get_hash(1, j);
                auto u = h.get_hash(2, j);
                if(id[u]) {
                    adj[id[u]].push_back(id[v]);
                    adj[id[v]].push_back(id[u]);
                }
            }
        }
        vector<bool> vis(node, false);
        int ans = 0;
        vector<array<int, 2>> dp(node);
        function<void(int, int)> dfs = [&](int u, int p) {
            vis[u] = true;
            dp[u][0] = 0;
            dp[u][1] = 1;
            for (auto v : adj[u]) {
                if (v == p) continue;
                if (!vis[v]) {
                    dfs(v, u);
                    dp[u][0] += max(dp[v][0], dp[v][1]);
                    dp[u][1] += dp[v][0];
                }
            }
        };
        for (int i = 1; i < node; i++) {
            if (!vis[i]) {
                dfs(i, -1);
                ans += max(dp[i][0], dp[i][1]);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
// https://codeforces.com/problemset/submission/856/243156365
