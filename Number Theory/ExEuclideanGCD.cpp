// https://codeforces.com/problemset/problem/1514/C
#include<bits/stdc++.h>
using namespace std;

// O(logmax(a,b))
int ExEuclideanGCD(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = ExEuclideanGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
// O(logm)
int modInverse(int a, int m) { // finding a^-1, m can be prime or non-prime
    int m0 = m, y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        int q = a / m;
        int t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
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
        int prod = 1;
        vector<int> ans;
        for(int i = 1; i < n; i++) {
            if(__gcd(i, n) == 1) {
                ans.push_back(i);
                prod = (prod*1LL*i) % n;
            }
        }
        if(prod != 1) {
            int inv = modInverse(prod, n);
            auto it = find(ans.begin(), ans.end(), inv);
            if(it != ans.end())ans.erase(it);
        }
        cout << ans.size() << "\n";
        for(int i = 0; i < (int)ans.size(); i++) {
            cout << ans[i] << " ";
        }
    }
    return 0;
}