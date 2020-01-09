#if 0
2020.01.09

和修车一样，将一个厨师按代价拆成 p 个，第 i 个花 i 倍代价。
但是这个数据范围下直接拆会 T 飞。
由于每个厨师每次只会用代价最小的一个，没必要一次全拆出来给费用流决策。
每个厨师永远保持一个，每次找出增广路后新加一个该厨师，代价倍数加 1 即可。
可是为啥这题不能拟 dinic 多路增广？
#endif
#include <cstdio>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 1000, maxm = 100000;
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

ll dis[maxn];
bool inq[maxn];
int from[maxn];
bool spfa(int s, int t) {
	std::queue<int> q;
	std::fill(dis, dis + t + 1, 1000000000000000000);
	std::fill(inq, inq + t + 1, 0);
	dis[s] = 0;
	q.push(s);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = 0;
		/* debug("%d : %lld\n", u, dis[u]); */
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
	return dis[t] < 1000000000000000000;
}

int id[maxn], ip;
int times[105];
int a[45][105];
ll mincostmaxflow(int s, int t, int n) {
	ll res = 0;
	while(spfa(s, t)) {
		int f = 2147483647;
		for(int x = t; x != s; x = to[from[x] ^ 1])
			f = std::min(f, cap[from[x]]);
		res += dis[t] * f;
		for(int x = t; x != s; x = to[from[x] ^ 1]) {
			cap[from[x]] -= f;
			cap[from[x] ^ 1] += f;
		}
		int j = id[to[from[t] ^ 1]];
		++ ip;
		++ times[j];
		for(int i = 1; i <= n; i ++)
			add(i, ip, 1, a[i][j] * times[j]);
		add(ip, t, 1, 0);
		id[ip] = j;
	}
	return res;
}

int b[45];
int main() {
	int n = read, m = read;
	int s = maxn - 2, t = maxn - 1;

	for(int i = 1; i <= n; i ++)
		add(s, i, b[i] = read, 0);

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++) {
			read(a[i][j]);
			add(i, n + j, 1, a[i][j]);
			id[n + j] = j;
		}
	ip = n + m;

	for(int j = 1; j <= m; j ++) {
		times[j] = 1;
		add(n + j, t, 1, 0);
	}

	printf("%lld\n", mincostmaxflow(s, t, n));
}
