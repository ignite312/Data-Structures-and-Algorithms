<snippet>
	<content><![CDATA[
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
void factorial() {
    fact[0] = fact[1] = 1;
    for(int i = 2; i <= N; i++) {
        fact[i] = (fact[i-1] * i) % M;
    }
}
]]></content>
	<!-- Optional: Set a tabTrigger to define how to trigger the snippet -->
	<tabTrigger>NCR</tabTrigger>
	<!-- Optional: Set a scope to limit where the snippet will trigger -->
	<scope>source.c++</scope>
</snippet>
