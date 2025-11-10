// https://codeforces.com/contest/1983/problem/D
#include <bits/stdc++.h>
using namespace std;
int inversion_count = 0;

void merge(vector<int> &v, int l, int r, int mid) {
    vector<int> L(v.begin() + l, v.begin() + mid + 1);
    vector<int> R(v.begin() + mid + 1, v.begin() + r + 1);
    int i = 0, j = 0, k = l;
    int l_sz = L.size();
    while(i < L.size() && j < R.size()) {
        if(L[i] <= R[j]) {
            v[k++] = L[i++];
        } else {
            v[k++] = R[j++];
            inversion_count += (l_sz - i); 
        }
    }
    while(i < L.size()) v[k++] = L[i++];
    while(j < R.size()) v[k++] = R[j++];
}
// 0-base indexing
void mergeSort(vector<int> &v, int l, int r) {
    if(l == r)return;
    int mid = l + (r - l)/2;
    mergeSort(v, l, mid);
    mergeSort(v, mid+1, r);
    merge(v, l, r, mid);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        vector<int> v(n), _v(n);
        set<int> st, _st;
        for(int i = 0; i < n; i++) {
            cin >> v[i];
            st.insert(v[i]);
        }
        for(int i = 0; i < n; i++) {
            cin >> _v[i];
            _st.insert(_v[i]);
        }
        if(st != _st) {
            cout << "No\n";
            continue;
        }
        mergeSort(v, 0, n-1);
        int count_1 = inversion_count;
        inversion_count = 0;
        mergeSort(_v, 0, n-1);
        if((count_1 % 2 == 0 && inversion_count % 2 == 0) || (count_1 % 2 != 0 && inversion_count % 2 != 0)) {
            cout << "Yes\n";
        }else cout << "No\n";
        inversion_count = 0;
    }
    return 0;
}