// https://www.codechef.com/problems/PRIMEDST
// It counts all the number of paths of length 1 to k
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 50001;
vector<int> adj[N];
int n, k;
int subtree[N], cnt[N], mx_depth, all_cnt[N];
bool visited[N];
// ll ans;

vector<bool> is_prime(N, true);
set<int> primes;
// O(Nlog(log(N)))
void sieve() {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i < N; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < N; j += i)
                is_prime[j] = false;
        }
    }
}
int getSubtree(int u, int p) {
    subtree[u] = 1;
    for(auto v : adj[u]) {
        if(!visited[v] && v != p) {
            getSubtree(v, u);
            subtree[u]+=subtree[v];
        }
    }
    return subtree[u];
}
int getCentroid(int u, int p, int desired) {
    for(auto v : adj[u])
        if(!visited[v] && v != p && subtree[v] > desired)
            return getCentroid(v, u, desired);
    return u;
}
void compute(int u, int p, bool filling, int depth) {
    if(depth > k)return;
    mx_depth = max(mx_depth, depth);
    if(filling) {
        cnt[depth]++;
    }else {
        // ans+=cnt[k - depth]*1LL;
        for(int i = 0; i <= mx_depth; i++) {
            if(cnt[i])all_cnt[i + depth]+=cnt[i];
        }
    }
    for(auto v : adj[u])if(!visited[v] && v != p)compute(v, u, filling, depth+1);
}
void centroidDecomposition(int u) {
    int centroid = getCentroid(u, -1, getSubtree(u, -1) >> 1);
    visited[centroid] = true;
    mx_depth = 0;
    for(auto v : adj[centroid]) {
        if(!visited[v]) {
            compute(v, centroid, false, 1);
            compute(v, centroid, true, 1);
        }
    }
    for(int i = 1; i <= mx_depth; i++)cnt[i] = 0;
    for(auto v : adj[centroid])if(!visited[v])centroidDecomposition(v);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    sieve();
    tt = 1;
    // cin >> tt;
    while(tt--) {
        cin >> n;
        for(int i = 2; i <= n-1; i++) {
            if(is_prime[i]) {
                primes.insert(i);
            }
        }
        for(int i = 0; i < n-1; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        // ans = 0;
        cnt[0] = 1;
        k = *primes.rbegin();
        centroidDecomposition(1);
        ll p_path = 0;
        for(auto x : primes) {
            p_path+=all_cnt[x];
        }
        ll total = n*1LL*(n-1)/2;
        cout << fixed << setprecision(6) << (p_path*1.0)/(total*1.0) << "\n";
    }
    return 0;
}