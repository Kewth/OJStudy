#if 0
2019.10.22

二分答案 T ，问题转换为判断是否有可行的分数。
每个限制可以表示成 x < y * k 这样的不等式，用差分约束即可。

然而题目从头到尾没有提到的一点是对于 k - T 倍杀必须有 T < k ，你大爷。

蛇皮，不知道为什么用最短路会 -1 而用最长路就可以，
大概是因为最短路的话 dis 始终很小导致精度会挂？
不知道为什么精度贼 wei 必须将 eps 设为极小的一个数，
大概把乘积边权用对数转换为加法边权就不会那么卡精度。
#endif
#include <cstdio>
#include <queue>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1005;
const double eps = 1e-15;
int t[maxn], a[maxn], b[maxn], k[maxn];
int head[maxn], nxt[maxn << 2], to[maxn << 2], hp = 1;
double val[maxn << 2];
double up[maxn], down[maxn];

inline void add(int u, int v, double w) {
	/* debug("%d -> %d : %lf\n", u, v, w); */
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	val[hp] = w;
}

int tot[maxn];
bool inq[maxn];
double dis[maxn];
int n, m, c;
bool spfa() {
	std::queue<int> q;
	q.push(n + 1);
	memset(tot, 0, sizeof tot);
	memset(inq, 0, sizeof inq);
	for(int i = 1; i <= n; i ++)
		dis[i] = 0;
	dis[n + 1] = 1;
	tot[n + 1] = 1;

	while(!q.empty()) {
		int u = q.front();
		q.pop();
		/* debug("%d : %lf\n", u, dis[u]); */
		inq[u] = 0;

		for(int i = head[u]; i; i = nxt[i]) {
			int v = to[i];
			if(dis[u] * val[i] > dis[v] + eps) {
				dis[v] = dis[u] * val[i];
				if(!inq[v]) {
					/* debug("%d -> %d\n", u, v); */
					q.push(v);
					inq[v] = 1;
					if(++ tot[v] > n)
						return 1;
				}
			}
		}
	}

	return 0;
}

bool check(double T) {
	/* debug("check %lf\n", T); */
	memset(head, 0, sizeof head);

	hp = 0;
	for(int i = 1; i <= m; i ++) {
		if(t[i] == 1)
			add(a[i], b[i], k[i] - T);
		else if(t[i] == 2)
			add(a[i], b[i], 1 / (k[i] + T));
	}

	for(int i = 1; i <= n; i ++) {
		add(n + 1, i, 1 / up[i]);
		add(i, n + 1, down[i]);
	}

	return spfa();
}

int main() {
	n = input(), m = input(), c = input();

	int min = 1000000000;
	for(int i = 1; i <= m; i ++) {
		t[i] = input();
		a[i] = input();
		b[i] = input();
		k[i] = input();
		if(t[i] == 1)
			min = std::min(k[i], min);
	}

	for(int i = 1; i <= n; i ++) {
		up[i] = 1e30;
		down[i] = 0;
	}

	for(int i = 1; i <= c; i ++) {
		int p = input();
		up[p] = down[p] = input();
	}

	double l = 0, r = min;
	while(r - l > eps) {
		double mid = (l + r) / 2;
		if(check(mid))
			l = mid;
		else
			r = mid - eps;
	}

	if(l < eps)
		puts("-1");
	else
		printf("%.6lf\n", l);
}
