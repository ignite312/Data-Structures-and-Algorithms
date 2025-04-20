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
    if(y > x) return 0.00;
    if(visited[mask][y]) return dp[mask][y];
    visited[mask][y] = true;

    double res = 0.0;
    for (int i = 0; i < n; ++i) {
        if (!(mask & (1 << i))) {
            double p = (double)v[i][2] / 100.0;
            double q = 1.0 - p;
            int now = y + v[i][1];
            double solve_score = 0.00;
            if (now <= x) {
                solve_score = v[i][0] + solve(mask | (1 << i), now);
            }
            double unsolve_score = solve(mask, now);
            double expected = p * solve_score + q * unsolve_score;
            res = max(res, expected);
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