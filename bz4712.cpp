#if 0
2019.10.05

动态 DP ，特别的是这里查询的是一颗子树。
Global Biased Tree 上查询 u 的子树的 DP 状态的话，
就相当于要查 u 所在重链从 u 向下的矩阵乘积，
也就是要查 u 所在 BST 的键值不小于 u 的点的乘积，
直接在 BST 上一边跳 father 一边维护乘积即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const lolong inf = 1000000000000000000;
struct DP { // 本质上是一个矩阵，因为封闭性可以压缩成两个值。
	lolong f, g;
	DP(lolong f = 0, lolong g = inf): f(f), g(g) { }
};
inline DP operator * (DP x, DP y) {
	return DP(x.f + y.f, std::min(x.g, x.f + y.g));
}

struct GBTree {
	int fai;
	int lti, rti;
	int fuck;
	DP val, mul;
};
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]
#define fa pool[self.fai]

const int maxn = 200005;
GBTree pool[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp = 1;
int size[maxn], son[maxn];
DP init(inf, inf);

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
	self.mul = lt.mul * self.val * rt.mul;
}

void add(int u, int now, int t) {
	DP dp = self.mul * init;
	now = u;
	self.val.f += dp.g * t;
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

void modify(int now, int x) {
	self.val.g += x;
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

lolong query(int now) {
	DP dp;
	int last = self.lti;
	while(1) {
		if(self.lti == last)
			dp = dp * self.val * rt.mul;
		if(fa.lti != now and fa.rti != now)
			break;
		last = now;
		now = self.fai;
	}
	dp = dp * init;
	return dp.g;
}

int main() {
	int n = input();

	for(int now = 1; now <= n; now ++) {
		self.val.f = 0;
		self.val.g = input();
	}

	for(int i = 1; i < n; i ++) {
		int u = input(), v = input();
		add(u, v);
		add(v, u);
	}

	dfs(1, 0);
	build(1);

	/* for(int now = 1; now <= n; now ++) */
	/* 	debug("%d : %d %d %d (%lld %lld) (%lld %lld)\n", */
	/* 			now, self.lti, self.rti, self.fai, */
	/* 			self.val.f, self.val.g, */
	/* 			self.mul.f, self.mul.g); */
	/* debug("\n"); */

	int q = input();
	while(q --) {
		int c = getchar();
		while(c != 'Q' and c != 'C') c = getchar();
		if(c == 'Q')
			printf("%lld\n", query(input()));
		else {
			int u = input();
			modify(u, input());
		}

		/* for(int now = 1; now <= n; now ++) */
		/* 	debug("%d : %d %d %d (%lld %lld) (%lld %lld)\n", */
		/* 			now, self.lti, self.rti, self.fai, */
		/* 			self.val.f, self.val.g, */
		/* 			self.mul.f, self.mul.g); */
		/* debug("\n"); */
	}
}
