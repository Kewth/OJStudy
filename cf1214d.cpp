#if 0
2019.09.05

设 a[x][y] 表示起点到 (x, y) 的路径数， b[x][y] 表示 (x, y) 到中点的路径数。
那么 a[x][y] * b[x][y] 即经过 (x, y) 的合法路径数。

统计 a[x][y] * b[x][y] = a[n][m] 的 (x, y) 数量（不包括起点终点），
这样的 (x, y) 是路径的必经之路。
如果起点无法到达终点，答案为 0 ，否则：
如果存在这样的点，那么答案为 1，否则答案为 2 （最多放两个就能堵住起点）。

但是 a, b 的大小远超过 long long ，需要 hash ，在 cf 上用 hash 是真的操蛋，
嗯，三个随机模数，卡我先去做 Hash killer 3 吧。
#endif
#include <cstdio>
#include <algorithm>
#include <ctime>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 2000005;
const int shit = 3;
bool ok[maxn << 1];
char map[maxn << 1];
lolong a[shit][maxn << 1], b[shit][maxn << 1];
int mod[shit];

int main() {
	int n = input(), m = input(), k = m + 2;

	for(int i = 1; i <= n; i ++)
		scanf("%s", map + i * k + 1);

	srand(unsigned(time(0)));
	for(int s = 0; s < shit; s ++)
		mod[s] = 1000000000 + (rand() % 1000000000);

	map[1 * k + 1] = '#';
	for(int s = 0; s < shit; s ++) {
		a[s][1 * k + 1] = 1;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				if(map[i * k + j] == '.')
					a[s][i * k + j] =
						(a[s][(i - 1) * k + j] + a[s][i * k + j - 1]) % mod[s];
	}
	map[1 * k + 1] = '.';

	map[n * k + m] = '#';
	for(int s = 0; s < shit; s ++) {
		b[s][n * k + m] = 1;
		for(int i = n; i; i --)
			for(int j = m; j; j --)
				if(map[i * k + j] == '.')
					b[s][i * k + j] =
						(b[s][(i + 1) * k + j] + b[s][i * k + j + 1]) % mod[s];
	}
	map[n * k + m] = '.';

	int zero = 0;
	for(int s = 0; s < shit; s ++) {
		zero += (a[s][n * k + m] == 0);
		zero += (b[s][1 * k + 1] == 0);
	}
	if(zero == shit * 2) {
		puts("0");
		return 0;
	}


	int tot = -2;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++) {
			int fuck = 0;
			for(int s = 0; s < shit; s ++)
				if(a[s][i * k + j] * b[s][i * k + j] % mod[s] == a[s][n * k + m])
					fuck ++;
			if(fuck == shit)
				tot ++;
		}

#if 0
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++)
			debug(" %lld", a[i * k + j]);
		debug("\n");
	}
	debug("\n");

	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++)
			debug(" %lld", b[i * k + j]);
		debug("\n");
	}
	debug("\n");

	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++)
			debug(" %lld", a[i * k + j] * b[i * k + j]);
		debug("\n");
	}
	debug("\n");
#endif

	if(tot)
		puts("1");
	else
		puts("2");
}
