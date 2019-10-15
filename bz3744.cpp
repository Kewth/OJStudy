#if 0
2019.10.15

毒瘤 lxl 卡人只会缩时限。
Ynoi 实力劝退。。再也不做了，告辞。

终于卡过去了，感动。
根号分块，分类处理：
1) 块间预处理 f[l][r] 表示第 l 个块到第 r 个块之间的逆序对数。
2) 零散的块各自之间维护块内前缀逆序对数和后缀逆序对数。
3) 两边零散的块之间线性排序后归并计算逆序对数
4) 零散的块与完整的块之间维护 bf[i][j] 表示前 i 个数与第 j 个块之间的逆序对数，
   然后将每个完整的块与零散块分别计算逆序对数。
5) 区间在一个块内时通过容斥加线性排序。

考虑维护上述信息，
块内排序，全局排序，然后对于每个块 b 与所有数做一遍归并，
这样就可以计算出所有数对块 b 的逆序对贡献，做一遍前缀和算出所有 bf[i][b] 。
对于每个块暴力或者树状数组算出 pre 和 suf ，同时得出 f[i][i] 。
然后每个 f[l][r] 通过容斥 f[l][r] = f[l + 1][r] + f[l][r - 1] - f[l + 1][r - 1] + x
可知 x 只需要计算第 l 个块和第 r 个块之间的逆序对，用 bf 直接计算。
至于查询时候的线性排序，在块内排序的时候用二元组，把每个数的原来的位置记下来，
这样将零散的块排序只需要按书顺序扫一遍该块的排序二元组即可。
最后是询问 [l, r] 在同一个区间，首先通过容斥得出答案为 pre[r] - pre[l - 1] - x ，
算 x 就是算块到 l - 1 和 l 到 r 之间的逆序对，同样线性排序后归并。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <ctime>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
typedef std::pair<int, int> Par;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 100005, maxb = 320;
int a[maxb * maxb];
lolong f[maxb][maxb];
lolong bf[maxb][maxn];
Par sort[maxb][maxb], alsort[maxb * maxb];
int first[maxb][maxb], second[maxb][maxb];
int pos[maxb * maxb];
int suf[maxb * maxb], pre[maxb * maxb];

int tmp[maxb << 1];
int merge(int l1, int r1, int l2, int r2) {
	int p1 = l1, p2 = l2, res = 0;
	while(p1 <= r1 and p2 <= r2) {
		if(tmp[p1] <= tmp[p2]) {
			p1 ++;
			res += p2 - l2;
		}
		else if(tmp[p1] > tmp[p2])
			p2 ++;
	}
	res += (p2 - l2) * (r1 - p1 + 1);
	return res;
}

int main() {
	int n = input();
	int B = int(sqrt(n) + 1);

	for(int i = 0; i < B * B; i ++)
		alsort[i] = sort[i / B][i % B] = Par(i < n ? a[i] = input() : 0, i);

	for(int b = 0; b < B; b ++) {
		std::sort(sort[b], sort[b] + B);
		for(int i = 0; i < B; i ++) {
			first[b][i] = sort[b][i].first;
			second[b][i] = sort[b][i].second;
		}
		for(int i = 0; i < B; i ++)
			pos[second[b][i]] = i;
	}

	for(int b = 0; b < B; b ++) {
		for(int i = 1; i < B; i ++) {
			pre[b * B + i] = pre[b * B + i - 1];
			for(int j = 0; j < i; j ++)
				if(a[b * B + j] > a[b * B + i])
					pre[b * B + i] ++;
		}
		for(int i = B - 2; i >= 0; i --) {
			suf[b * B + i] = suf[b * B + i + 1];
			for(int j = i + 1; j < B; j ++)
				if(a[b * B + i] > a[b * B + j])
					suf[b * B + i] ++;
		}
		f[b][b] = suf[b * B];
	}

	std::sort(alsort, alsort + B * B);
	for(int b = 0; b < B; b ++) {
		int p1 = 0, p2 = 0;
		while(p1 < B * B and p2 < B) {
			if(alsort[p1].first <= first[b][p2]) {
				if(alsort[p1].second < b * B)
					bf[b][alsort[p1].second] = p2;
				p1 ++;
			}
			else
				p2 ++;
		}
		while(p1 < B * B) {
			if(alsort[p1].second < b * B)
				bf[b][alsort[p1].second] = p2;
			p1 ++;
		}

		p1 = B * B - 1;
		p2 = B - 1;
		while(p1 >= 0 and p2 >= 0) {
			if(alsort[p1].first >= first[b][p2]) {
				if(alsort[p1].second >= b * B + B)
					bf[b][alsort[p1].second] = B - p2 - 1;
				p1 --;
			}
			else
				p2--;
		}
		while(p1 >= 0) {
			if(alsort[p1].second >= b * B + B)
				bf[b][alsort[p1].second] = B - p2 - 1;
			p1 --;
		}

		for(int i = 1; i < B * B; i ++)
			bf[b][i] += bf[b][i - 1];
	}

	for(int l = B - 1; l >= 0; l --)
		for(int r = l + 1; r < B; r ++) {
			f[l][r] = f[l + 1][r] + f[l][r - 1] - f[l + 1][r - 1];
			f[l][r] += bf[l][r * B + B - 1] - bf[l][r * B - 1];
		}

    debug("%lf\n", clock() / double(CLOCKS_PER_SEC));
	lolong ans = 0;
	int q = input();
	while(q --) {
		int l = int((linput() ^ ans) - 1);
		int r = int((linput() ^ ans) - 1);
		int L = l / B + 1, R = r / B - 1;

		if(l / B == r / B) {
			int b = l / B;
			ans = pre[r] - (l > b * B ? pre[l - 1] : 0);

			int p1 = 0, p2 = B;
			for(int i = 0; i < B; i ++)
				if(second[b][i] < l)
					tmp[++ p1] = first[b][i];
				else if(second[b][i] <= r)
					tmp[++ p2] = first[b][i];
			ans -= merge(1, p1, B + 1, p2);
		}

		else {
			ans = f[L][R] + suf[l] + pre[r];

			int p1 = 0, p2 = B;
			for(int i = 0; i < B; i ++) {
				if(second[L - 1][i] >= l)
					tmp[++ p1] = first[L - 1][i];
				if(second[R + 1][i] <= r)
					tmp[++ p2] = first[R + 1][i];
			}
			ans += merge(1, p1, B + 1, p2);

			for(int b = L; b <= R; b ++)
				ans += bf[b][L * B - 1] - (l ? bf[b][l - 1] : 0) +
					bf[b][r] - bf[b][R * B + B - 1];
		}

		printf("%lld\n", ans);
	}
    debug("%lf\n", clock() / double(CLOCKS_PER_SEC));
}
