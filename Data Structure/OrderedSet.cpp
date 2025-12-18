// https://codeforces.com/gym/105873/problem/I
// Erase in ordered multiset is not supported directly
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;
template <class T>
using ordered_multiset = tree<
    T,
    null_type,
    less_equal<T>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--) {
        ordered_set<int> os;
        os.insert(5);
        os.insert(1);
        os.insert(10);
        os.insert(3);
        os.insert(5);

        auto it = os.find_by_order(5);
        if(it == os.end()) {
          cout << "Out of index\n";
        }
        cout << *os.find_by_order(1) << "\n"; // find by index
        cout << os.order_of_key(6) << "\n"; // count total number less than
    }
    return 0;
}