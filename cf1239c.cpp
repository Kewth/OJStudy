#if 0
2020.04.01

JB 题，细节有点多但是没啥意义。
用 set, priority_queue 等 STL 按时间顺序模拟即可，复杂度 O(nlogn) 。
#endif
#include <cstdio>
#include <algorithm>
#include <set>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 100005;

struct P {
	ll ti;
	int id, place_holder;
} pe[maxn];
bool operator < (P x, P y) {
	if (x.ti == y.ti) return x.id < y.id;
	return x.ti < y.ti;
};
bool operator > (P x, P y) {
	if (x.ti == y.ti) return x.id > y.id;
	return x.ti > y.ti;
};
ll ans[maxn];

int main () {
	int n = read, p = read;
	for (int i = 1; i <= n; i ++) pe[i] = {read, i, 0};
	std::sort(pe + 1, pe + n + 1);

	std::set<int> inque;
	std::set<int> wait;
	std::priority_queue<P, std::vector<P>, std::greater<P> > que;
	ll las = 0;

	for (int i = 1; i <= n; i ++) {
		while (!que.empty() and que.top().ti < pe[i].ti) {
			P tmp = que.top();
			inque.erase(tmp.id);
			que.pop();
			if (wait.upper_bound(tmp.id) != wait.end()) {
				int j = *wait.upper_bound(tmp.id);
				if (inque.upper_bound(j) == inque.begin()) {
					wait.erase(j);
					ans[j] = las = las + p;
					inque.insert(j);
					que.push({las, j, 0});
				}
			}
		}
		if (inque.upper_bound(pe[i].id) == inque.begin()) {
			/* debug("%d %d\n", pe[i].id, *inque.upper_bound(pe[i].id)); */
			ans[pe[i].id] = las = std::max(pe[i].ti, las) + p;
			inque.insert(pe[i].id);
			que.push({las, pe[i].id, 0});
		}
		else
			wait.insert(pe[i].id);
	}

	for (int i : wait)
		ans[i] = las = las + p;

	for (int i = 1; i <= n; i ++) printf("%lld ", ans[i]);
	puts("");
}
