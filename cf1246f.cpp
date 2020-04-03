#pragma GCC optimize(3)
#if 0
2020.04.02

倒着考虑，对于一个点 i ，考虑一步能到达 i 的所有点 j 。
不难发现合法的点 j 构成了一个区间。
更一般的，对于一个点 i ，能在 k 步以内到达 i 的所有点 j 构成区间 [L[k][i], R[k][i]] 。
不难发现答案就是 sum(n - (R - L + 1)) ，问题转换为求 sum(L) 和 sum(R) 。
而所有的 L, R 有 O(n^2) 种，不能直接进行计算。

注意到对于区间 [L, R], 能一步到达这个区间的新区间的右端点实际上是 [L, R] 中，
每种字符最靠右的位置的 nxt 最大值，其中 nxt[i] 是 i 右边与 i 字符相同的最小位置。
那么对于 [L1, R] 和 [L2, R] ，如果它们包含的字符集数目相同，
那么能一步到达这个两个区间的新区间右端点相同。
对于左端点有类似的结论。

那么对于所有 t ，预处理 fr[t][i] 表示满足区间 [L, i] 内有 t 种字符的区间中，
能一步到达这个区间的新区间的右端点，类似地处理 fl[t][i] 。
对于区间 [L, R] ，如果它的字符集大小为 t ，能一步到达它的新区间就是 [fl[t][L], fr[t][R]] 。
随着区间 [L, R] 的扩大，字符集大小单调不减，但是字符集大小最多增加 26 次。
也就是说对于字符集大小不变的一段连续扩展可以放在一起处理，并且此时的 L, R 是互不影响的。

求出 fl, fr 的倍增数组，枚举字符集大小，对于每个点 i 倍增地扩展能达到它的区间即可。
细节略，总复杂度 O(nlognA) ，其中 A 是字符集大小，实现得不精细就很容易多个 log 或者 A 。
#endif
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <functional>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

const int maxn = 100005, maxk = 17, A = 26;
char s[maxn];
// 学到许多，下面这两个常数差了至少 3 到 5 倍。
/* int fl[maxn][maxk], fr[maxn][maxk]; */
/* ll sl[maxn][maxk], sr[maxn][maxk]; */
int fl[maxk][maxn], fr[maxk][maxn];
ll sl[maxk][maxn], sr[maxk][maxn];
int tol[maxn], tor[maxn];
int L[maxn], R[maxn];
int pre[maxn][A + 1], nxt[maxn][A + 1];
int st[maxk][maxn];
int hb[maxn];
int tot[maxn];

void stinit (int n) {
	for (int i = n; i; i --)
		for (int k = 1; i + (1 << k) - 1 <= n; k ++)
			st[k][i] = st[k - 1][i] | st[k - 1][i + (1 << k >> 1)];
	for (int i = 2; i <= n; i ++)
		hb[i] = hb[i >> 1] + 1;
}

int stquery (int l, int r) {
	int k = hb[r - l + 1];
	return st[k][l] | st[k][r - (1 << k) + 1];
}

inline int S (int i) { return s[i] - 'a'; }

int main () {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1));

	for (int i = 1; i <= n; i ++)
		st[0][i] = 1 << S(i);
	stinit(n);

	std::fill(pre[1] + 1, pre[1] + A + 1, tol[1] = 1);
	for (int i = 2; i <= n; i ++) {
		std::copy(pre[i - 1], pre[i - 1] + A + 1, pre[i]);
		tol[i] = pre[i][S(i) + 1];
		pre[i][S(i) + 1] = i;
	}

	std::fill(nxt[n] + 1, nxt[n] + A + 1, tor[n] = n);
	for (int i = n - 1; i; i --) {
		std::copy(nxt[i + 1], nxt[i + 1] + A + 1, nxt[i]);
		tor[i] = nxt[i][S(i) + 1];
		nxt[i][S(i) + 1] = i;
	}

	for (int i = 1; i <= n; i ++) {
		std::sort(pre[i] + 1, pre[i] + A + 1, std::greater<int>());
		std::sort(nxt[i] + 1, nxt[i] + A + 1);
	}

	for (int i = 1; i <= n; i ++) fl[0][i] = fr[0][i] = L[i] = R[i] = i;
	std::fill(tot + 1, tot + n + 1, n);

	ll ans = 1ll * n * n * n - n;
	/* debug("%lld\n", ans); */
	for (int t = 1; t <= A; t ++) {
		for (int i = 1; i <= n; i ++) {
			sl[0][i] = fl[0][i] = std::min(fl[0][i], tol[nxt[i][t]]);
			sr[0][i] = fr[0][i] = std::max(fr[0][i], tor[pre[i][t]]);
		}
		for (int k = 1; k < maxk; k ++)
			for (int i = 1; i <= n; i ++) {
				fl[k][i] = fl[k - 1][fl[k - 1][i]];
				fr[k][i] = fr[k - 1][fr[k - 1][i]];
				sl[k][i] = sl[k - 1][i] + sl[k - 1][fl[k - 1][i]];
				sr[k][i] = sr[k - 1][i] + sr[k - 1][fr[k - 1][i]];
			}
		for (int i = 1; i <= n; i ++)
			if (tot[i] and __builtin_popcount(unsigned(stquery(L[i], R[i]))) == t) {
				for (int k = maxk - 1; k >= 0; k --)
					if ((1 << k) <= tot[i]) {
						int nl = fl[k][L[i]], nr = fr[k][R[i]];
						if (__builtin_popcount(unsigned(stquery(nl, nr))) <= t) {
							ans += sl[k][L[i]];
							ans -= sr[k][R[i]];
							L[i] = nl;
							R[i] = nr;
							tot[i] -= 1 << k;
						}
					}
				if (tot[i]) {
					ans += sl[0][L[i]];
					ans -= sr[0][R[i]];
					L[i] = fl[0][L[i]];
					R[i] = fr[0][R[i]];
					-- tot[i];
				}
			}
		/* for (int i = 1; i <= n; i ++) */
		/* 	debug("%d - %d (%d)\n", L[i], R[i], tot[i]); */
		/* debug("%lld\n", ans); */
		/* debug("\n"); */
	}

	printf("%lld\n", ans);
}
