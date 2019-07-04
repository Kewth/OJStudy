#if 0
2019.07.04

又是靠看代码搞懂的题。。。
先求出所有白点在黑点连线两边的方案（枚举两个黑点，统计两边的白点），
那么其中计算了在黑点凹的情况，考虑如何求出黑点凹且白点在两边的方案减去。

枚举黑点，求出所有以该点为起点的黑黑向量和黑白向量，按角度排序。
枚举黑黑向量，其角度为 a ，
考虑求出有多少对角度为 b, c 的黑白向量满足：
1) b 在 a 到 a + PI 之间，c 在 a + PI 到 a 之间。
2) c 在 b 到 b + PI 之间。
这样的 b, c 即构成一个黑点凹白点在两边的四边形。

预处理黑白向量的数量前缀和，
以及黑黑向量 a 到 a + PI 的最靠近 a + PI 的向量 d ，
就可以得到 a 到 a + PI 以及 a + PI 到 a 之间有多少黑白向量，
假设再枚举每个黑白向量 b ，那么其贡献就是 a + PI 到 b + PI 之间的黑白向量数，
即 0 到 b + PI 之间的减去 0 到 a + PI 之间的黑白向量数。
即上述前缀和的差值。
那么所有 b 的贡献和就是该前缀和的前缀和的差值。
#endif
#include <cstdio>
#include <cmath>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

struct Dot {
	int x, y;
};
struct Vector {
	double a;
	bool wb;
	bool fuck_memory[7];
};

const int maxn = 404;
Dot w[maxn], b[maxn];
Vector v[maxn * maxn << 1];
lolong s[maxn * maxn << 1];
lolong ss[maxn * maxn << 1];
lolong to[maxn * maxn << 1];

inline bool cmp(Vector x, Vector y) {
	return x.a < y.a;
}

lolong solve(int n) {
	int N = n << 1;
	for(int i = 1; i <= n; i ++) {
		if(v[i].a < 0)
			v[i].a += M_PI * 2;
		v[n + i].a = v[i].a + M_PI * 2;
		v[n + i].wb = v[i].wb;
	}
	std::sort(v + 1, v + N + 1, cmp);
	/* for(int i = 1; i <= N; i ++) */
	/* 	debug("%.2lf ", v[i].a); */
	/* debug("\n"); */
	for(int i = 1; i <= N; i ++)
		s[i] = s[i - 1] + v[i].wb;
	for(int i = 1; i <= N; i ++) {
		to[i] = to[i - 1];
		while(to[i] + 1 <= N and v[to[i] + 1].a <= v[i].a + M_PI)
			to[i] ++;
		ss[i] = ss[i - 1] + s[to[i]] * v[i].wb;
	}
	/* for(int i = 1; i <= N; i ++) */
	/* 	debug("%lld ", to[i]); */
	/* debug("\n"); */
	/* for(int i = 1; i <= N; i ++) */
	/* 	debug("%lld ", s[i]); */
	/* debug("\n"); */
	/* for(int i = 1; i <= N; i ++) */
	/* 	debug("%lld ", ss[i]); */
	/* debug("\n"); */
	lolong res = 0;
	for(int i = 1; i <= n; i ++)
		if(not v[i].wb) {
			if(v[i].a < M_PI)
				res += (s[to[i]] - s[i]) * (s[n] - s[to[i]] + s[i]);
			res -= (ss[to[i]] - ss[i]) - (s[to[i]] - s[i]) * s[to[i]];
		}
	return res;
}

int main() {
	int n = input(), m = input();
	for(int i = 1; i <= n; i ++) {
		b[i].x = input();
		b[i].y = input();
	}
	for(int i = 1; i <= m; i ++) {
		w[i].x = input();
		w[i].y = input();
	}
	lolong ans = 0;
	for(int i = 1; i <= n; i ++) {
		int p = 0;
		for(int j = 1; j <= n; j ++)
			if(i != j) {
				p ++;
				v[p].a = atan2(b[j].y - b[i].y, b[j].x - b[i].x);
				v[p].wb = false;
			}
		for(int j = 1; j <= m; j ++) {
			p ++;
			v[p].a = atan2(w[j].y - b[i].y, w[j].x - b[i].x);
			v[p].wb = true;
		}
		ans += solve(p);
	}
	printf("%lld\n", ans);
}
