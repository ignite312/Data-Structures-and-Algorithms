#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100000;
vector<bool> is_prime(N+1, true);

// O(Nlog(N))
void divisors() {
    vector<vector<int>> d(N+1);
    for(int i = 1; i <= N; i++) {
        for(int j = i; j <= N; j+=i) {
            d[j].push_back(i);
        }
    }
}
// O(sqrt(N))
vector<ll> divisor(ll a) {
    vector<ll> divisors;
    for (ll i = 1; i*i <= a; ++i) {
        if(a % i == 0) {
            if(a / i == i)divisors.push_back(i);
            else {
                divisors.push_back(i);
                divisors.push_back(a/i);
            }
        }
    }
    return divisors;
}
// O(Nlog(log(N)))
void sieve() {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= N; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= N; j += i)
                is_prime[j] = false;
        }
    }
}
// O(sqrt(N))
vector<ll> prime_factorization(ll n) {
    vector<ll> factorization;
    while (n % 2 == 0) {
        factorization.push_back(2);
        n /= 2;
    }
    for (ll d = 3; d * d <= n; d += 2) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
    }
    if (n > 1) factorization.push_back(n);
    return factorization;
}
// O(sqrt(N))
int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        } 
    }
    if (n > 1)
        result -= result / n;
    return result;
}
// O(Nloglog(N))
void phi_1_to_n(int n) {
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}
// O(Nloglog(N))
void phi_1_to_n_(int n) {
    vector<int> phi(n + 1);
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        phi[i] = i - 1;

    for (int i = 2; i <= n; i++)
        for (int j = 2 * i; j <= n; j += i)
              phi[j] -= phi[i];
}
//O(Nlog(logN))
void computeSPF() {
    iota(spf, spf + N, 0);
    for (int i = 2; i < N; i++) { // i*i will work
        if (spf[i] == i) {
            for (int j = 2*i; j < N; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
}
//O(Nlog(logN))
void computeGPF() {
    iota(gpf, gpf + N, 0);
    for (int i = 2; i < N; i++) { // N = 30, gpf[28] i*i will not work
        if (gpf[i] == i) {
            for (int j = 2*i; j < N; j += i) {
                gpf[j] = i;
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
    }
    return 0;
}