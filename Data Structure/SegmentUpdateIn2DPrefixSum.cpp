// https://codeforces.com/contest/2000/problem/E
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n, m, k;

void update(vector<vector<ll>>& grid, int x1, int y1, int x2, int y2, int val) {
    grid[x1][y1] += val;
    if (x2 + 1 < n) grid[x2 + 1][y1] -= val;
    if (y2 + 1 < m) grid[x1][y2 + 1] -= val;
    if (x2 + 1 < n && y2 + 1 < m) grid[x2 + 1][y2 + 1] += val;
}
vector<vector<ll>> calculate(vector<vector<ll>> &grid) {
    vector<vector<ll>> ans(n, vector<ll>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ans[i][j] = grid[i][j];
            if(i > 0) ans[i][j] += ans[i - 1][j];
            if(j > 0) ans[i][j] += ans[i][j - 1];
            if(i > 0 && j > 0) ans[i][j] -= ans[i - 1][j - 1];
        }
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        cin >> n >> m >> k;
        vector<vector<ll>> grid(n, vector<ll>(m, 0));
        for(int i = 0; i < n-k+1; i++) {
            for(int j = 0; j < m-k+1; j++) {
                update(grid, i, j, i+k-1, j+k-1, 1);
            }
        }
        int w;
        cin >> w;
        vector<ll> wt(w);
        for(int i = 0; i < w; i++) {
            cin >> wt[i];
        }
        grid = calculate(grid);
        vector<ll> cnt;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cnt.push_back(grid[i][j]);
            }
        }
        sort(cnt.rbegin(), cnt.rend());
        sort(wt.rbegin(), wt.rend());
        ll ans = 0;
        for(int i = 0; i < w; i++) {
            ans += wt[i] * cnt[i];
        }
        cout << ans << "\n";
    }
    return 0;
}