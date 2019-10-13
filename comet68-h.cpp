#if 0
2019.10.01

将 DAG 上的博弈游戏推广到任意有向图上，
能到达必败点的仍然是必胜点，但反之却不一定，
如果一个点不能到达必败点，它有可能是平局状态。
但如果一个点只能到达必胜点，那么它就一定是必败点。

把每个到必胜点的边删掉，那么除了初始状态外一个点没有出边时就是必败。
而每个到必败点的点都可以直接确定是必胜点。
那么据此可以做类似拓扑排序的东西，没确定一个点必败或必胜都可以将它的入边割掉，
最后剩下若干环，这些点一定是平局状态。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 1010;
int nxt[maxn * maxn * 2], tox[maxn * maxn * 2], toy[maxn * maxn * 2], hp;
int head[maxn][maxn];
int in[maxn][maxn];
bool vis[maxn][maxn];
int f[maxn][maxn];

inline void add(int ux, int uy, int vx, int vy) {
	if(!vx or !vy) return;
	nxt[++ hp] = head[ux][uy];
	head[ux][uy] = hp;
	tox[hp] = vx;
	toy[hp] = vy;
	in[vx][vy] ++;
}

void update(int ux, int uy) {
	if(vis[ux][uy])
		return;
	vis[ux][uy] = 1;

	/* debug("update %d %d : %d\n", ux, uy, f[ux][uy]); */

	for(int i = head[ux][uy]; i; i = nxt[i]) {
		int vx = tox[i], vy = toy[i];
		in[vx][vy] --;
		if(f[ux][uy] == -1)
			f[vx][vy] = 1;
		if(!in[vx][vy] and !f[vx][vy])
			f[vx][vy] = -1;
		if(f[vx][vy])
			update(vx, vy);
	}
}

int main() {
	int q = input();
	while(q --) {
		int n = input(), m = input();

		hp = 0;
		for(int i = 0; i < n; i ++)
			for(int j = 0; j < n; j ++)
				head[i][j] = f[i][j] = in[i][j] = vis[i][j] = 0;

		for(int i = 0; i < n; i ++)
			for(int j = 0; j < n; j ++) {
				add(j, (i + j) % n, i, j);
				add(j, (i * j) % n, i, j);
			}

		for(int i = 1; i < n; i ++)
			f[i][0] = -1;
		for(int j = 1; j < n; j ++)
			f[0][j] = 1;

		for(int i = 0; i < n; i ++)
			for(int j = 0; j < n; j ++)
				if(!in[i][j] and (i or j))
					update(i, j);

		/* for(int i = 0; i < n; i ++) */
		/* 	for(int j = 0; j < n; j ++) { */
		/* 		debug("%d %d: %d\n", i, j, f[i][j]); */
		/* 		for(int k = head[i][j]; k; k = nxt[k]) */
		/* 			debug("<- %d %d\n", tox[k], toy[k]); */
		/* 	} */

		while(m --) {
			int a = input(), b = input();
			if(f[a][b] == 1)
				puts("cocktail");
			else if(f[a][b] == 0)
				puts("draw");
			else
				puts("sys");
		}
	}
}
