#if 0
2020.02.01

设 g = gcd(n, m) ，那么模 g 不同余的任何两个点都永远不会被匹配到一起，
因此按模 g 的值将位置分成 g 类，转换为 g 的子问题。
如果存在一类位置不存在初始点，该类位置永远无法发生匹配，全局无解。
接下来的讨论认为 n, m 互质。

只考虑一边，n 个位置 (boy) 什么时候全部被覆盖，两边取最大值即可。
考虑最短路模型，建立源点 S ，对于每个初始点 k ，
连边 S -> k % n ，距离为 k 。
然后对于任意点 k 如果 k 被匹配，那么 m 天后，匹配它的对应点有又变回来了，
此时 (k + m) % n 也会被匹配，因此连边 k -> (k + m) % n ，距离为 m 。

跑单源最短路，求 dis 最大值，特别的，
对于 boy 的每个初始点 k ，其 dis 对最大值不应有贡献，
因为事实上该点在进行匹配前就已经被覆盖。

但数据范围不支持直接跑最短路，注意到这个图很特殊，
除了源点连的边外，其他边的长度都为 m ，且在模 n 意义下连边，
称这类边为同余边，事实上对于同余边 u -> v ，
如果 u 和 v 都不是初始点，那么 v 的入边唯一，
一定有 dis[v] = dis[u] + m ，因此 u 这个点可以直接删掉。
这样删掉所有没用的点，剩下的点是 O(n) 的。
换言之，对于初始点 u ，如果它走同余边到达的第一个初始点为 v ，
那么路径上经过的非初始点只需考虑最后一个。
唯一的问题是对于 u 求出这个 v 。

只需要选定最小的初始点 x ，用扩欧求出其到所有初始点需要经过的同余边数量，
然后将所有初始点按这个数量排序，
对于相邻两个初始点 u, v 而言，u 走同余边到达的第一个初始点就是 v ，
容易反证得到这个结论。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 100005;

int tmp1, tmp2;
int exgcd(int a, int b, int &x, int &y) {
	if(!b) {
		x = 1;
		y = 0;
		return a;
	}
	int g = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return g;
}

struct Shit {
	int frombegin, now, buff;
} shi[maxn << 1];
std::set<int> keyn[maxn << 1], keym[maxn << 1];

ll solve(int n, int m, int id) {
	std::map<int, int> dis;
	std::set<int> pos;
	for(int x : keyn[id]) {
		pos.insert(x);
		dis[x] = x;
	}
	for(int x : keym[id]) {
		pos.insert(x % n);
		// XXX: WTF? 这下面两个有啥区别？
		if(dis.count(x % n))
			dis[x % n] = std::min(dis[x % n], x);
		else
			dis[x % n] = x;
		// dis[x % n] = dis.count(x % n) ? std::min(dis[x % n], x) : x;
	}

	int x;
	exgcd(m, n, x, tmp2);
	x %= n;
	if(x < 0) x += n;

	int p = 0;
	for(int po : pos)
		shi[++ p] = {int(1ll * x * (po - *pos.begin()) % n),
			dis[po], int(keyn[id].count(po))};
	std::sort(shi + 1, shi + p + 1, [](Shit x, Shit y) {
				return x.frombegin < y.frombegin;
			});
	shi[p + 1] = {n, -1, -1};

	ll res = - 10000000000000;
	for(int i = 1; i <= p; i ++)
		if(!shi[i].buff or
				shi[i + 1].frombegin > shi[i].frombegin + 1)
		res = std::max(res, shi[i].now +
				1ll * (shi[i + 1].frombegin - shi[i].frombegin - 1) * m);

#if 0
	debug("fuck solve %d %d\n", n, m);
	for(int i = 1; i <= p + 1; i ++)
		debug("%d, %d, %d\n",
				shi[i].frombegin, shi[i].now, shi[i].buff);
	debug("res = %lld\n", res);
#endif
	return res;
}

int main() {
	int n = read, m = read;
	int g = exgcd(n, m, tmp1, tmp2);

	if(g > 200000) return puts("-1"), 0;

	for(int i = read; i; -- i) {
		int x = read;
		keyn[x % g].insert(x / g);
	}
	for(int i = read; i; -- i) {
		int x = read;
		keym[x % g].insert(x / g);
	}

	ll ans = 0;
	for(int i = 0; i < g; i ++) {
		if(keyn[i].empty() and keym[i].empty()) return puts("-1"), 0;
		ans = std::max(ans, solve(n / g, m / g, i) * g + i);
		std::swap(keyn[i], keym[i]);
		ans = std::max(ans, solve(m / g, n / g, i) * g + i);
	}

	printf("%lld\n", ans);
}
