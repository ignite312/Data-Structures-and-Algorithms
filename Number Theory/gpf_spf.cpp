// https://codeforces.com/contest/1366/problem/D
#include <bits/stdc++.h>
using namespace std;
const int N = 1e7+1;
int spf[N];  // Smallest Prime Factor
int gpf[N];  // Greatest Prime Factor

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
    computeGPF();
    int tt = 1;
    // cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        vector<array<int, 2>> ans(n); 
        for(int i = 0; i < n; i++) {
            int x;
            cin >> x;
            int _gpf = gpf[x];
            int d1 = 1;
            int _x = x;
            while(_x % _gpf == 0) {
                _x/=_gpf;
                d1*=_gpf;
            }
            if(_x == 1) {
                ans[i][0] = ans[i][1] = -1;
            }else {
                ans[i][0] = d1;
                ans[i][1] = x/d1;
            }
        }
        for(int i = 0; i < n; i++) {
            cout << ans[i][0] << " ";
        }
        cout << "\n";
        for(int i = 0; i < n; i++) {
            cout << ans[i][1] << " ";
        }
    }
    return 0;
}