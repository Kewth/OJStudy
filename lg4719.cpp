#if 0
2019.10.04

动态 DP 模板，采用 Global Biased tree ，简称狗比树，又名全局二叉平衡树。
简单来说就是在轻重链剖分的结构上用普通二叉树维护静态的 LCT 。
踩了一个坑，维护区间乘积的时候不能乘答案的初始矩阵。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

typedef int Mar[2][2];

struct GBTree {
	int fai;
	int lti, rti;
	Mar val, mul;
};
#define self pool[now]
#define fa pool[self.fai]
#define lt pool[self.lti]
#define rt pool[self.rti]

const int maxn = 100005, inf = 1000000000;
GBTree pool[maxn];
int son[maxn], size[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp = 1;
int val[maxn];

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

Mar out;
inline void Mul(Mar a, Mar b) {
	for(int i = 0; i < 2; i ++)
		for(int j = 0; j < 2; j ++) {
			out[i][j] = - inf;
			for(int k = 0; k < 2; k ++)
				out[i][j] = std::max(out[i][j], a[i][k] + b[k][j]);
		}
}

inline void copy(Mar &a, Mar b) {
	for(int i = 0; i < 2; i ++)
		for(int j = 0; j < 2; j ++)
			a[i][j] = b[i][j];
}

void update(int now) {
	copy(self.mul, lt.mul);
	Mul(self.mul, self.val);
	copy(self.mul, out);
	Mul(self.mul, rt.mul);
	copy(self.mul, out);
}

void getans(int now, int &f, int &g) {
	Mul(self.mul, pool[maxn - 1].val);
	f = out[0][0];
	g = out[1][0];
}

int tmp[maxn];
int sbuild(int l, int r) {
	int sum = 0;
	for(int i = l; i <= r; i ++)
		sum += size[tmp[i]] - size[son[tmp[i]]];
	int nowsum = 0;
	for(int i = l; i <= r; i ++) {
		int now = tmp[i];
		nowsum += size[now] - size[son[now]];
		if((nowsum << 1) >= sum) {
			self.lti = sbuild(l, i - 1);
			self.rti = sbuild(i + 1, r);
			lt.fai = rt.fai = now;
			update(now);
			return now;
		}
	}
	return 0;
}

void add(int u, int now, int t) {
	int f, g;
	getans(now, f, g);
	now = u;
	self.val[0][1] += g * t;
	self.val[1][0] += std::max(f, g) * t;
	self.val[1][1] += std::max(f, g) * t;
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
	self.val[0][1] -= val[now];
	val[now] = x;
	self.val[0][1] += val[now];

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
		self.val[0][0] = - inf;
		self.val[0][1] = val[now];
		self.val[1][0] = 0;
		self.val[1][1] = 0;
	}

	for(int i = 1; i < n; i ++) {
		int u = input(), v = input();
		add(u, v);
		add(v, u);
	}

	int now = 0;
	self.mul[0][1] = self.mul[1][0] = - inf;
	dfs(1, 0);
	now = build(1);

	/* for(int now = 1; now <= n; now ++) */
	/* 	debug("%d : %d %d %d (%d %d %d %d) (%d %d %d %d)\n", */
	/* 			now, self.lti, self.rti, self.fai, */
	/* 			self.val[0][0], self.val[0][1], self.val[1][0], self.val[1][1], */
	/* 			self.mul[0][0], self.mul[0][1], self.mul[1][0], self.mul[1][1]); */
	/* debug("\n"); */

	while(q --) {
		int u = input(), x = input();
		modify(u, x);
		int f, g;
		getans(now, f, g);
		printf("%d\n", std::max(f, g));

		/* for(int now = 1; now <= n; now ++) */
		/* 	debug("%d : %d %d %d (%d %d %d %d) (%d %d %d %d)\n", */
		/* 			now, self.lti, self.rti, self.fai, */
		/* 			self.val[0][0], self.val[0][1], self.val[1][0], self.val[1][1], */
		/* 			self.mul[0][0], self.mul[0][1], self.mul[1][0], self.mul[1][1]); */
		/* debug("\n"); */
	}
}
