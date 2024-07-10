// https://codeforces.com/contest/1983/problem/D
#include <bits/stdc++.h>
using namespace std;
int inversion_count = 0;

void merge(vector<int> &v, int l, int r, int mid) {
    int l_sz = mid - l + 1;
    int r_sz = r - (mid + 1) + 1;
    int L[l_sz], R[r_sz];
    for(int i = 0; i < l_sz; i++)L[i] = v[i+l];
    for(int i = 0; i < r_sz; i++)R[i] = v[i+mid+1];
    int l_i = 0, r_i = 0;
    
    for(int i = l; i <= r && l_i < l_sz && r_i < r_sz; i++) {
        if(L[l_i] <= R[r_i])l_i++;
        else if(L[l_i] > R[r_i]){
            inversion_count+=(l_sz-1)-l_i+1;
            r_i++;
        }
    }
    l_i = 0, r_i = 0;
    for(int i = l; i <= r; i++) {
        if(r_i == r_sz) {
            v[i] = L[l_i];
            l_i++;
        }else if(l_i == l_sz) {
            v[i] = R[r_i];
            r_i++;
        }else if(L[l_i] <= R[r_i]) {
            v[i] = L[l_i];
            l_i++;
        }else {
            v[i] = R[r_i];
            r_i++;
        }
    }
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