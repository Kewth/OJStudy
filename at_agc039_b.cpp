#if 0
2019.10.06

枚举在 set1 的点，然后 bfs 分层。
#endif
#include <cstdio>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 205;
char s[maxn][maxn];
int d[maxn];

int ans;
bool shit;
void bfs(int st, int n) {
	std::queue<int> q;
	d[st] = 1;
	q.push(st);

	while(!q.empty()) {
		int u = q.front();
		q.pop();
		/* debug("%d %d\n", u, d[u]); */
		if(d[u] > ans) ans = d[u];

		for(int i = 1; i <= n; i ++)
			if(s[u][i] == '1' and !d[i]) {
				d[i] = d[u] + 1;
				q.push(i);
			} else if(s[u][i] == '1' and (d[i] & 1) == (d[u] & 1))
				shit = 1;
	}
}

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++)
		scanf("%s", s[i] + 1);

	for(int i = 1; i <= n; i ++) {
		/* debug("start %d\n", i); */
		for(int j = 1; j <= n; j ++)
			d[j] = 0;
		bfs(i, n);
		if(shit) {
			puts("-1");
			return 0;
		}
	}

	printf("%d\n", ans);
}
