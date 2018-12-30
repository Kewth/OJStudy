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
const int maxv = 25050, maxn = 110;
bool f[maxv];
int a[maxn];

// Main function {{{1
int main() {
	/* freopen("money.in", "r", stdin); */
	/* freopen("money.out", "w", stdout); */
	int T = input();
	while(T --) {
		int n  = input(), max = 0;
		for(int i=1;i<=n;i++) {
			a[i] = input();
			max = std::max(a[i], max);
		}
		std::sort(a+1, a+n+1);
		f[0] = true;
		for(int i=1;i<=max;i++) {
			f[i] = false;
			for(int j=1;j<=n&&a[j]<=i;j++)
				if(f[i-a[j]]) {
					f[i] = true;
					break;
				}
		}
		int ans = 0;
		for(int i=1;i<=n;i++) {
			bool can = true;
			for(int j=1;j<i;j++)
				if(f[a[i]-a[j]]) {
					can = false;
					break;
				}
			if(can) ans ++;
		}
		printf("%d\n", ans);
	}
}

// }}}1
