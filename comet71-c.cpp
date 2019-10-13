#if 0
2019.10.12

建图，将输入的矩阵看做 m * n 个点，对于每一辆车（每一列）按时间顺序连边，
即 n1 前面的从上向下连，后面的从下向上连，边权为 0 ，因为坐车不会有等待时间。
每一行依然按时间顺序连边，两点的边权 (u, v) 为它们的时间差，
因为从 u 到 v 相当于要从 u 下车一直等到 v 上车。
然后类似地建源点汇点跑最短路即可。
可能的坑点是一行中时间相等的车要双向连边而不能只连单向边，要保证这些车在一个强连通分量。
#endif
#include <cstdio>
#include <queue>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 1000050;
struct Dot {
	int t;
	int dis;
	Dot *to[3];
} D[maxn];
int nxt[maxn], to[maxn];
Dot *d[maxn];

bool cmp(Dot *x, Dot *y) {
	return x -> t < y -> t;
}

int main() {
	for(int i = 0; i < maxn; i ++)
		d[i] = &D[i];

	int Test = input();
	while(Test --) {
		int m = input(), n1 = input(), n2 = input();
		int s = input() - 1, t1 = input(), t2 = input();
		int n = n1 + n2;

		Dot *S = d[n * m], *T = d[n * m + 1];
		S -> t = t1;
		T -> t = t2;

		S -> to[0] = S -> to[2] = NULL;
		T -> to[0] = T -> to[1] = T -> to[2] = NULL;

		for(int i = 0; i < m * n; i ++) {
			d[i] -> t = input();
			int a = i / n, b = i % n;
			if(b < n1)
				d[i] -> to[0] = a < m - 1 ? d[i + n] : NULL;
			if(b >= n1)
				d[i] -> to[0] = a > 0 ? d[i - n] : NULL;
		}

		for(int i = 0; i < m; i ++) {
			std::sort(d + i * n, d + i * n + n, cmp);
			for(int j = 0; j < n - 1; j ++)
				d[i * n + j] -> to[1] = d[i * n + j + 1];
			d[i * n + n - 1] -> to[1] = NULL;
			for(int j = 1; j < n; j ++)
				d[i * n + j] -> to[2] = d[i * n + j - 1];
			d[i * n] -> to[2] = NULL;
		}

		S -> to[1] = NULL;
		for(int i = 0; i < n; i ++)
			if(d[s * n + i] -> t >= S -> t) {
				S -> to[1] = d[s * n + i];
				break;
			}

		/* d[s * n + n - 1] -> to[1] = NULL; */
		for(int i = n - 1; i >= 0; i --)
			if(d[s * n + i] -> t <= T -> t) {
				d[s * n + i] -> to[1] = T;
				break;
			}

		for(int i = 0; i < n * m + 2; i ++)
			d[i] -> dis = 1000000000;
		T -> dis = t2 - t1;

		typedef std::pair<int, Dot *> Par;
		std::priority_queue<Par> q;
		q.push(Par(S -> dis = 0, S));

		while(!q.empty()) {
			int di = - q.top().first;
			Dot *u = q.top().second;
			q.pop();
			if(di > u -> dis) continue;

			/* debug("%ld : (%ld, %ld) %d\n", */
			/* 		u - D, u -> to[0] - D, u -> to[1] - D, u -> dis); */

			for(int i = 0; i < 3; i ++) {
				Dot *v = u -> to[i];
				if(!v) continue;
				int tod = u -> dis + (i ? v -> t - u -> t : 0);
				if(v -> t >= u -> t and tod < v -> dis) {
					v -> dis = tod;
					q.push(Par(- tod, v));
				}
			}
		}

		printf("%d\n", T -> dis);
		for(int i = 0; i < n * m + 2; i ++)
			d[i] = &D[i];
	}
}
