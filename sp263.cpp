#if 0
date

kmp 的 fail[] 有一个性质就是 x - fail[x] 是前缀 x 的最大循环节（不完整循环），
加上一些特判。
#endif
#include <cstdio>

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1000005;
char s[maxn];
int fail[maxn];

int main() {
	int T = input();
	for(int t = 1; t <= T; t ++) {
		int n = input();
		scanf("%s", s + 1);
		fail[0] = -1;
		for(int i = 0; i < n; i ++) {
			int j = fail[i];
			while(~ j and s[j + 1] != s[i + 1])
				j = fail[j];
			fail[i + 1] = j + 1;
		}
		printf("Test case #%d\n", t);
		for(int i = 1; i <= n; i ++) {
			int x = i - fail[i];
			if(not (i % x) and i != x)
				printf("%d %d\n", i, i / x);
		}
		puts("");
	}
}

