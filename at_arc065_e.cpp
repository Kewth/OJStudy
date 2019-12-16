#if 0
2019.12.15

首先曼哈顿转切比雪夫，然后考虑计算有序二元组，算出来除以二就是答案。

二元组两个点的切比雪夫距离 d 是确定的，
考虑对于每个可能的点 u ，找出与之距离为 d 的所有点 v ，
如果 (a, b) 能到 (u, ~) ，那么就也能到 (u, v) 。
bfs 找出每个可能 u 即可。

期间用 set 和 vector 维护每一列每一行的所有点。
set 维护有哪些点还没有被 bfs 到，vector 维护有哪些点。
对于点 u ，与之距离为 d 的点在一个矩形上，在对应的 vector 中二分出有多少可行的 v 贡献答案，
在对应的 set 中找出范围内剩下的 v 并加入 bfs 队列中，同时删掉已经入队的 v 。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> Par;
typedef std::set<Par>::iterator iter;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 200005;
int tmp[maxn], tp;
int px[maxn], py[maxn];
struct Shit {
	std::set<Par> s;
	std::vector<Par> v;
};
Shit sx[maxn], sy[maxn];

inline int sc(int x) {
	int res = int(std::lower_bound(tmp + 1, tmp + tp + 1, x) - tmp);
	return tmp[res] == x ? res : 0;
}

int main() {
	int n = read, a = read, b = read;

	for(int i = 1; i <= n; i ++) {
		int x = read, y = read;
		tmp[++ tp] = px[i] = x + y;
		tmp[++ tp] = py[i] = x - y;
	}

	int d = std::max(std::abs(px[a] - px[b]), std::abs(py[a] - py[b]));

	std::sort(tmp + 1, tmp + tp + 1);

	for(int i = 1; i <= n; i ++) {
		sx[sc(px[i])].s.insert(Par(py[i], i));
		sy[sc(py[i])].s.insert(Par(px[i], i));
		sx[sc(px[i])].v.push_back(Par(py[i], i));
		sy[sc(py[i])].v.push_back(Par(px[i], i));
	}

	for(int i = 1; i <= tp; i ++) {
		std::sort(sx[i].v.begin(), sx[i].v.end());
		std::sort(sy[i].v.begin(), sy[i].v.end());
	}

	ll ans = 0;
	std::queue<int> q;
	q.push(a);
	sx[sc(px[a])].s.erase(Par(py[a], a));
	sy[sc(py[a])].s.erase(Par(px[a], a));

	while(!q.empty()) {
		int u = q.front();
		q.pop();

		/* debug("bfs %d\n", u); */

		auto search = [&](Shit &s, int l, int r) {
			/* debug(" s\n"); */

			auto lit = std::lower_bound(s.v.begin(), s.v.end(), Par(l, 0));
			auto rit = std::lower_bound(s.v.begin(), s.v.end(), Par(r + 1, 0));
			ans += rit - lit;

			for(iter it = s.s.lower_bound(Par(l, 0));
					it != s.s.end() and it -> first <= r;) {

				/* debug("%d, %d\n", u, v); */
				int v = it -> second;
				q.push(v);
				++ it;

				sx[sc(px[v])].s.erase(Par(py[v], v));
				sy[sc(py[v])].s.erase(Par(px[v], v));
			}
		};


		int lx = px[u] - d, rx = px[u] + d;
		int ly = py[u] - d, ry = py[u] + d;

		search(sx[sc(lx)], ly, ry - 1);
		search(sx[sc(rx)], ly + 1, ry);
		search(sy[sc(ly)], lx + 1, rx);
		search(sy[sc(ry)], lx, rx - 1);
	}

	printf("%lld\n", ans >> 1);
}
