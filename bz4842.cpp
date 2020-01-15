#if 0
2020.01.15

要消圈的费用流都是 !@^(!@$#%&@#$%@#% 。

将一个长为 k 的连续段覆盖 n 个点这个关系换成用 n 个点覆盖 n - k + 1 个段。
强制选 S ，只考虑改 E ，那么每个段被覆盖的 E 的次数就有上界和下界。
而每个点去作为 E 覆盖若干段会有若干收益。
这是个经典的会有正环的最大费用可行流问题。

哪个消圈的费用流能跑 1000 啊。

不能直接增广，按收益从大到小贪心先去覆盖，跑增广路，然后在此基础上费用流增广。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 1005, maxm = 4005;
int head[maxn], nxt[maxm << 1], to[maxm << 1], cap[maxm << 1], cost[maxm << 1], hp = 1;

inline void add(int u, int v, int ca, int co) {
	if((hp & 1) and !ca) return;
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	cap[hp] = ca;
	cost[hp] = co;
	if(!(hp & 1)) add(v, u, 0, - co);
}

ll dis[maxn];
bool inq[maxn], vis[maxn];
int from[maxn], tot[maxn];
int spfa(int s, int t) {
	std::queue<int> q;
	std::fill(dis, dis + t + 1, - 1000000000000000000);
	std::fill(inq, inq + t + 1, 0);
	std::fill(tot, tot + t + 1, 0);
	dis[s] = 0;
	q.push(s);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = 0;
		vis[u] = 1;
		for(int i = head[u]; i; i = nxt[i])
			if(cap[i] and dis[u] + cost[i] > dis[to[i]]) {
				dis[to[i]] = dis[u] + cost[i];
				from[to[i]] = i ^ 1;
				if(!inq[to[i]]) {
					if(++ tot[to[i]] > t) return to[i];
					q.push(to[i]);
					inq[to[i]] = 1;
				}
			}
	}
	return dis[t] > - 1000000000000000000 ? -1 : 0;
}

bool fuck[maxn];
ll lupdate(int s, int x) {
	int flow = cap[from[x] ^ 1];
	ll sum = cost[from[x] ^ 1];
	for(int u = to[from[x]]; u != s; u = to[from[u]]) {
		flow = std::min(flow, cap[from[u] ^ 1]);
		sum += cost[from[u] ^ 1];
	}
	cap[from[x] ^ 1] -= flow;
	cap[from[x]] += flow;
	for(int u = to[from[x]]; u != s; u = to[from[u]]) {
		cap[from[u] ^ 1] -= flow;
		cap[from[u]] += flow;
	}
	return sum * flow;
}

ll update(int x, int n) {
	std::fill(fuck, fuck + n + 1, 0);
	while(!fuck[x]) {
		fuck[x] = 1;
		x = to[from[x]];
	}
	return lupdate(x, x);
}

ll mincostmaxflow(int s, int t) {
	ll res = 0;
	int get;
	while((get = spfa(s, t)))
		if(get == -1)
			res += lupdate(s, t);
		else
			res += update(get, t);
	for(int u = 1; u <= t; u ++)
		if(!vis[u])
			while((get = spfa(u, t)) > 0)
				res += update(get, t);
	return res;
}

int a[maxn], b[maxn], c[maxn];
par pr[maxn];
int main() {
	int n = read, k = read, min = read, max = k - read;
	for(int i = 1; i <= n; i ++)
		read(a[i]);
	ll ans = 0;
	for(int i = 1; i <= n; i ++) {
		int x = read;
		ans += x;
		a[i] -= x;
		pr[i] = par(a[i], i);
	}

	int s = n - k + 3, t = n - k + 4;
	for(int i = 1; i <= n - k + 1; i ++) {
		c[i] = max == min ? 0 : hp + 1;
		add(i, i + 1, max - min, 0);
		add(s, i + 1, min, 0);
		add(i, t, min, 0);
	}

	for(int i = 1; i <= n; i ++) {
		int l = std::max(1, i - k + 1);
		int r = std::min(n - k + 1, i);
		b[i] = hp + 1;
		add(r + 1, l, 1, a[i]);
	}

	std::sort(pr + 1, pr + n + 1);
	for(int i = n; i; i --)
		if(pr[i].first > 0) {
			int id = pr[i].second;
			int l = std::max(1, id - k + 1);
			int r = std::min(n - k + 1, id);
			for(int j = l; j <= r; j ++)
				if(!cap[c[j]])
					goto FAIL;
			for(int j = l; j <= r; j ++) {
				-- cap[c[j]];
				++ cap[c[j] ^ 1];
			}
			-- cap[b[id]];
			++ cap[b[id] ^ 1];
			ans += a[id];
FAIL:;
		}

	ans += mincostmaxflow(s, t);
	printf("%lld\n", ans);
	for(int i = 1; i <= n; i ++)
		if(cap[b[i]]) putchar('E');
		else putchar('S');
	puts("");
}
