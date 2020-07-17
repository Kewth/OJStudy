/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.16

 * Solution:
  最大密度子图模板，分数规划 + 最大权闭合子图。

 * Digression:
  奇葩的是竟然不是输出密度而是输出最大点数，那么就是要在最小割中求一组方案，最小割的一组
方案可以由最后一次 bfs 分层的被成功分层的点的集合给出。但这并不能保证求出来的是最大点数，
此题一个显然的 hack 是 "4 0" ，数据傻逼，事实上应该在残量网络上从汇点开始搜。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 100, maxm = 1000, maxd = maxn + maxm + 2, maxe = maxm * 3 + maxn;
const double eps = 1e-8;
int mx[maxm + 5], my[maxm + 5];
int head[maxd + 5], nxt[maxe * 2 + 5], to[maxe * 2 + 5], hp;
double cap[maxe * 2 + 5];
int cur[maxd + 5], level[maxd + 5];
int isans[maxn + 5];

inline void add (int u, int v, double c) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	cap[hp] = c;
	if (!(hp & 1)) add(v, u, 0);
}

bool bfs (int s, int t) {
	std::fill(level, level + t + 1, 0);
	std::queue<int> q;
	level[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; i; i = nxt[i])
			if (cap[i] > eps and !level[to[i]]) {
				level[to[i]] = level[u] + 1;
				q.push(to[i]);
			}
	}
	return level[t];
}

double dfs (int u, int t, double f) {
	if (u == t) return f;
	for (int &i = cur[u]; i; i = nxt[i])
		if (cap[i] > eps and level[to[i]] == level[u] + 1) {
			double nf = dfs(to[i], t, std::min(f, cap[i]));
			if (nf > eps) {
				cap[i] -= nf;
				cap[i ^ 1] += nf;
				return nf;
			}
		}
	return 0;
}

bool check (int n, int m, double X) {
	int S = n + m + 1, T = n + m + 2;
	hp = 1;
	std::fill(head, head + T + 1, 0);
	for (int i = 1; i <= n; i ++)
		add(i, T, X);
	for (int i = 1; i <= m; i ++) {
		add(S, n + i, 1);
		add(n + i, mx[i], HUGE_VAL);
		add(n + i, my[i], HUGE_VAL);
	}
	double sum = m;
	while (bfs(S, T)) {
		std::copy(head, head + T + 1, cur);
		double f = 0;
		do {
			f = dfs(S, T, HUGE_VAL);
			sum -= f;
		} while (f > eps);
	}
	return sum > eps;
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= m; i ++) read(mx[i], my[i]);
	double l = 0, r = m;
	for (int k = 0; k < 64; k ++) {
		double mid = (l + r) / 2;
		if (check(n, m, mid)) l = mid;
		else r = mid;
	}
	check(n, m, l - eps);
	for (int i = 1; i <= m; i ++)
		if (level[n + i])
			/* debug("%d %d\n", mx[i], my[i]), */
			isans[mx[i]] = isans[my[i]] = 1;
	int ans = 0;
	for (int i = 1; i <= n; i ++)
		if (isans[i])
			++ ans;
	printf("%d\n", std::max(1, ans));
}
