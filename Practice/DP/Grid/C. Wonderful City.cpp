//https://codeforces.com/problemset/problem/2096/C
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1001;
const ll INF = 1e18;
int grid[N][N];
int a[N], b[N];
int n;
ll dp_row[N][2], dp_col[N][2];

ll solve_row() {
    for (int i = 0; i < n; ++i) {
        dp_row[i][0] = dp_row[i][1] = INF;
    }
    dp_row[0][0] = 0;
    dp_row[0][1] = a[0];
    for (int i = 1; i < n; ++i) {
        for (int prev = 0; prev < 2; ++prev) {
            if (dp_row[i-1][prev] == INF) continue;
            for (int curr = 0; curr < 2; ++curr) {
                bool valid = true;
                for (int j = 0; j < n; ++j) {
                    int h1 = grid[i-1][j] + prev;
                    int h2 = grid[i][j] + curr;
                    if (h1 == h2) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    ll cost = dp_row[i-1][prev] + (curr ? a[i] : 0);
                    if (cost < dp_row[i][curr]) {
                        dp_row[i][curr] = cost;
                    }
                }
            }
        }
    }
    return min(dp_row[n-1][0], dp_row[n-1][1]);
}

ll solve_col() {
    for (int j = 0; j < n; ++j) {
        dp_col[j][0] = dp_col[j][1] = INF;
    }
    dp_col[0][0] = 0;
    dp_col[0][1] = b[0];
    for (int j = 1; j < n; ++j) {
        for (int prev = 0; prev < 2; ++prev) {
            if (dp_col[j-1][prev] == INF) continue;
            for (int curr = 0; curr < 2; ++curr) {
                bool valid = true;
                for (int i = 0; i < n; ++i) {
                    int h1 = grid[i][j-1] + prev;
                    int h2 = grid[i][j] + curr;
                    if (h1 == h2) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    ll cost = dp_col[j-1][prev] + (curr ? b[j] : 0);
                    if (cost < dp_col[j][curr]) {
                        dp_col[j][curr] = cost;
                    }
                }
            }
        }
    }
    return min(dp_col[n-1][0], dp_col[n-1][1]);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while(tt--) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cin >> grid[i][j];
            }
        }
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for(int i = 0; i < n; i++) {
            cin >> b[i];
        }
        ll x = solve_row();
        ll y = solve_col();
        if (x == INF || y == INF) {
            cout << -1 << "\n";
        } else {
            cout << x + y << "\n";
        }
    }
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1001;
const ll INF = 1e18;
int grid[N][N];
int a[N], b[N];
int n;
ll dp_row[N][2], dp_col[N][2];

ll solve_row() {
    for (int i = 0; i < n; ++i) {
        dp_row[i][0] = dp_row[i][1] = INF;
    }
    dp_row[0][0] = 0;
    dp_row[0][1] = a[0];
    for (int i = 1; i < n; ++i) {
        for (int prev = 0; prev < 2; ++prev) {
            if (dp_row[i-1][prev] == INF) continue;
            for (int curr = 0; curr < 2; ++curr) {
                bool valid = true;
                for (int j = 0; j < n; ++j) {
                    int h1 = grid[i-1][j] + prev;
                    int h2 = grid[i][j] + curr;
                    if (h1 == h2) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    ll cost = dp_row[i-1][prev] + (curr ? a[i] : 0);
                    if (cost < dp_row[i][curr]) {
                        dp_row[i][curr] = cost;
                    }
                }
            }
        }
    }
    return min(dp_row[n-1][0], dp_row[n-1][1]);
}

ll solve_col() {
    for (int j = 0; j < n; ++j) {
        dp_col[j][0] = dp_col[j][1] = INF;
    }
    dp_col[0][0] = 0;
    dp_col[0][1] = b[0];
    for (int j = 1; j < n; ++j) {
        for (int prev = 0; prev < 2; ++prev) {
            if (dp_col[j-1][prev] == INF) continue;
            for (int curr = 0; curr < 2; ++curr) {
                bool valid = true;
                for (int i = 0; i < n; ++i) {
                    int h1 = grid[i][j-1] + prev;
                    int h2 = grid[i][j] + curr;
                    if (h1 == h2) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    ll cost = dp_col[j-1][prev] + (curr ? b[j] : 0);
                    if (cost < dp_col[j][curr]) {
                        dp_col[j][curr] = cost;
                    }
                }
            }
        }
    }
    return min(dp_col[n-1][0], dp_col[n-1][1]);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while(tt--) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cin >> grid[i][j];
            }
        }
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for(int i = 0; i < n; i++) {
            cin >> b[i];
        }
        ll x = solve_row();
        ll y = solve_col();
        if (x == INF || y == INF) {
            cout << -1 << "\n";
        } else {
            cout << x + y << "\n";
        }
    }
    return 0;
}