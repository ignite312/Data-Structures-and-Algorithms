## Function to calculate ``nCr`` and ``nPr``
```C++
ll nPr(int n, int r) {
    if (r < 0 || r > n) {
        return 0;
    }
    ll result = 1;
    for (int i = 0; i < r; ++i) {
        result *= n--;
    }
    return result;
}
ll nCr(int n, int r) {
    if (r < 0 || r > n) {
        return 0;
    }
    ll result = 1;
    for(int i = 1; i <= r; ++i) {
        result *= n--;
        result /= i;
    }
    return result;
}
```