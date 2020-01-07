#if 0
2020.01.05

考虑一个 5 个点构成的集合（简称 5-set ），有三种情况：
1) 凸包是五边形，那么这个 5-set 不可能是一个四边形内部一个点
2) 凸包是四边形，那么这个 5-set 只可能是凸包作为四边形取包含里面那个点
3) 凸包是三角l形，那么这个 5-set 可以选出两个四边形来分别包含凸包内的两个点
记上面三种 5-set 的个数分别为 x5, x4, x3 ，那么答案就是 x4 + 2 x3 。

分别统计 x4, x3 没思路了，出题人给出了一个惊为天人的做法。

容易知道 X = x5 + x4 + x3 = C(n, 5) ，设 Y = 5 x5 + 4 x4 + 3 x3 ，
那么答案 ans = 5X - Y ，问题转换为求 Y 。
这个 Y 的形式非常优美，就是每个 5-set 的凸包的边数的和。
枚举每条边 E ，考虑它在多少个 5-set 中作为凸包，那么 E 已经可以确定两个点，
就是考虑有多少 3-set 全部在 E 的一端，假设 E 的一端有 k 个点，
那么这一端的贡献就是 C(k, 3) ，而统计一条边一端的点数是很容易的，
只需要枚举一个顶点 x 然后对于 x 引出的每条边极角排序，
按极角序枚举每条边的同时维护一端即可，复杂度 O(n^2logn) 。

dnmd 卡精度还卡常，不能使用 atan2 以及 double 甚至 long double 运算。
需要用向量叉积代替极角。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 2505;
int x[maxn], y[maxn];
struct Vec {
	int x, y;
};
Vec v[maxn << 1];

ll cross(Vec a, Vec b) {
	return 1ll * a.x * b.y - 1ll * a.y * b.x;
}

inline ll C(ll n, int m) {
	ll res = 1;
	for(int i = 0; i < m; i ++) (res *= n - i) /= i + 1;
	return res;
}

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		read(x[i], y[i]);

	ll X = C(n, 5), Y = 0;
	for(int i = 1; i <= n; i ++) {
		int vp = 0;
		for(int j = 1; j <= n; j ++)
			if(j != i)
				v[++ vp] = Vec({x[j] - x[i], y[j] - y[i]});
		std::sort(v + 1, v + vp + 1, [](Vec a, Vec b) {
					int ain = a.y < 0 or (a.x > 0 and a.y == 0);
					int bin = b.y < 0 or (b.x > 0 and b.y == 0);
					if(ain != bin) return ain < bin;
					return cross(a, b) > 0;
				});

		for(int j = 1; j <= vp; j ++)
			v[vp + j] = v[j];

		int las = 1;
		for(int j = vp + 1; j <= (vp << 1); j ++) {
			while(las + vp <= j or cross(v[j], v[las]) > 0) ++ las;
			Y += C(j - las, 3);
		}
	}

	printf("%lld\n", X * 5 - Y);
}
