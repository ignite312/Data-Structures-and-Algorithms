#include<bits/stdc++.h>
using namespace std;

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
    }
    return 0;
}
