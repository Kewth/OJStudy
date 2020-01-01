#if 0
2019.08.07

如果没有不重叠的限制，fail 树上的深度就是答案。
对于这个限制，考虑维护 ffail[i] 表示 i 跳 fail 跳到的第一个合法节点。
辛运的是 ffail 可以和 fail 一样类似求出，求出后跳 ffail 记 fail 树深度即可。
#endif
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1000005, mod = 1000000007;
char s[maxn];
int fail[maxn], ffail[maxn], deep[maxn];

int main() {
	int T = input();
	while(T --) {
		scanf("%s", s + 1);
		int n = strlen(s + 1);
		fail[0] = -1;
		ffail[0] = -1;
		for(int i = 0; i < n; i ++) {
			int j = fail[i];
			while(~j and s[j + 1] != s[i + 1])
				j = fail[j];
			fail[i + 1] = j + 1;
			deep[i + 1] = deep[j + 1] + 1;
			j = ffail[i];
			while((~j and s[j + 1] != s[i + 1]) or j + 1 > (i + 1) / 2)
				j = fail[j];
			ffail[i + 1] = j + 1;
			// debug("%d -> %d\n", i + 1, j + 1);
		}
		int ans = 1;
		for(int i = 1; i <= n; i ++)
			// debug("%d : %d\n", i, deep[i]),
			ans = 1ll * ans * (deep[ffail[i]] + 1) % mod;
		printf("%d\n", ans);
	}
}
