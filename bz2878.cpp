#if 0
2019.09.06

设 down[u] 表示 u 点开始向下走的期望长度，up[u] 表示向上。
设 son[u] 表示 u 点向下走的点数， pa[u] 表示向上。
每个点对答案的贡献就是 (up[u] * pa[u] + down[u] * son[u]) / (pa[u] + son[u]) 。

假设是颗树，可以直接 DP ，并且根节点 pa[u] = 0 ，其他点 pa[u] = 1 。

如果有环，定义在环上走为向上，否则为向下，那么 down[u] 仍然是可以 DP 的，考虑求 up[u] 。

对于环上每一个点 root ，只要求出 up[root] ，就能 DP 出 root 的子树的所有 up[u] 。
此时 pa[root] = 2 ，枚举向上的两种走法（环的两边），
发现走出一步后，剩下的问题就变成了树。

由于环很小，每个 root 枚举向上走的方向 (root -> x) 后断掉 root 的边，
然后剩下的问题是以 x 为根的子树，
直接 DP 出此时的 down[x] （此时看做没有环，在环上走不一定算向上），
贡献到 up[root] 即可。
#endif
#include <cstdio>
#define debug(...) // fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005;
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], hp = 1;

inline void add(int u, int v, int w) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	val[hp] = w;
}

int stack[maxn], sp;
int du[maxn];

void sort(int n) {
	for(int i = 1; i <= n; i ++)
		if(du[i] == 1)
			stack[++ sp] = i;

	while(sp) {
		int u = stack[sp --];
		for(int i = head[u]; i; i = nxt[i])
			if(du[to[i]]) {
				du[to[i]] --;
				du[u] --;
				if(du[to[i]] == 1)
					stack[++ sp] = to[i];
			}
	}
}

bool cut[maxn << 1];
double down[maxn], up[maxn];
int son[maxn], pa[maxn];

double calc(int u) {
	double res = (up[u] * pa[u] + down[u] * son[u]) / (son[u] + pa[u]);
	for(int i = head[u]; i; i = nxt[i])
		if(not cut[i]) {
			cut[i ^ 1] = true;
			res += calc(to[i]);
			cut[i ^ 1] = false;
		}
	return res;
}

void dp_down(int u) {
	down[u] = 0;
	son[u] = 0;

	for(int i = head[u]; i; i = nxt[i])
		if(not cut[i]) {
			pa[to[i]] = 1;
			cut[i ^ 1] = true;
			dp_down(to[i]);
			cut[i ^ 1] = false;
			son[u] ++;
			down[u] += down[to[i]] + val[i];
		}

	if(son[u])
		down[u] /= son[u];

	debug("down %d : %d %lf\n", u, son[u], down[u]);
}

void dp_up(int u) {
	debug("up %d : %d %lf\n", u, son[u], up[u]);

	for(int i = head[u]; i; i = nxt[i])
		if(not cut[i]) {
			up[to[i]] = val[i] +
				(son[u] - 1 + pa[u] > 0 ?
				(up[u] * pa[u] + down[u] * son[u] - down[to[i]] - val[i]) /
				(son[u] - 1 + pa[u]) : 0);
			cut[i ^ 1] = true;
			dp_up(to[i]);
			cut[i ^ 1] = false;
		}
}

int main() {
	int n = input(), m = input();

	for(int i = 1; i <= m; i ++) {
		int u = input(), v = input(), w = input();
		add(u, v, w);
		add(v, u, w);
		du[u] ++;
		du[v] ++;
	}

	sort(n);

	double ans = 0;

	if(m == n)
		for(int u = 1; u <= n; u ++)
			if(du[u]) {
				int x = 0, y = 0;

				for(int i = head[u]; i; i = nxt[i])
					if(du[to[i]]) {
						if(x) y = i;
						else x = i;
					}

				debug("deal with %d\n", u);

				cut[y ^ 1] = cut[x ^ 1] = true;
				dp_down(to[x]);
				up[u] += val[x] + down[to[x]];
				dp_down(to[y]);
				up[u] += val[y] + down[to[y]];
				up[u] /= 2;
				cut[y ^ 1] = cut[x ^ 1] = false;

				debug("begin calc\n");

				cut[x] = cut[y] = true;
				pa[u] = 2;
				dp_down(u);
				dp_up(u);
				ans += calc(u);
				cut[x] = cut[y] = false;
			}

	if(m == n - 1) {
		pa[1] = 0;
		dp_down(1);
		dp_up(1);
		ans += calc(1);
	}

	printf("%.5lf\n", ans / n);
}
