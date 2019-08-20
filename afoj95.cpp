#if 0
2019.08.20

直接 DP 设 f[i][j] 表示考虑前 i 个，钦定第 i 个字符为 j 的方案数。
需要注意的是 1 这个字符需同时考虑两边，把状态分成两种 1 即可。
#endif
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

const int maxn = 1000005, mod = 1000000007;
char s[maxn];
int f[maxn][5];

int main() {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1));

	switch(s[1]) {
		case '?': f[1][0] = f[1][3] = f[1][4] = 1; break;
		case '*': f[1][3] = 1; break;
		case '0': f[1][0] = 1; break;
		case '1': f[1][4] = 1; break;
		case '2': break;
	}

	for(int i = 2; i <= n; i ++) {
		if(s[i] == '?' or s[i] == '0')
			f[i][0] = (f[i - 1][0] + f[i - 1][1]) % mod;

		if(s[i] == '?' or s[i] == '1') {
			f[i][1] = f[i - 1][3];
			f[i][4] = (f[i - 1][0] + f[i - 1][1]) % mod;
		}

		if(s[i] == '?' or s[i] == '2')
			f[i][2] = f[i - 1][3];

		if(s[i] == '?' or s[i] == '*')
			f[i][3] = (0ll + f[i - 1][4] + f[i - 1][2] + f[i - 1][3]) % mod;

		/* debug("%d %d %d %d %d\n", f[i][0], f[i][1], f[i][2], f[i][3], f[i][4]); */
	}

	switch(s[n]) {
		case '?': printf("%lld\n", (0ll + f[n][0] + f[n][1] + f[n][3]) % mod); break;
		case '*': printf("%d\n", f[n][3]); break;
		case '0': printf("%d\n", f[n][0]); break;
		case '1': printf("%d\n", f[n][1]); break;
		case '2': puts("0"); break;
	}
}
