#if 0
2020.02.22

交换两个相同数是没用的，而交换两个不同数逆序对变化恰好为 1 。
因此只要合法，答案就是当前逆序对数与期望逆序对数的差。
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
char s[maxn];

int main() {
	int q = read;
	while(q --) {
		int n = read, m = read;
		scanf("%s", s + 1);

		int D = 0, M = 0;
		ll now = 0;
		for(int i = 1; i <= n; i ++)
			if(s[i] == 'D') ++ D;
			else now += D, ++ M;

		if(m > 1ll * D * M) {
			puts("-1");
			continue;
		}
		printf("%lld\n", std::abs(now - m));
	}
}
