#include<bits/stdc++.h>
using namespace std;

vector<string> permutation(string s) {
    sort(s.begin(), s.end());
    vector<string> ans;
    do {
        ans.push_back(s);
    }while(next_permutation(s.begin(), s.end()));
    return ans;
}
vector<string> combination(int n, int k) {
    vector<string> ans;
    for(int mask = 0; mask < (1 << n); mask++) {
        if(__builtin_popcount(mask) != k)continue;
        string s = "";
        for(int i = 0; i < n; i++) if(mask & (1 << i))s+=to_string(i+1);
            ans.push_back(s);
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    while(tt--) {
        vector<string> combinations = combination(8, 4);
        for(auto ele : combinations){cout << ele << "\n";}
            cout << "\n";
        
        string s = "12345";
        vector<string> permutations = permutation(s);
        for(auto ele : permutations){cout << ele << "\n";}
    }
}
