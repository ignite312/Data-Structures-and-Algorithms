// https://codeforces.com/gym/102644/problem/C
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mod = 1e9 + 7;

template <class T, int N, int M> 
struct Matrix {
  typedef Matrix Mx;
  array<array<T, M>, N> d{};

  // Matrix multiplication
  template <int P>
    Matrix<T, N, P> operator*(const Matrix<T, M, P>& m) const {
      Matrix<T, N, P> a;
      for (int i = 0; i < N; i++)
        for (int j = 0; j < P; j++)
          for (int k = 0; k < M; k++)
            a.d[i][j] = (a.d[i][j] + d[i][k] * m.d[k][j]) % mod;
      return a;
    }
  // Matrix-vector multiplication
  vector<T> operator*(const vector<T>& vec) const {
    vector<T> ret(N, 0);
    for (int i = 0; i < N; i++)
      for (int j = 0; j < M; j++)
        ret[i] += d[i][j] * vec[j];
    return ret;
  }
  // Matrix exponentiation
  Matrix<T, N, N> operator^(ll p) const {
    static_assert(N == M);
    assert(p >= 0);
    Matrix < T, N, N > a, b( * this);
    for (int i = 0; i < N; i++) a.d[i][i] = 1; // Identity matrix
    while (p) {
      if (p & 1) a = a * b;
      b = b * b;
      p >>= 1;
    }
    return a;
  }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        ll k;
        cin >> k;
        Matrix<ll, 2, 2> mat;
        mat.d[0][0] = 1;
        mat.d[0][1] = 1;
        mat.d[1][0] = 1;
        mat.d[1][1] = 0;
        cout << (mat ^ k).d[1][0] << "\n";
    }
    return 0;
}