#include <bits/stdc++.h>
using namespace std;
#define ll long long

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
            a.d[i][j] += d[i][k] * m.d[k][j];
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
template<class T> struct SubMatrix {
  // 0-based indexing
  vector<vector<T>> p;
  SubMatrix(const vector<vector<T>>& v) {
    int R = v.size(), C = v[0].size();
    p.assign(R + 1, vector<T>(C + 1, 0));
    for (int r = 0; r < R; ++r) {
      for (int c = 0; c < C; ++c) {
        p[r + 1][c + 1] = v[r][c] + p[r][c + 1] + p[r + 1][c] - p[r][c];
      }
    }
  }
  T sum(int u, int l, int d, int r) {
    return p[d + 1][r + 1] - p[u][r + 1] - p[d + 1][l] + p[u][l];
  }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        // Create a 2x4 matrix
        Matrix<int, 2, 4> mat1;
        mat1.d = {{
            {1, 4, 55, 7},
            {1, 6, 87, 4}
        }};

        // Create a 4x4 matrix
        Matrix<int, 4, 4> mat2;
        mat2.d = {{
            {6, 2, 2, 1},
            {7, 55, 72, 1},
            {5, 7, 6, 8},
            {7, 6, 1, 3}
        }};

        // Matrix multiplication mat1 * mat2
        Matrix<int, 2, 4> result = mat1 * mat2;
        cout << "Result of mat1 * mat2:\n";
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++)
                cout << result.d[i][j] << " ";
            cout << "\n";
        }

        // Matrix-vector multiplication
        vector<int> vec = {1, 1, 1, 1};
        vector<int> res_vec = mat1 * vec;
        cout << "Result of mat1 * vec:\n";
        for (int i = 0; i < 2; i++)
            cout << res_vec[i] << " ";
        cout << "\n";

        // Matrix exponentiation mat2^3
        Matrix<int, 4, 4> exp_result = mat2 ^ 3;
        cout << "Result of mat2^3:\n";
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                cout << exp_result.d[i][j] << " ";
            cout << "\n";
        }
    }
    return 0;
}