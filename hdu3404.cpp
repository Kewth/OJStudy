#if 0
2020.03.14

Nim 积 + 翻棋子博弈的板子，两个维度的限制是独立的，
分别求出在两个维度上的 SG 值求 Nim 积即可。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

int f[30][30];
int nim(int x, int y) {
	int res = 0;
	for(int i = 0; i < 30; i ++)
		if(x >> i & 1)
			for(int j = 0; j < 30; j ++)
				if(y >> j & 1)
					res ^= f[i][j];
	return res;
}

int F(int x, int y) {
	int res = 1;
	for(int k = 0; k < 6; k ++) {
		int v = 1 << (1 << k);
		if((x & y) >> k & 1)
			res = res * v ^ nim(res, (v >> 1));
		if((x xor y) >> k & 1)
			res = res * v;
	}
	return res;
}

int main() {
	for(int i = 0; i < 30; i ++)
		for(int j = 0; j < 30; j ++)
			f[i][j] = F(i, j);

	int T = read;
	while(T --) {
		int n = read;
		int sg = 0;
		while(n --)
			sg ^= nim(read, read);
		if(sg) puts("Have a try, lxhgww.");
		else puts("Don't waste your time.");
	}
}
