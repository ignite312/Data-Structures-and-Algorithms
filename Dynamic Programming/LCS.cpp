// https://lightoj.com/problem/batman
#include <bits/stdc++.h>
using namespace std;
const int N = 51;
int dp[N][N][N];

int lcsRec(string &s1, string &s2, string &s3, int m, int n, int o) {
    if (m == 0 || n == 0 || o == 0)
        return 0;
    if (dp[m][n][o] != -1)
        return dp[m][n][o];
    if (s1[m - 1] == s2[n - 1] && s1[m-1] == s3[o-1])
        return dp[m][n][o] = 1 + lcsRec(s1, s2, s3, m - 1, n - 1, o-1);
    int ret = INT_MIN;
    for(int i = -1; i < 1; i++) {
      for(int j = -1; j < 1; j++) {
        for(int k = -1; k < 1; k++) {
          if(i == j && i == k)continue;
          ret = max(ret, lcsRec(s1, s2, s3, m+i, n+j, o+k));
        }
      }
    }
    return dp[m][n][o] = ret;
}
int lcs(string &s1,string &s2, string &s3){
    int m = s1.length();
    int n = s2.length();
    int o = s3.length();
    memset(dp, -1, sizeof(dp));
    return lcsRec(s1, s2, s3, m, n, o);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt, cs = 1;
  tt = 1;
  cin >> tt;
  while (tt--) {
    string a, b, c;
    cin >> a >> b >> c;
    cout << "Case " << cs++ << ": " << lcs(a, b, c) << "\n";
  }
  return 0;
}