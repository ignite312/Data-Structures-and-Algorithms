#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        vector<int> ele(n);
        for(int i = 0; i < n; i++) {
            cin >> ele[i];
        }
        for(int i = 0; i < n; i++) {
            cout << ele[i] << " ";
        }
    }
}
