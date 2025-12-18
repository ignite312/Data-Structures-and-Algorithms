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
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
      int a, b;
      cin >> a >> b;
      int x, y;
      cout << ExEuclideanGCD(a, b, x, y) << " " << x << " " << y << "\n";
    }
    return 0;
}