// https://codeforces.com/contest/1951/problem/E
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000001;

int bigPow(ll b, ll p, const int mod) {
  int ans = 1 % mod;
  b %= mod;
  if(b < 0) b += mod;
  while(p) {
    if(p & 1) ans = (ll) ans * b % mod;
    b = (ll) b * b % mod;
    p >>= 1;
  }
  return ans;
}

const int mod1 = 127657753, mod2 = 987654319;
const int pw1 = 137, pw2 = 277;
int p1[N], p2[N], ip1[N], ip2[N];
void init() {
  p1[0] = p2[0] = 1;
  for(int i = 1; i < N; i++) {
    p1[i] = (ll)p1[i - 1]*pw1 % mod1;
    p2[i] = (ll)p2[i - 1]*pw2 % mod2;
  }
  int inv_pw1 = bigPow(pw1, mod1 - 2, mod1);
  int inv_pw2 = bigPow(pw2, mod2 - 2, mod2);
  ip1[0] = ip2[0] = 1;
  for(int i = 1; i < N; i++) {
    ip1[i] = (ll)ip1[i - 1]*inv_pw1 % mod1;
    ip2[i] = (ll)ip2[i - 1]*inv_pw2 % mod2;
  }
}
struct Hashing {
  int n;
  vector < int > h1, h2;
  void build(const string & s) {
    n = s.size();
    h1.assign(n + 1, 0), h2.assign(n + 1, 0);
    for(int i = 0; i < n; i++) {
      h1[i + 1] = (h1[i] + (ll)s[i] * p1[i]) % mod1;
      h2[i + 1] = (h2[i] + (ll)s[i] * p2[i]) % mod2;
    }
  }
  // Get hash of substring [l, r] (1-based)
  inline pair < int, int > get(int l, int r) {
    int x1 = (ll)(h1[r] - h1[l - 1] + mod1) * ip1[l - 1] % mod1;
    int x2 = (ll)(h2[r] - h2[l - 1] + mod2) * ip2[l - 1] % mod2;
    return { x1, x2 };
  }
  inline pair<int, int> full_hash() {
    return get(1, n);
  }
};
bool isPalindrome(Hashing & H, Hashing & RH, int l, int r, int n) { // 1-based
  return H.get(l, r) == RH.get(n - r + 1, n - l + 1);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  init();
  int tt;
  tt = 1;
  cin >> tt;
  while(tt--) {
    string s, rs;
    cin >> s;
    int n = s.size();
    int cnt = count(s.begin(), s.end(), s[0]);
    if (cnt == n) {
      cout << "NO\n";
      continue;
    }
    rs = s;
    reverse(rs.begin(), rs.end());
    Hashing H, RH;
    H.build(s);
    RH.build(rs);
    if (!isPalindrome(H, RH, 1, n, n)) {
      cout << "YES\n1\n" << s.substr(0, n) << "\n";
      continue;
    }
    bool ok = false;
    for(int i = 0; i < n; i++) {
      if(!isPalindrome(H, RH, 1, i + 1, n) && !isPalindrome(H, RH, i + 1 + 1, n, n)) {
        cout << "YES\n2\n" << s.substr(0, i + 1) << " " << s.substr(i + 1, n - (i + 1)) << "\n";
        ok = true;
        break;
      }
    }
    if (!ok) cout << "NO\n";
  }
  return 0;
}