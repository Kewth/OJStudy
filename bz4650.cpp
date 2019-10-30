#if 0
2019.10.29

设 a[i] 表示以 i 结尾的形如 AA 的子串数，b[i] 表示以 i 开头的形如 BB 的子串数。
那么答案就是 sum(a[i] b[i + 1]) 。
考虑求 a（求 b 是类似的），枚举 A 的长度 l ，设每个下标为 l 的整数倍的点为关键点。
那么每个长为 2l 的 AA 一定恰好经过两个相邻的关键点。
枚举这对相邻的关键点 (i, j)，求出 i, j 前缀的最长公共后缀 x 及 i, j 后缀的最长公共前缀 y 。
如果 x, y 拼起来 (x + y - 1) 的长度不小于 l ，那么就有 AA 经过这对关键点 (i, j) 。
具体是哪些 AA 也不难通过 x, y 算出来，它们的开头位置形成一个区间，可以用差分实现区间加值。
至于求两个前缀的最长公共后缀可以建出后缀自动机然后在 parent 树上求 lca 。
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 30005, maxk = 26, maxl = 16;
char s[maxn];
int ch[maxn << 2][maxk], len[maxn << 2], fa[maxn << 2][maxl], cp;
int deep[maxn << 2];
int pos[maxn][2];
int a[maxn], b[maxn];

void update(int x) {
	if(!x or deep[x]) return;
	update(*fa[x]);
	deep[x] = deep[*fa[x]] + 1;
	for(int k = 1; k < maxl; k ++)
		fa[x][k] = fa[fa[x][k - 1]][k - 1];
}

void build(int n, int t) {
	int last = ++ cp, begin = last;
	for(int _i = 1; _i <= n; _i ++) {
		int i = t ? n - _i + 1 : _i;
		int x = s[i] - 'a';
		int now = pos[i][t] = ++ cp;
		len[now] = len[last] + 1;

		int pre = last;
		while(pre and !ch[pre][x]) {
			ch[pre][x] = now;
			pre = *fa[pre];
		}

		if(pre) {
			int preto = ch[pre][x];
			if(len[preto] == len[pre] + 1)
				*fa[now] = preto;
			else {
				int sp = ++ cp;
				len[sp] = len[pre] + 1;
				*fa[sp] = *fa[preto];
				memcpy(ch[sp], ch[preto], sizeof ch[sp]);

				while(pre and ch[pre][x] == preto) {
					ch[pre][x] = sp;
					pre = *fa[pre];
				}

				*fa[preto] = sp;
				*fa[now] = sp;
			}
		}

		else
			*fa[now] = begin;

		last = now;
	}

	for(int i = begin; i <= cp; i ++) {
		update(i);
		/* debug("%d: l=%d, c=[%d,%d], f=%d, d=%d\n", */
		/* 		i, len[i], ch[i][0], ch[i][1], *fa[i], deep[i]); */
	}
}

int lca(int x, int y) {
	if(deep[x] < deep[y])
		std::swap(x, y);

	for(int k = maxl - 1; k >= 0; k --)
		if(deep[fa[x][k]] >= deep[y])
			x = fa[x][k];

	for(int k = maxl - 1; k >= 0; k --)
		if(fa[x][k] != fa[y][k]) {
			x = fa[x][k];
			y = fa[y][k];
		}

	return x == y ? x : *fa[x];
}

int main() {
	int T = read;

	while(T --) {
		cp = 0;
		memset(ch, 0, sizeof ch);
		memset(len, 0, sizeof len);
		memset(fa, 0, sizeof fa);
		memset(deep, 0, sizeof deep);
		memset(pos, 0, sizeof pos);
		memset(a, 0, sizeof a);
		memset(b, 0, sizeof b);

		scanf("%s", s + 1);
		int n = int(strlen(s + 1));

		build(n, 0);
		build(n, 1);

		for(int l = 1; l <= n; l ++) {
			for(int i = l << 1;	i <= n; i += l)
				if(s[i] == s[i - l]) {
					int x = std::min(l, len[lca(pos[i][0], pos[i - l][0])]);
					int y = std::min(l, len[lca(pos[i][1], pos[i - l][1])]);
					/* debug("%d %d %d %d\n", i - l, i, x, y); */
					int L = std::max(1, i - l - x + 1);
					int R = std::min(n, i + y - 1);
					if(x + y - 1 >= l) {
						b[L] ++;
						b[R - (l << 1) + 2] --;
						a[L + (l << 1) - 1] ++;
						a[R + 1] --;
					}
				}
		}

		for(int i = 1; i <= n; i ++) {
			a[i] += a[i - 1];
			b[i] += b[i - 1];
		}

		/* for(int i = 1; i <= n; i ++) */
		/* 	debug("%d %d\n", a[i], b[i]); */

		ll ans = 0;
		for(int i = 1; i < n; i ++)
			ans += 1ll * a[i] * b[i + 1];

		printf("%lld\n", ans);
	}
}
