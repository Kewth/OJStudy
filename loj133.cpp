#if 0
2019.09.05

二维树状数组模板。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x = -1; scanf("%d", &x); return x; }

const int maxn = 1 << 13;
lolong bit[maxn][maxn];

void add(int x, int y, int v) {
	for(int k1 = x; k1 < maxn; k1 += k1 & -k1)
		for(int k2 = y; k2 < maxn; k2 += k2 & -k2)
			bit[k1][k2] += v;
}

lolong query(int x, int y) {
	lolong res = 0;
	for(int k1 = x; k1; k1 -= k1 & -k1)
		for(int k2 = y; k2; k2 -= k2 & -k2)
			res += bit[k1][k2];
	return res;
}

inline lolong calc(int x1, int y1, int x2, int y2) {
	return query(x2, y2) - query(x1 - 1, y2) -
		query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
}

int main() {
	int n = input(), m = input();

	while(true) {
		int typ = input();
		if(typ == -1)
			break;
		if(typ == 1) {
			int x = input(), y = input(), w = input();
			add(x, y, w);
		} else if(typ == 2) {
			int x1 = input(), y1 = input(), x2 = input(), y2 = input();
			printf("%lld\n", calc(x1, y1, x2, y2));
		}

		/* debug("%lld\n", calc(1, 1, n, m)); */
	}
}
