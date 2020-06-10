/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.09

 * Solution:
    注意到 k * q 一定，阈值分块，对 s 建 SAM 。
    如果 k 较小，每个 t 暴力把每个子串扔到 SAM 里跑得到出现次数，然后只需要对于每个
[l, r] 查询它在 a 到 b 之间出现了多少次，预处理 + 二分即可。
    如果 q 较小，把 t 的每个前缀扔进去 SAM ，得到每个前缀的位置，和每个前缀匹配的最
大长度（最长的出现在 s 的后缀），然后每个子串在 s 的位置就可以在 parent 树上倍增来定
位到，暴力扫 a 到 b 的每个区间即可。
    两者复杂度分别为 O(q k^2 logm) 和 O(q m logn) ，总复杂度 O(S sqrt(m) log) ，其中
S 为 k 和 q 的乘积。

 * Digression:
  没了板子后缀自动机果然打错了。

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
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005, maxc = 26, maxk = 18;
int Fa[maxk][maxn << 1], *fa = Fa[0];
int ch[maxn << 1][maxc], len[maxn << 1], times[maxn << 1], cp = 1;
std::vector<int> G[maxn << 1];

int insert (int pre, int x) {
	int now = ++ cp;
	len[now] = len[pre] + 1;
	times[now] = 1;
	while (pre and !ch[pre][x])
		ch[pre][x] = now, pre = fa[pre];
	if (pre) {
		int preto = ch[pre][x];
		if (len[preto] == len[pre] + 1)
			fa[now] = preto;
		else {
			int sp = ++ cp;
			len[sp] = len[pre] + 1;
			/* fa[sp] = pre; */ // 艹艹艹
			fa[sp] = fa[preto];
			std::copy(ch[preto], ch[preto] + maxc, ch[sp]);
			while (pre and ch[pre][x] == preto)
				ch[pre][x] = sp, pre = fa[pre];
			fa[now] = fa[preto] = sp;
		}
	} else
		fa[now] = 1;
	return now;
}

void dfs (int u) {
	for (int k = 1; k < maxk; k ++)
		Fa[k][u] = Fa[k - 1][Fa[k - 1][u]];
	/* debug("%d : len=%d fa=%d ch={%d,%d} t=%d\n", */
	/* 		u, len[u], fa[u], ch[u][0], ch[u][1], times[u]); */
	for (int v : G[u]) {
		dfs(v);
		times[u] += times[v];
	}
}

char s[maxn], t[maxn];
int spos[maxn];
int tpos[maxn], tlen[maxn];
int ml[maxn], mr[maxn];

void solve1 (int, int, int q, int K) {
	while (q --) {
		scanf("%s", t + 1);
		tpos[0] = 1;
		for (int i = 1; i <= K; i ++) {
			int &now = tpos[i] = tpos[i - 1], x = t[i] - 'a';
			tlen[i] = tlen[i - 1];
			while (now and !ch[now][x]) {
				now = fa[now];
				tlen[i] = std::min(tlen[i], len[now]);
			}
			now = now ? ch[now][x] : 1;
			++ tlen[i];
		}
		int a = read + 1, b = read + 1;
		ll ans = 0;
		for (int i = a; i <= b; i ++) {
			int now = tpos[mr[i]];
			if (tlen[mr[i]] < mr[i] - ml[i] + 1) continue;
			for (int k = maxk - 1; k >= 0; k --)
				if (len[Fa[k][now]] >= mr[i] - ml[i] + 1)
					now = Fa[k][now];
			// XXX: to be optimized
			/* while (len[fa[now]] >= mr[i] - ml[i] + 1) */
			/* 	now = fa[now]; */
			ans += times[now];
		}
		printf("%lld\n", ans);
	}
}

void solve2 (int, int m, int q, int K) {
	static std::vector<int> set[600][600];
	for (int i = 1; i <= m; i ++)
		set[ml[i]][mr[i]].push_back(i);
	while (q --) {
		scanf("%s", t + 1);
		int a = read, b = read + 1;
		ll ans = 0;
		for (int l = 1; l <= K; l ++) {
			int now = 1;
			for (int r = l; r <= K; r ++) {
				std::vector<int> &S = set[l][r];
				now = ch[now][t[r] - 'a'];
				if (!now) break;
				if (S.size() <= 8) {
					for (size_t i = 0; i < S.size(); i ++)
						if (a < S[i] and S[i] <= b)
							ans += times[now];
				}
				else {
					ans += 1ll * times[now] * int(std::upper_bound(S.begin(),
								S.end(), b) - S.begin());
					ans -= 1ll * times[now] * int(std::upper_bound(S.begin(),
								S.end(), a) - S.begin());
				}
			}
		}
		printf("%lld\n", ans);
	}
}

int main () {
	int n = read, m = read, q = read, K = read;
	scanf("%s", s + 1);
	len[0] = -1;
	spos[0] = 1;
	for (int i = 1; i <= n; i ++)
		spos[i] = insert(spos[i - 1], s[i] - 'a');
	for (int i = 1; i <= m; i ++) {
		ml[i] = read + 1;
		mr[i] = read + 1;
	}

	for (int i = 2; i <= cp; i ++)
		G[fa[i]].push_back(i);
	dfs(1);

	if (q <= 310)
		solve1(n, m, q, K);
	else
		solve2(n, m, q, K);
}
