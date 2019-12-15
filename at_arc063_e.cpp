#if 0
2019.12.15

每次考虑当前未被考虑的权值最小的点，设该点权值为 w ，检查与该点相连的每个点 v ，
如果 v 权值未知，另 v 的权值为 w + 1 即可。
用优先队列找出每次权值最小的点。
#endif
#include <cstdio>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> Par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100010;
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp = 1;
int a[maxn];
bool get[maxn];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

int main() {
	int n = read;

	for(int i = 1; i < n; i ++) {
		int u = read, v = read;
		add(u, v);
		add(v, u);
	}

	std::priority_queue<Par> qu;

	int k = read;
	while(k --) {
		int u = read;
		read(a[u]);
		qu.push(Par(- a[u], u));
		get[u] = 1;
	}

	while(!qu.empty()) {
		int u = qu.top().second;
		qu.pop();

		for(int i = head[u]; i; i = nxt[i]) {
			int v = to[i];
			if(get[v] and a[v] != a[u] + 1 and a[v] != a[u] - 1)
				return puts("No"), 0;
			if(!get[v]) {
				a[v] = a[u] + 1;
				get[v] = 1;
				qu.push(Par(- a[v], v));
			}
		}
	}

	puts("Yes");
	for(int i = 1; i <= n; i ++)
		printf("%d\n", a[i]);
}
