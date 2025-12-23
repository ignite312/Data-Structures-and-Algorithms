// https://atcoder.jp/contests/abc402/submissions/65039350
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 9;
int n, x;
bool visited[(1 << N) + 1][50001];
double dp[(1 << N) + 1][50001];
vector<array<int, 3>> v(N);

double solve(int mask, int y) {
    if(visited[mask][y]) return dp[mask][y];
    visited[mask][y] = true;
    double res = 0.0;
    for (int i = 0; i < n; ++i) {
        if (!(mask & (1 << i))) {
            double p = (double)v[i][2] / 100.0;
            double q = 1.0 - p;
            int now = y + v[i][1];
            if (now <= x) {
                double solve_score = v[i][0] + solve(mask | (1 << i), now);
                double unsolve_score = solve(mask, now);
                double expected = p * solve_score + q * unsolve_score;
                res = max(res, expected);
            }
        }
    }
    return dp[mask][y] = res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        cin >> n >> x;
        for(int i = 0; i < n; i++) {
            cin >> v[i][0] >> v[i][1] >> v[i][2];
        }
        cout << fixed << setprecision(10) << solve(0, 0) << "\n";
    }
    return 0;
}
/*
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 9;
int n, x;
vector<array<int, 3>> v(N);
double dp[(1 << N)][50001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> x;
    for(int i = 0; i < n; i++) {
        cin >> v[i][0] >> v[i][1] >> v[i][2];
    }
    for (int mask = (1 << n) - 1; mask >= 0; --mask) {
        for (int y = x; y >= 0; --y) {
            for (int i = 0; i < n; ++i) {
                if (!(mask & (1 << i))) {
                    double p = (double)v[i][2] / 100.0;
                    double q = 1.0 - p;
                    int next_time = y + v[i][1];
                    if (next_time <= x) {
                        double solve_score = v[i][0] + dp[mask | (1 << i)][next_time];
                        double unsolve_score = dp[mask][next_time];
                        double expected = p * solve_score + q * unsolve_score;
                        dp[mask][y] = max(dp[mask][y], expected);
                    }
                }
            }
        }
    }
    cout << fixed << setprecision(10) << dp[0][0] << "\n";
    return 0;
}
*/