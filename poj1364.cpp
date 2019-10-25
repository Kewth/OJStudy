#if 0
2019.10.25

把区间和转换为前缀和后就是差分约束裸题了。
（还真就一遍 A 了）
#endif
#include <cstdio>
#include <cstring>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x = 0; scanf("%d", &x); return x; }

const int maxn = 105;
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], hp;

inline void add(int u, int v, int w) {
	/* debug("%d -> %d : %d\n", u, v, w); */
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	val[hp] = w;
}

lolong dis[maxn];
bool vis[maxn], inq[maxn];
int tot[maxn];

bool spfa(int s) {
	memset(inq, 0, sizeof inq);
	memset(dis, 0, sizeof dis);
	memset(tot, 0, sizeof tot);

	std::queue<int> q;
	q.push(s);
	dis[s] = - 1000000000;

	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = 0;
		vis[u] = 1;

		for(int i = head[u]; i; i = nxt[i]) {
			int v = to[i];
			if(dis[u] + val[i] < dis[v]) {
				dis[v] = dis[u] + val[i];
				if(!inq[v]) {
					inq[v] = 1;
					q.push(v);
					tot[v] ++;
					if(tot[v] >= 100)
						return 1;
				}
			}
		}
	}

	return 0;
}

int main() {
	char fuckstr[5];
	while(1) {
		int n = input(), m = input();
		if(!n and !m) break;
		/* debug("%d %d\n", n, m); */

		memset(head, hp = 0, sizeof head);
		memset(vis, 0, sizeof vis);

		for(int i = 1; i <= m; i ++) {
			int a = input(), b = a + input();
			scanf("%s", fuckstr);
			int k = input();
			a --;

			if(*fuckstr == 'g')
				add(b, a, -k - 1);
			else
				add(a, b, k - 1);
		}

		bool ans = 1;
		for(int u = 0; u <= n; u ++)
			if(!vis[u] and spfa(u)) {
				ans = 0;
				break;
			}

		if(ans) puts("lamentable kingdom");
		else puts("successful conspiracy");
	}
}
