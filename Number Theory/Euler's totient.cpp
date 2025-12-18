// https://www.hackerrank.com/contests/srbd-code-contest-2024-round-1/challenges/mathematician-montu/problem
#include <bits/stdc++.h>
using namespace std;
const int N = 1000000;
#define ll long long
vector<bool> is_prime(N+1, true);
vector<int> primes;

void sieve() {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= N; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= N; j += i)
                is_prime[j] = false;
        }
    }
    for(int i = 2; i <= N; i++) {
        if(is_prime[i]) {
            primes.push_back(i);
        }
    }
}

// O(sqrt(N))
ll phi(ll n) {
    ll result = n;
    for (ll p : primes) {
        if (p * p > n) break;
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result/n;
    return result;
}

unordered_map<ll, ll> phi_cache;
ll cached_phi(ll n) {
    if (phi_cache.count(n)) return phi_cache[n];
    return phi_cache[n] = phi(n);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    sieve();
    int tt;
    cin >> tt;
    for (int cs = 1; cs <= tt; cs++) {
        ll n;
        int q;
        cin >> n >> q;
        cout << "Case " << cs << ":";
        vector<pair<ll, int>> queries(q);
        for (int i = 0; i < q; i++) {
            cin >> queries[i].first;
            queries[i].second = i;
        }
        sort(queries.begin(), queries.end());
        vector<ll> answers(q);
        for (int i = 0; i < q; i++) {
            ll m = queries[i].first;
            int idx = queries[i].second;
            if (n % m == 0) {
                answers[idx] = cached_phi(n / m);
            } else {
                answers[idx] = 0;
            }
        }
        for (ll ans : answers) {
            cout << " " << ans;
        }
        cout << "\n";
    }
    return 0;
}