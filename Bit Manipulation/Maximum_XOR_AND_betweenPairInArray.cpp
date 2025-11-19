// https://www.geeksforgeeks.org/maximum-value-pair-array/
// https://www.geeksforgeeks.org/maximum-xor-of-two-numbers-in-an-array/
#include <bits/stdc++.h>
using namespace std;

// nlog(m), where m is the maximum number present in the array
int max_xor(vector<int> &a, int n) {
    int mx = 0, mask = 0;
    set<int> st;
    for (int i = 30; i >= 0; i--) {
        mask |= (1 << i);
        for (int i = 0; i < n; ++i) {
            st.insert(a[i] & mask);
        }
        int newMx = mx | (1 << i);
        for (int prefix : st) {
            if (st.count(newMx ^ prefix)) {
                mx = newMx;
                break;
            }
        }
        st.clear();
    }
    return mx;
}
int checkBit(int pattern, vector<int> &a, int n) {
    int count = 0;
    for (int i = 0; i < n; i++)
        if ((pattern & a[i]) == pattern)
            count++;
    return count;
}
// nlog(m), where m is the maximum number present in the array
int max_and(vector<int> &a, int n) {
    int res = 0, count;
     for (int bit = 31; bit >= 0; bit--) {
        count = checkBit(res | (1 << bit), a, n);
        if (count >= 2)
            res = res | (1 << bit); 
    }
    return res;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  tt = 1;
  // cin >> tt;
  while(tt--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << max_xor(a, n);
  }
  return 0;
}