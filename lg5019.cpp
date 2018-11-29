// include files {{{1
#include <bits/stdc++.h>

// function to speed up input {{{1
long long input() {
	int ch = getchar();
	long long res = 0;
	while(ch < '0' or ch > '9') ch = getchar();
	while(ch >= '0' and ch <= '9') res = res * 10 + ch - '0', ch = getchar();
	return res;
}

// global variables {{{1
const int maxn = 100050;
int d[maxn];

// Main function {{{1
int main() {
	int n = input();
	long long ans = 0;
	d[0] = 0;
	for(int i=1;i<=n;i++) {
		d[i] = input();
		if(d[i] > d[i-1])
			ans += d[i] - d[i-1];
	}
	printf("%lld\n", ans);
}

// }}}1
