// S_n = a(1-r^n)/(1-r)
long long geometricSeriesSum(long long a, long long r, int n) {
    if (r == 1) return a * n;
    return a * (bigPow(r, n) - 1) / (r - 1);
}
// S_n = n/2*(2*a + (n-1)*d)
long long arithmeticSeriesSum(long long a, long long d, long long n) {
    return n * (2*a + (n-1)*d) / 2;
}
