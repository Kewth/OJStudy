#if 0
2019.12.28

学习了一发广义 SAM ，感觉就是一玄学，又回到了当年学 SAM 的状态。

对于原树建广义 SAM ，那么对于串 S ，考虑一个个添加字符的同时更新答案。
每添加一个字符多出的子串是当前 S 的所有后缀，找到当前最大的能在后缀自动机上表示的后缀 k ，
设 k 的长度为 curlen ，那么长度不超过 curlen 的后缀都能在 SAM 上表示，
也就是都能在原树上找到路径匹配。

在 SAM 上树上差分求出每个状态的出现次数。
然后 k 的贡献就是不断跳 parent 树的父亲边的同时统计答案，
预处理出跳到每个点的答案贡献，再树上差分，就能 O(1) 得到一个状态到根的贡献和。
#endif
#include <cstdio>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 800005, maxk = 3;
int ch[maxn << 1][maxk], len[maxn << 1], fa[maxn << 1];
int times[maxn << 1];
ll f[maxn << 1];
int pos[maxn];
std::vector<int> G[maxn << 1];
char s[8000000]; // S 的范围？

void dfs1(int u) {
	for(int v : G[u]) {
		dfs1(v);
		times[u] += times[v];
	}
}

void dfs2(int u) {
	for(int v : G[u]) {
		f[v] += f[u] + 1ll * times[u] * (len[u] - len[fa[u]]);
		dfs2(v);
	}
}

int main() {
	int n = read;
	int cp = 1;
	pos[1] = 1;

	for(int u = 2; u <= n; u ++) {
		int pre = pos[int(read)];
		int x = char(read) - 'a';
		int now = ++ cp;
		len[now] = len[pre] + 1;
		times[now] = 1;

		while(pre and !ch[pre][x]) {
			ch[pre][x] = now;
			pre = fa[pre];
		}

		if(pre) {
			int preto = ch[pre][x];
			if(len[preto] == len[pre] + 1)
				fa[now] = preto;
			else {
				int sp = ++ cp;
				len[sp] = len[pre] + 1;
				fa[sp] = fa[preto];
				for(int i = 0; i < maxk; i ++)
					ch[sp][i] = ch[preto][i];
				fa[preto] = fa[now] = sp;
				while(pre and ch[pre][x] == preto) {
					ch[pre][x] = sp;
					pre = fa[pre];
				}
			}
		}
		else
			fa[now] = 1;
		pos[u] = now;
	}

	/* for(int i = 1; i <= cp; i ++) */
	/* 	debug("%d: len=%d c=%d,%d,%d fa=%d\n", */
	/* 			i, len[i], ch[i][0], ch[i][1], ch[i][2], fa[i]); */

	for(int i = 2; i <= cp; i ++)
		G[fa[i]].push_back(i);

	dfs1(1);
	dfs2(1);

	ll ans = 0;
	scanf("%s", s);
	int now = 1, curlen = 0;
	for(char *p = s; *p; ++ p) {
		int x = *p - 'a';
		if(ch[now][x]) {
			now = ch[now][x];
			++ curlen;
		}
		else {
			while(now and !ch[now][x])
				now = fa[now];
			if(now) {
				curlen = len[now] + 1;
				now = ch[now][x];
			} else {
				now = 1;
				curlen = 0;
			}
		}
		/* debug("%d %d\n", now, curlen); */
		ans += 1ll * times[now] * (curlen - len[fa[now]]) + f[now];
	}

	printf("%lld\n", ans);
}
