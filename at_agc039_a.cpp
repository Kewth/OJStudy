#if 0
2019.10.05

对于每段连续出现 k 次的字符都有 k / 2 的代价，
特殊判断首尾相连以及整个都一个字符的情况即可。
#endif
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 105;
char s[maxn];

int main() {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1));
	int k = input();

	if(s[1] != s[n]) {
		int l = 0;
		lolong ans = 0;
		for(int i = 1; i <= n; i ++) {
			if(s[i] != s[i - 1]) {
				ans += l >> 1;
				l = 0;
			}
			l ++;
		}
		ans += l >> 1;
		printf("%lld\n", ans * k);
	}

	else {
		int a = 0;
		int l = 0;
		lolong ans = 0;
		for(int i = 1; i <= n; i ++) {
			if(s[i] != s[i - 1]) {
				if(!a) a = l;
				else ans += l >> 1;
				l = 0;
			}
			l ++;
		}

		if(a) {
			ans += (a + l) >> 1;
			printf("%lld\n", ans * k - ((a + l) >> 1) + (a >> 1) + (l >> 1));
		}

		else {
			printf("%lld\n", 1ll * k * l >> 1);
		}
	}
}
