#if 0
2020.02.24

很诡。
首先确定最优策略，每次一定是选择可以到达的点中期望步数最小的点。
假设将所有点按期望步数排序，就能很容易知道期望的计算方式。
虽然期望步数是未知的，但是可以逐个确定期望步数最小的点。
从终点开始，每次找到还未排序的点中期望步数最小的点 x ，
此时期望步数比 x 小的点都确定了，x 点的期望步数也能确定，
然后将 x 对其他点的贡献加上，重复此步骤直到所有点排好序。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1010;
bool vis[maxn];
ld p[maxn][maxn], E[maxn], pre[maxn];

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			p[i][j] = ld(read) / 100;

	for(int i = 1; i < n; i ++)
		pre[i] = 1;

	E[0] = 1e200;
	int x = n;
	while(x) {
		vis[x] = 1;
		E[x] = (E[x] + pre[x]) / (1 - pre[x]);
		for(int i = 1; i <= n; i ++)
			if(i != x)
				E[i] += p[i][x] * pre[i] * (E[x] + 1);
		for(int i = 1; i <= n; i ++)
			pre[i] *= 1 - p[i][x];
		x = 0;
		for(int i = 1; i <= n; i ++)
			if(!vis[i] and (E[i] + pre[i]) / (1 - pre[i]) <
					(E[x] + pre[x]) / (1 - pre[x]))
				x = i;
		// for(int i = 1; i <= n; i ++)
			// debug(" %.3lf", double(E[i]));
		// debug("\n");
	}

	printf("%.8lf\n", double(E[1]));
}
