#if 0
2020.03.13

设 k = n - m ，相当于搬运前可以进行 k 次操作，每次操作把一个数拆成两个。
序列中的一个数根据使用的总的操作次数可以抽象为泛化背包。
用线段树维护所有背包的和即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 405;
ll seg[maxn << 2][maxn];
#define lt (now << 1)
#define rt (now << 1 | 1)

ll f[maxn];

int m;
void update(int now) {
	for(int i = 0; i <= m; i ++)
		seg[now][i] = 1000000000000000000;
	for(int i = 0; i <= m; i ++)
		for(int j = 0; i + j <= m; j ++)
			seg[now][i + j] = std::min(seg[now][i + j],
					seg[lt][i] + seg[rt][j]);
}

void modify(int now, int L, int R, int p, int x) {
	if(L == R) {
		for(int i = 0; i <= m; i ++) {
			int min = x / (i + 1);
			int b = x % (i + 1), a = i + 1 - b;
			seg[now][i] = 1ll * a * min * min +
				1ll * b * (min + 1) * (min + 1);
		}
		return;
	}
	int M = (L + R) >> 1;
	if(p <= M) modify(lt, L, M, p, x);
	else modify(rt, M + 1, R, p, x);
	update(now);
}

int main() {
	int n = read;
	m = read - n;
	for(int i = 1; i <= n; i ++)
		modify(1, 1, n, i, read);

	int q = read;
	while(q --) {
		int k = read, x = read;
		modify(1, 1, n, k, x);
		printf("%lld\n", seg[1][m]);
	}
}
