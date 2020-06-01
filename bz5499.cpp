#if 0
2020.06.01

  考虑对于每个子树 u 求出最优的段集合，由于两个子树之间互不影响，加入一个子树 v 的时候，
逐个把 v 的集合第 k 大值放进当前集合的第 k 值内，如果不足则新添，最后加入 u 自己，u 必须
单独占一个位置，用堆维护，复杂度 O(n^2 logn) 。
  类似启发式合并，注意到加入一个子树的时候操作的两个堆交换不会影响操作后的堆，因此把较小
的堆执行操作放入较大的堆即可。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔   CopyRight :)
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 200005;
int val[maxn];
std::priority_queue<int> q[maxn];
std::vector<int> G[maxn];

void dfs (int u) {
	for (int v : G[u]) {
		dfs(v);
		if (q[v].size() > q[u].size())
			std::swap(q[u], q[v]); // XXX: C++11 only
		std::vector<int> tmp;
		while (!q[v].empty()) {
			tmp.push_back(std::max(q[u].top(), q[v].top()));
			q[u].pop();
			q[v].pop();
		}
		for (int x : tmp)
			q[u].push(x);
	}
	q[u].push(val[u]);
}

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) read(val[i]);
	for (int i = 2; i <= n; i ++) G[read].push_back(i);
	dfs(1);
	ll ans = 0;
	while (!q[1].empty())
		ans += q[1].top(), q[1].pop();
	printf("%lld\n", ans);
}
