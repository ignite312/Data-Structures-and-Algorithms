// https://codeforces.com/gym/105657/problem/F
#include<bits/stdc++.h>
using namespace std;
#define ll long long

struct SCC {
    // 1-base indexing
    // 1 2 // 2 1 // 1 3 // 2 4 -> why radj
    int n;
    int c_id; // unique id starting from 1
    vector<vector<int>> adj, radj;
    vector<int> todo, id;
    vector<bool> vis;
    SCC(int _n) : n(_n) {
        c_id = 0;
        adj.resize(n+1), radj.resize(n+1), id.assign(n+1, -1), vis.resize(n+1);
    }
    void build(int x, int y) { adj[x].push_back(y), radj[y].push_back(x); }
    void dfs(int x) {
        vis[x] = true;
        for(auto y : adj[x]) if (!vis[y]) dfs(y);
        todo.push_back(x);
    }
    void dfs2(int u, int c_id) {
        id[u] = c_id;
        for(auto v : radj[u]) if(id[v] == -1) dfs2(v, c_id);
    }
    void gen() {
        for(int i = 1; i <= n; i++) if (!vis[i]) dfs(i);
        reverse(todo.begin(), todo.end());
        for(auto x : todo) if(id[x] == -1) {
            ++c_id;
            dfs2(x, c_id);
        }
    }
};
ll f(ll a, ll b) {
    if(a > b) return 0;
    ll ln = (b - a + 1);
    return (ln * (ln - 1)) / 2;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        int n, k, q;
        cin >> n >> k >> q;
        vector<int> v(n);
        vector<vector<int>> rank_list(k, vector<int>(n));
        SCC scc(n);
        for(int i = 0; i < k; i++) {
            for(int j = 0; j < n; j++) {
                cin >> rank_list[i][j];
                if(j > 0) {
                    scc.build(rank_list[i][j-1], rank_list[i][j]);
                }
            }
        }
        scc.gen();
        for(int i = 0; i < k; i++) {
            for(int j = 0; j < n; j++) {
                rank_list[i][j] = scc.id[rank_list[i][j]];
            }
        }
        vector<pair<int, int>> seg[k];
        vector<vector<ll>> pfx(k, vector<ll>(n+1, 0));
        for(int i = 0; i < k; i++) {
            ll sum_now = 0;
            ll l = 0;
            for(int j = 1; j < n; j++) {
                if(rank_list[i][j-1] != rank_list[i][j]) {
                    ll r = j - 1;
                    seg[i].push_back({l, r});
                    ll seg_sz = (r - l + 1);
                    sum_now += (seg_sz * (seg_sz - 1)) / 2;
                    l = j;
                }
                pfx[i][j-1] = sum_now;
                if(j == n - 1) {
                    ll r = n - 1;
                    seg[i].push_back({l, r});
                    sum_now += (r - l + 1) * (r - l) / 2;
                    pfx[i][j] = sum_now;
                }
            }
        }
        vector<vector<int>> next(k, vector<int>(n, -1)), prev(k, vector<int>(n, -1));
        for(int i = 0; i < k; i++) {
            for(auto &[l, r] : seg[i]) {
                for(int j = l; j <= r; j++) {
                    next[i][j] = r;
                    prev[i][j] = l;
                }
            }
        }
        ll tans = 0;
        for(int i = 0; i < q; i++) {
            int id, l, r;
            cin >> id >> l >> r;
            id = ((id + tans) % k) + 1;
            l = ((l + tans) % n) + 1;
            r = ((r + tans) % n) + 1;
            --l, --r, --id;
            ll now_l = -1, now_r = -1;
            ll ans = 0;
            now_l = next[id][l] + 1;
            now_r = prev[id][r] - 1;
            if(now_l <= now_r) {
                ans += (pfx[id][now_r] - pfx[id][now_l - 1]);
                ans += f(l, now_l - 1);
                ans += f(now_r + 1, r);
            } else if(next[id][r] == next[id][l] && prev[id][l] == prev[id][r]) {
                ans += f(l, r);
            } else {
                ans += f(l, next[id][l]) + f(next[id][l] + 1, r);
            }
            tans = ans;
            cout << ans << "\n";
        }
    }
    return 0;
}