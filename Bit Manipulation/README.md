## Maximum AND value of a pair in an array
```C++
// CPP Program to find maximum XOR value of a pair
#include <bits/stdc++.h>
using namespace std;

// Utility function to check number of elements
// having set msb as of pattern
int checkBit(int pattern, int arr[], int n)
{
	int count = 0;
	for (int i = 0; i < n; i++)
		if ((pattern & arr[i]) == pattern)
			count++;
	return count;
}

// Function for finding maximum and value pair
int maxAND(int arr[], int n)
{
	int res = 0, count;

	// iterate over total of 32bits from msb to lsb
	for (int bit = 31; bit >= 0; bit--) {
		// find the count of element having same pattern as
		// obtained by adding bits on every iteration.
		count = checkBit(res | (1 << bit), arr, n);

		// if count >= 2 set particular bit in result
		if (count >= 2)
			res = res | (1 << bit); // this is the pattern
									// we continued
	}

	return res;
}

// Driver function
int main()
{
	int arr[] = { 4, 8, 6, 2 };
	int n = sizeof(arr) / sizeof(arr[0]);
	cout << "Maximum AND Value = " << maxAND(arr, n);
	return 0;
}
```
Maximum XOR of Two Numbers in an Array
```c++
// C++ implementation of the above approach

#include <bits/stdc++.h>
using namespace std;

// Function to return the
// maximum xor
int max_xor(int arr[], int n)
{
	int maxx = 0, mask = 0;

	set<int> se;

	for (int i = 30; i >= 0; i--) {

		// set the i'th bit in mask
		// like 100000, 110000, 111000..
		mask |= (1 << i);

		for (int i = 0; i < n; ++i) {

			// Just keep the prefix till
			// i'th bit neglecting all
			// the bit's after i'th bit
			se.insert(arr[i] & mask);
		}

		int newMaxx = maxx | (1 << i);

		for (int prefix : se) {

			// find two pair in set
			// such that a^b = newMaxx
			// which is the highest
			// possible bit can be obtained
			if (se.count(newMaxx ^ prefix)) {
				maxx = newMaxx;
				break;
			}
		}

		// clear the set for next
		// iteration
		se.clear();
	}

	return maxx;
}

// Driver Code
int main()
{

	int arr[] = { 25, 10, 2, 8, 5, 3 };
	int n = sizeof(arr) / sizeof(arr[0]);

	cout << max_xor(arr, n) << endl;

	return 0;
}
```

```c++
#include <iostream>

using namespace std;

class Node {
public:
	Node* one;
	Node* zero;
};

class trie {
	Node* root;

public:
	trie() { root = new Node(); }

	void insert(int n)
	{
		Node* temp = root;
		for (int i = 31; i >= 0; i--) {
			int bit = (n >> i) & 1;
			if (bit == 0) {
				if (temp->zero == NULL) {
					temp->zero = new Node();
				}
				temp = temp->zero;
			}
			else {
				if (temp->one == NULL) {
					temp->one = new Node();
				}
				temp = temp->one;
			}
		}
	}

	int max_xor_helper(int value)
	{
		Node* temp = root;
		int current_ans = 0;

		for (int i = 31; i >= 0; i--) {
			int bit = (value >> i) & 1;
			if (bit == 0) {
				if (temp->one) {
					temp = temp->one;
					current_ans += (1 << i);
				}
				else {
					temp = temp->zero;
				}
			}
			else {
				if (temp->zero) {
					temp = temp->zero;
					current_ans += (1 << i);
				}
				else {
					temp = temp->one;
				}
			}
		}
		return current_ans;
	}

	int max_xor(int arr[], int n)
	{
		int max_val = 0;
		insert(arr[0]);
		for (int i = 1; i < n; i++) {
			max_val = max(max_xor_helper(arr[i]), max_val);
			insert(arr[i]);
		}
		return max_val;
	}
};

int main()
{
	int input[] = { 25, 10, 2, 8, 5, 3 };
	int n = sizeof(input) / sizeof(int);
	trie t;
	cout << t.max_xor(input, n);

	return 0;
}

```
