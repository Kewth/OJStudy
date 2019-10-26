#if 0
2019.10.25
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 100005;
char s[maxn];

int main() {
	int n = input();
	scanf("%s", s + 1);
	int ans = 0;
	for(int i = 1; i <= n; i ++)
		ans += s[i] == 'G';
	printf("%d\n", ans);
}
