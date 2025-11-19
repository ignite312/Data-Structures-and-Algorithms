// https://codeforces.com/gym/102644/problem/C
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int M = 1e9 + 7;

struct Matrix {
    int a[2][2] = {{0, 0}, {0, 0}};
    Matrix operator *(const Matrix& other) {
        Matrix product;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    product.a[i][k] = (product.a[i][k] + (ll) a[i][j] * other.a[j][k]) % M;
                }
            }
        }
        return product;
    }
};
Matrix expo_power(Matrix a, ll k) {
    Matrix product;
    for (int i = 0; i < 2; i++) {
        product.a[i][i] = 1;
    }
    while (k > 0) {
        if (k % 2) {
            product = product * a;
        }
        a = a * a;
        k /= 2;
    }
    return product;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        ll k;
        cin >> k;
        Matrix M;
        M.a[0][0] = 1;
        M.a[0][1] = 1;
        M.a[1][0] = 1;
        M.a[1][1] = 0;
        cout << expo_power(M, k).a[1][0] << "\n";
    }
    return 0;
}
