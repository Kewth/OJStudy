#if 0
2019.11.07

动态 DP ，设 f[u] 表示选 u 时 u 子树的代价，g[u] 表示不选 u 时 u 子树的代价。
询问两个点的时候，把钦定必选的点权值设为 0 ，钦定不选的点权值设为 INF 即可。
似乎本题的矩阵不能直接用两个 (f, g) 代替，这样没有结合律。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const lolong inf = 1000000000000000000;
struct Mar {
	lolong a[2][2];
	Mar(lolong a00 = 0, lolong a01 = inf, lolong a10 = inf, lolong a11 = 0) {
		a[0][0] = a00;
		a[0][1] = a01;
		a[1][0] = a10;
		a[1][1] = a11;
	}
} init(0, 0, 0, 0);
inline Mar operator * (Mar u, Mar v) {
	Mar res(inf, inf, inf, inf);
	for(int i = 0; i < 2; i ++)
		for(int j = 0; j < 2; j ++)
			for(int k = 0; k < 2; k ++)
				res.a[i][j] = std::min(res.a[i][j],
						u.a[i][k] + v.a[k][j]);
	return res;
}

struct GBTree {
	int lti, rti, fai, fuck;
	Mar val, mul;
};
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]
#define fa pool[self.fai]

const int maxn = 100005;
GBTree pool[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp = 1;
int size[maxn], son[maxn];
lolong val[maxn];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

void dfs(int u, int f) {
	size[u] = 1;
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != f) {
			dfs(to[i], u);
			if(size[to[i]] > size[son[u]])
				son[u] = to[i];
			size[u] += size[to[i]];
		}
}


inline void update(int now) {
	if(self.lti)
		self.mul = lt.mul * self.val * rt.mul;
	else
		self.mul = self.val * rt.mul;
}

inline void add(int u, int now, int t) {
	Mar dp = self.mul * init;
	now = u;
	self.val.a[0][0] += std::min(dp.a[0][0], dp.a[1][0]) * t;
	self.val.a[0][1] += std::min(dp.a[0][0], dp.a[1][0]) * t;
	self.val.a[1][0] += dp.a[0][0] * t;
}

int tmp[maxn];
int sbuild(int l, int r) {
	lolong sum = 0;
	for(int i = l; i <= r; i ++)
		sum += size[tmp[i]] - size[son[tmp[i]]];
	lolong nowsum = 0;
	for(int i = l; i <= r; i ++) {
		nowsum += size[tmp[i]] - size[son[tmp[i]]];
		if((nowsum << 1) >= sum) {
			int now = tmp[i];
			self.lti = sbuild(l, i - 1);
			self.rti = sbuild(i + 1, r);
			lt.fai = rt.fai = now;
			update(now);
			return now;
		}
	}
	return 0;
}

int build(int p) {
	for(int u = p; u; u = son[u])
		for(int i = head[u]; i; i = nxt[i])
			if(size[to[i]] < size[u] and to[i] != son[u]) {
				int now = build(to[i]);
				self.fai = u;
				add(u, now, 1);
			}
	int tp = 0;
	for(int u = p; u; u = son[u])
		tmp[++ tp] = u;
	return sbuild(1, tp);
}

void modify(int now, lolong x) {
	self.val.a[0][0] += x - val[now];
	self.val.a[0][1] += x - val[now];
	val[now] = x;
	while(now) {
		if(self.fai and fa.lti != now and fa.rti != now) {
			add(self.fai, now, -1);
			update(now);
			add(self.fai, now, 1);
		} else
			update(now);
		now = self.fai;
	}
}

int main() {
	int n = input(), q = input();

	for(int now = 1; now <= n; now ++) {
		val[now] = input();
		self.val = Mar(val[now], val[now], 0, inf);
	}

	for(int i = 1; i < n; i ++) {
		int u = input(), v = input();
		add(u, v);
		add(v, u);
	}

	dfs(1, 0);
	int now = build(1);

/* 	for(int now = 1; now <= n; now ++) */
/* 		debug("%d : %d %d %d (%lld %lld %lld %lld) (%lld %lld %lld %lld)\n", */
/* 				now, self.lti, self.rti, self.fai, */
/* 				self.val.a[0][0], self.val.a[0][1], self.val.a[1][0], self.val.a[1][1], */
/* 				self.mul.a[0][0], self.mul.a[0][1], self.mul.a[1][0], self.mul.a[1][1]); */
/* 	debug("\n"); */

	while(q --) {
		int a = input(), x = input(), b = input(), y = input();
		lolong vala = val[a], valb = val[b];
		lolong ans = x * vala + y * valb;

		modify(a, x ? 0 : inf);
		modify(b, y ? 0 : inf);

		Mar dp = self.mul * init;
		ans += std::min(dp.a[0][0], dp.a[1][0]);
		if(ans >= (inf >> 1))
			puts("-1");
		else
			printf("%lld\n", ans);

		modify(a, vala);
		modify(b, valb);
	}
}
