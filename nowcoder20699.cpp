#if 0
2020.02.23

DP 设 f[i][j][k] 表示考虑前 i 盏灯，已覆盖的右端点为 k 的最小左端点，
其中这个范围内有若干未覆盖的地方等着之后覆盖，这些位置中最小的为 j ，
如果 j = 0 表示区间内没有未覆盖的地方。
转移略。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 105;
struct Lamp {
	int m, l, r;
} la[maxn];
int pool[2][maxn << 2][maxn << 2];
int tmp[maxn << 2];

bool cmp(Lamp x, Lamp y) {
	return x.m < y.m;
}

inline void update(int &x, int y) {
	if(!x or y < x) x = y;
}

int main() {
	int n = read, p = 0;
	for(int i = 1; i <= n; i ++) {
		int m = read, len = read;
		la[i] = {m, m - len, m + len};
		tmp[++ p] = la[i].l;
		tmp[++ p] = la[i].m;
		tmp[++ p] = la[i].r;
	}

	std::sort(la + 1, la + n + 1, cmp);
	std::sort(tmp + 1, tmp + p + 1);

	auto f = pool[0], g = pool[1];
	for(int i = 1; i <= n; i ++) {
		int li = int(std::lower_bound(tmp + 1, tmp + p + 1, la[i].l) - tmp);
		int mi = int(std::lower_bound(tmp + 1, tmp + p + 1, la[i].m) - tmp);
		int ri = int(std::lower_bound(tmp + 1, tmp + p + 1, la[i].r) - tmp);

		for(int j = 0; j <= p; j ++)
			for(int k = j + 1; k <= p; k ++)
				g[j][k] = f[j][k];

		f[0][ri] = mi;
		f[0][mi] = li;

		for(int j = 0; j <= p; j ++)
			for(int k = j + 1; k <= p; k ++)
				if(g[j][k]) {
					int nj = j;
					if(mi > k) update(nj, k);
					update(f[nj][std::max(k, ri)], g[j][k]);

					nj = j;
					if(li > k) update(nj, k);
					if(li <= j) nj = 0;
					update(f[nj][std::max(k, mi)], g[j][k]);
					update(f[nj][std::max(k, mi)], li);
				}

#if 0
		debug("%d:\n", i);
		for(int j = 0; j <= p; j ++)
			for(int k = j + 1; k <= p; k ++)
				if(f[j][k] != g[j][k])
					debug("%d~%d, %d\n", tmp[f[j][k]], tmp[k], tmp[j]);
#endif
	}

	int ans = 0;
	for(int i = 1; i <= p; i ++)
		if(f[0][i])
			ans = std::max(ans, tmp[i] - tmp[f[0][i]]);
	printf("%d\n", ans);
}
