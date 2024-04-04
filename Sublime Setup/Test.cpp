#include<bits/stdc++.h>
using namespace std;
#define ll long long
int N = 200000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        vector<int> v(n);
        for(int i = 0; i < n; i++) {
            cin >> v[i];
        }
        for(int i = 0; i < n; i++) {
            cout << v[i] << " ";
        }
    }
}
