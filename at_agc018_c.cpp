#if 0
2019.12.25

首先默认将三元组 (a, b, c) 替换为二元组 (e=b-a, f=c-a) （先默认所有人拿金币）。
然后问题转换为在 n 个二元组中选 y 个获得 e 收益，选 z 个获得 f 收益，最大化总收益。
对于两个二元组 (e[i], f[i]), (e[j], f[j]) 假设 i 选 f 且 j 选 e ，
考虑什么时候交换他们的选择收益不会变少，也就是 e[i] + f[j] >= e[j] + f[i] ，
移项得 e[i] - f[i] >= e[j] - f[j] ，那么通过排序使得二元组按 e - f 单调不降，
就有对于任意 i < j ，如果 i 选 f 且 j 选 e ，那么交换两者状态一定不会变差。
换言之，存在最优解满足选 e 的全在选 f 的左边，
也就是说存在一个 k 使得有最优解在 1 到 k 中取 y 个 e 在 k + 1 到 n 中取 z 个 f 。
那么只需要通过优先队列预处理出每个前缀前 y 大的 e 的和以及每个后缀前 z 大的 f 的和。
然后枚举 k 即可得出答案。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005;
struct obj {
	int a, b;
};
obj ob[maxn];
ll lget[maxn], rget[maxn];

int main() {
	int x = read, y = read, z = read;

	int n = x + y + z;
	ll ans = 0;
	for(int i = 1; i <= n; i ++) {
		int v = read;
		ans += v;
		ob[i].a = read - v;
		ob[i].b = read - v;
	}

	std::sort(ob + 1, ob + n + 1, [](obj x, obj y) {
				return x.a - x.b > y.a - y.b;
			});

	/* debug("%lld\n", ans); */
	/* for(int i = 1; i <= n; i ++) */
	/* 	debug("%d %d\n", ob[i].a, ob[i].b); */

	std::priority_queue<int, std::vector<int>, std::greater<int> > biggest;

	for(int i = 1; i <= n; i ++) {
		lget[i] = lget[i - 1] + ob[i].a;
		biggest.push(ob[i].a);
		if(int(biggest.size()) > y) {
			lget[i] -= biggest.top();
			biggest.pop();
		}
	}

	while(!biggest.empty()) biggest.pop();
	for(int i = n; i; i --) {
		rget[i] = rget[i + 1] + ob[i].b;
		biggest.push(ob[i].b);
		if(int(biggest.size()) > z) {
			rget[i] -= biggest.top();
			biggest.pop();
		}
	}

	/* for(int i = 1; i <= n; i ++) */
	/* 	debug("l=%lld r=%lld\n", lget[i], rget[i]); */

	ll max = - 1000000000000000000;
	for(int k = y; k <= n - z; k ++)
		max = std::max(max, lget[k] + rget[k + 1]);

	printf("%lld\n", ans + max);
}
