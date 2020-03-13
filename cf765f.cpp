#if 0
2020.03.11

可以分块，这种统计区间数对信息的询问都可以参考 Ynoi 的区间逆序对。
这题要能处理两个东西：
1) f[b][i] 表示第 b 块到第 belong[i] +- 1 块这部分和
第 i 个点到那之间这部分之间的答案。
2) F[l][r] 表示第 l 块到第 r 块之间的答案。

注意到如果知道一段排序后的结果，就能线性求出这段的答案。
因此还要能 O(块大小) 对于至多两段块内区间的并排序。
只要预处理一个块内的排序结果就能做到对一个块内区间排序，
而对于两个区间一起排序只需要再进行一次归并。

对于询问 [l, r]，如果 l, r 在同一个块，直接排序求答案。
否则对于零散的部分排序求答案，整块之间查询 F ，零散和整块之间查询 f 。

f 的处理就是处理出 g[b][i] 表示第 b 块和第 i 个点之间的答案。
然后做个类似于二位前缀和的东西即可。
而 F 是可以从 f 递推得到的。

当然正解是利用到了一个性质：可能对答案产生贡献的数对是 O(nlogV) 的。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005, maxs = 500, maxb = 500, inf = 1000000000;
int bl[maxn];
int L[maxs], R[maxs];
int a[maxn];
par s[maxn];
int f[maxs][maxn];
int bf[maxs][maxs];
int tmp1[maxb], tmp2[maxb], tmp3[maxb];

int block_sort(int l, int r, int *tmp = tmp1) {
	int b = bl[l], p = 0;
	for(int i = L[b]; i <= R[b]; i ++)
		if(l <= s[i].second and s[i].second <= r)
			tmp[++ p] = s[i].first;
	return p;
}

void calc(int p, int &tar, int *tmp = tmp1) {
	for(int i = 1; i < p; i ++)
		tar = std::min(tar, tmp[i + 1] - tmp[i]);
}

int main() {
	int n = read, B = int(sqrt(n));
	for(int i = 1; i <= n; i ++)
		s[i] = par(a[i] = read, i);

	int S = 0;
	for(int i = 1; i <= n; i ++) {
		if(!S or R[S] - L[S] + 1 == B)
			L[++ S] = i;
		bl[R[S] = i] = S;
	}

	for(int b = 1; b <= S; b ++)
		std::sort(s + L[b], s + R[b] + 1);

	for(int b = 1; b <= S; b ++)
		for(int c = 1; c <= S; c ++) {
			int p = L[b];
			for(int i = L[c]; i <= R[c]; i ++) {
				while(p <= R[b] and s[p].first < s[i].first)
					++ p;
				int &now = f[b][s[i].second] = inf;
				if(p <= R[b])
					now = std::min(now, s[p].first - s[i].first);
				if(p > L[b])
					now = std::min(now, s[i].first - s[p - 1].first);
			}
		}

	for(int b = 1; b <= S; b ++)
		for(int c = 1; c < b; c ++)
			for(int i = R[c] - 1; i >= L[c]; i --)
				f[b][i] = std::min(f[b][i], f[b][i + 1]);

	for(int b = 1; b <= S; b ++)
		for(int c = S; c > b; c --)
			for(int i = L[c] + 1; i <= R[c]; i ++)
				f[b][i] = std::min(f[b][i], f[b][i - 1]);

	for(int i = 1; i <= n; i ++) {
		f[bl[i]][i] = inf;
		for(int b = bl[i] + 1; b <= S; b ++)
			f[b][i] = std::min(f[b - 1][i], f[b][i]);
		for(int b = bl[i] - 1; b; b --)
			f[b][i] = std::min(f[b + 1][i], f[b][i]);
	}

	for(int b = S; b; b --) {
		calc(block_sort(L[b], R[b]), bf[b][b] = inf);
		for(int c = b + 1; c <= S; c ++)
			bf[b][c] = std::min({bf[b][c - 1], f[b][R[c]], bf[c][c]});
	}

	int q = read;
	while(q --) {
		int l = read, r = read, ans = inf;
		// debug("query %d %d\n", l, r);

		if(bl[l] == bl[r])
			calc(block_sort(l, r), ans);

		else {
			int lb = bl[l] + 1, rb = bl[r] - 1;

			int p2 = block_sort(l, R[lb - 1], tmp2);
			int p3 = block_sort(L[rb + 1], r, tmp3);
			std::merge(tmp2 + 1, tmp2 + p2 + 1,
					tmp3 + 1, tmp3 + p3 + 1, tmp1 + 1);
			int p1 = p2 + p3;
			calc(p1, ans);

			if(lb <= rb) {
				ans = std::min(ans, bf[lb][rb]);
				ans = std::min(ans, f[rb][l]);
				ans = std::min(ans, f[lb][r]);
			}
		}

		printf("%d\n", ans);
	}
}
