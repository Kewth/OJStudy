#if 0
2020.02.23

史上最难费用流。

用线性规划描述这个问题，有两类决策变量：
1) x_i 表示第 i 天氪金数，
2) y_i 表示第 i 个活动中实际有用的氪金数。
那么有三类约束：
1) sum(x_i) <= C
2) y_i <= K_i
3) y_i <= sum(x_j [R_i <= j <= R_i])
需要最大化 sum(y_i * Y_i) 。

考虑这个线性规划对偶问题，有三类决策变量 z, {a}, {b} 。
两类约束：
1) z - sum(b_j [L_i <= j <= R_i]) >= 0
2) a_i + b_i >= Y_i
需要最小化 C * z + sum(a_i * K_i) 。

不难发现一定存在最优解使得所有 a_i + b_i 恰好等于 Y_i 。
将 B_i 消掉，得到新的两类约束：
1) z + sum(a_j [L_i <= j <= R_i]) >= S_i
2) a_i <= Y_i
其中 S_i 是第 i 天所有活动的贡献和。

到此这个线性规划就非常明显了，第二类约束是范围限制，
第一类约束每个决策变量都存在于约束的连续一段。
将约束松弛后差分即可得到费用流建图方式。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 2020, maxm = 12345, inf = 2000000005;
int S[maxn];
int head[maxn], nxt[maxm], to[maxm], cap[maxm], cost[maxm], hp = 1;

inline void add(int u, int v, int ca, int co) {
	if((hp & 1) and !ca) return;
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	cap[hp] = ca;
	cost[hp] = co;
	if(!(hp & 1)) add(v, u, 0, - co);
}

int dis[maxn];
bool inq[maxn];
int from[maxn];

bool spfa(int s, int t) {
	std::queue<int> q;
	std::fill(dis, dis + t + 1, inf);
	std::fill(inq, inq + t + 1, 0);
	dis[s] = 0;
	q.push(s);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = 0;
		for(int i = head[u]; i; i = nxt[i])
			if(cap[i] and dis[u] + cost[i] < dis[to[i]]) {
				from[to[i]] = i;
				dis[to[i]] = dis[u] + cost[i];
				if(!inq[to[i]]) {
					q.push(to[i]);
					inq[to[i]] = 1;
				}
			}
	}
	return dis[t] < inf;
}

ll mcmf(int s, int t) {
	ll res = 0;
	while(spfa(s, t)) {
		int f = inf;
		for(int x = t; x != s; x = to[from[x] ^ 1])
			f = std::min(f, cap[from[x]]);
		for(int x = t; x != s; x = to[from[x] ^ 1]) {
			cap[from[x]] -= f;
			cap[from[x] ^ 1] += f;
		}
		res += 1ll * f * dis[t];
	}
	return res;
}

int main() {
	int q = read;
	while(q --) {
		int n = read, m = read, C = read;
		int s = n + 2, t = n + 3;
		std::fill(S, S + n + 2, 0);
		std::fill(head, head + t + 1, 0);
		hp = 1;

		for(int i = 1; i <= n; i ++)
			add(i, i + 1, inf, 0);

		add(n + 1, 1, inf, C);

		for(int i = 1; i <= m; i ++) {
			int l = read, r = read, K = read, Y = read;
			add(r + 1, l, Y, K);
			for(int j = l; j <= r; j ++)
				S[j] += Y;
		}

		for(int i = 1; i <= n + 1; i ++) {
			int d = S[i] - S[i - 1];
			if(d > 0) add(i, t, d, 0);
			if(d < 0) add(s, i, -d, 0);
		}

		// 必须满流
		// 没有负环
		printf("%lld\n", mcmf(s, t));
	}
}
