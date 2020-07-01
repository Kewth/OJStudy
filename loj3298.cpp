/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.19

 * Solution:
  容易想到对于右端点 r ，预处理 f[r] 表示 s 中以 r 为右端点的最大的在 t 中出现的子串
长度。那么对于询问，如果 l = 1 答案就是 f[r] 的前缀最大值，否则，稍加变换，就是区间内
min(f[i], i - l + 1) 的最大值。
  预处理 f[r] 对 t 建 SAM 把 s 扔进去跑即可。
  似乎到这就可以直接数据结构暴力维护，但是 f 有一些性质。首先注意到 i - f[i] 是单调不
减的，事实上对于询问区间 [l, r] 可以分成两段 [l, m] 和 [m + 1, r] ，前者区间的所有 i
都满足 i - f[i] + 1 < l ，后者都不满足。那么前者的贡献就是右端点最大值，就是 m ，后者
的贡献就是 f 的最大值，做个 RMQ 即可。
  那么问题只剩下快速求出分界点 m ，注意到 m 只与 l 有关，不妨设 m = R[l] ，不难发现由
于 i - f[i] 单调，R[i] 也是单调不减的。

 * Digression:
  不难题。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005, maxc = 2;
char s[maxn], t[maxn];
int len[maxn << 1], ch[maxn << 1][2], fa[maxn << 1], cp = 1;

int insert (int pre, int x) {
	int now = ++ cp;
	len[now] = len[pre] + 1;
	while (pre and !ch[pre][x])
		ch[pre][x] = now, pre = fa[pre];
	if (pre) {
		int preto = ch[pre][x];
		if (len[preto] == len[pre] + 1)
			fa[now] = preto;
		else {
			int sp = ++ cp;
			len[sp] = len[pre] + 1;
			fa[sp] = fa[preto];
			std::copy(ch[preto], ch[preto] + maxc, ch[sp]);
			while (pre and ch[pre][x] == preto)
				ch[pre][x] = sp, pre = fa[pre];
			fa[now] = fa[preto] = sp;
		}
	}
	else fa[now] = 1;
	return now;
}

int st[20][maxn], hb[maxn];
int *f = st[0], R[maxn];

inline int query (int l, int r) {
	int k = hb[r - l + 1];
	return std::max(st[k][l], st[k][r - (1 << k) + 1]);
}

int main () {
	scanf("%s", s + 1);
	scanf("%s", t + 1);
	int n = int(strlen(s + 1)), m = int(strlen(t + 1));

	int las = 1;
	for (int i = 1; i <= m; i ++)
		las = insert(las, t[i] - 'a');

	int now = 1;
	for (int i = 1; i <= n; i ++) {
		int x = s[i] - 'a';
		while (now and !ch[now][x]) now = fa[now];
		f[i] = std::min(f[i - 1], len[now]) + 1;
		now = now ? ch[now][x] : 1;
	}

	for (int i = 1; i <= n; i ++) {
		int &k = R[i] = R[i - 1];
		while (k + 1 <= n and k + 1 - f[k + 1] + 1 < i)
			++ k;
	}

	for (int i = n; i; i --)
		for (int k = 1; i + (1 << k) - 1 <= n; k ++)
			st[k][i] = std::max(st[k - 1][i], st[k - 1][i + (1 << k >> 1)]);
	for (int i = 2; i <= n; i ++)
		hb[i] = hb[i >> 1] + 1;

	int q = read;
	while (q --) {
		int l = read, r = read;
		if (R[l] >= r) printf("%d\n", r - l + 1);
		else printf("%d\n", std::max(R[l] - l + 1, query(R[l] + 1, r)));
	}
}
