#if 0
2020.05.08

  一个数 x 可能产生贡献的必要条件其出现不少于 x 次，这样的数不超过 O(sqrt) 个，对于每个
维护一个桶，询问暴力查询出现次数即可。
#endif
#include <cstdio>

struct { inline operator int () { int x; return scanf("%d", &x), x; } } read;

const int maxn = 100005, maxb = 500;
int a[maxn], tot[maxn];
int t[maxb][maxn], val[maxb];

int main () {
	int n = read, q = read;
	for (int i = 1; i <= n; i ++)
		if ((a[i] = read) <= n)
			++ tot[a[i]];
	int p = 0;
	for (int x = 1; x <= n; x ++)
		if (tot[x] >= x) {
			val[++ p] = x;
			for (int i = 1; i <= n; i ++)
				t[p][i] = t[p][i - 1] + (a[i] == x);
		}
	while (q --) {
		int l = read, r = read, ans = 0;
		for (int i = 1; i <= p; i ++)
			if (t[i][r] - t[i][l - 1] == val[i])
				++ ans;
		printf("%d\n", ans);
	}
}
