#include<bits/stdc++.h>
using namespace std;
void printInt128(__int128 x) {
    if (x == 0) {
        cout << 0;
        return;
    }
    if (x < 0) {
        cout << '-';
        x = -x;
    }
    string s;
    while (x > 0) {
        s.push_back('0' + x % 10);
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        cin.ignore();
        while(n--) {
            string sentence;
            getline(cin, sentence);
            istringstream iss(sentence);
            string word;
            while (iss >> word) {
                cout << word << " ";
            }cout << "\n";
        }
        __int128 val = (__int128)1e18 * 1e18;
        printInt128(val);
        cout << '\n';
    }
    return 0;
}