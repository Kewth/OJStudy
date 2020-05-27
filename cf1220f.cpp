#if 0
2020.05.27

  将序列倍长，考虑对于每个长为 n 的区间动态维护笛卡尔树深度。
  注意到需要的需要支持的修改只有在右边加入一个数和删除最左边的数。那么加入的数在笛卡尔数
上没有右儿子，其带来的影响就是把其左儿子对应的子树的深度整体加一，而其左儿子对应的子树对
应的是一段连续区间 [l, r] ，其中 l - 1 是最靠右的不超过加入的数的数的位置。删除同理。
  不难想到用线段树维护每个位置在笛卡尔树上的深度，只需要支持区间加，查询单点值和查询全局
最大值三个操作。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔   CopyRight :)
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 400005;
int a[maxn];
int tol[maxn], tor[maxn];
int stack[maxn], sp;
int seg[maxn << 2], tag[maxn << 2];
#define ls (now << 1)
#define rs (now << 1 | 1)

void add (int now, int L, int R, int l, int r, int x) {
	if (r < L or l > R) return;
	if (l <= L and R <= r) return seg[now] += x, tag[now] += x, void();
	int M = (L + R) >> 1;
	add(ls, L, M, l, r, x);
	add(rs, M + 1, R, l, r, x);
	seg[now] = std::max(seg[ls], seg[rs]) + tag[now];
}

int query (int now, int L, int R, int p) {
	if (p == 0) return 0;
	if (L == R) return seg[now];
	int M = (L + R) >> 1;
	if (p <= M) return query(ls, L, M, p) + tag[now];
	else return query(rs, M + 1, R, p) + tag[now];
}

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++)
		a[i + n] = a[i] = read;
	int N = n * 2;

	for (int i = 1; i <= N; i ++) {
		while (sp and a[stack[sp]] > a[i])
			-- sp;
		tol[i] = stack[sp];
		stack[++ sp] = i;
	}
	sp = 0;
	for (int i = N; i; i --) {
		while (sp and a[stack[sp]] > a[i])
			-- sp;
		tor[i] = stack[sp];
		stack[++ sp] = i;
	}

	int ans = 100000000, shift = 0;
	for (int r = 1; r < N; r ++) {
		int l = r - n + 1;
		if (l > 1) {
			/* debug("shit %d -> %d\n", l - 1, tor[l - 1]); */
			add(1, 1, N, l - 1, l - 1, -query(1, 1, N, tor[l - 1]) - 1);
			add(1, 1, N, l, tor[l - 1] - 1, -1);
		}
		add(1, 1, N, tol[r] + 1, r - 1, 1);
		add(1, 1, N, r, r, query(1, 1, N, tol[r]) + 1);
		if (l >= 1 and seg[1] < ans) {
			ans = seg[1];
			shift = l - 1;
		}
		/* debug("%d - %d : %d\n", l, r, seg[1]); */
		/* for (int i = 1; i <= N; i ++) */
		/* 	debug(" %d", query(1, 1, N, i)); */
		/* debug("\n"); */
	}

	printf("%d %d\n", ans, shift);
}
