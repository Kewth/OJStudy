#if 0
2020.02.22

问题就是每次在剩下的点中找到当前点的下两个点，用链表存点即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 1000005;
int a[maxn];
int nxt[maxn];

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		nxt[i] = i + 1;
	nxt[n] = 1;

	int pre = n, now = 1, p = 0;
	while(p < n) {
		a[now] = ++ p;
		nxt[pre] = nxt[now];
		pre = nxt[now];
		now = nxt[nxt[now]];
	}

	for(int i = 1; i <= n; i ++)
		printf("%d ", a[i]);
	puts("");
}
