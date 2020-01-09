#if 0
2020.01.09

建 ACAM ，在上面 DP 设 f[i][j] 表示长为 i 的串在 ACAM 的节点 j 的方案数。
g[i][j] 表示同样情况下已经匹配过了完整单词的方案数。
踩坑：一个节点只要跳 fail 能跳到单词节点就可以匹配，并不一定要恰为单词节点。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 105, maxk = 26, mod = 10007;
int ch[maxn * maxn][maxk], cp = 1;
bool word[maxn * maxn];
int fail[maxn * maxn];
int f[maxn][maxn * maxn], g[maxn][maxn * maxn];

void build() {
	std::queue<int> q;
	q.push(1);
	for(int x = 0; x < maxk; x ++)
		ch[0][x] = 1;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		word[u] |= word[fail[u]];
		for(int x = 0; x < maxk; x ++)
			if(ch[u][x]) {
				fail[ch[u][x]] = ch[fail[u]][x];
				q.push(ch[u][x]);
			} else
				ch[u][x] = ch[fail[u]][x];
	}
}

char s[maxn];
int main() {
	int n = read, m = read;
	for(int i = 1; i <= n; i ++) {
		scanf("%s", s + 1);
		int now = 1;
		for(int j = 1; s[j]; j ++) {
			int &to = ch[now][s[j] - 'A'];
			if(!to) to = ++ cp;
			now = to;
		}
		word[now] = 1;
	}

	build();

	f[0][1] = 1;
	for(int i = 0; i < m; i ++) {
		for(int j = 1; j <= cp; j ++) {
			for(int x = 0; x < maxk; x ++) {
				(f[i + 1][ch[j][x]] += f[i][j]) %= mod;
				(g[i + 1][ch[j][x]] += g[i][j]) %= mod;
			}
		}
		for(int j = 1; j <= cp; j ++)
			if(word[j])
				g[i + 1][j] = f[i + 1][j];
	}

	/* for(int j = 1; j <= cp; j ++) */
	/* 	debug("%d -> %d %d %d\n", j, ch[j][0], ch[j][1], ch[j][2]); */

/* 	for(int i = 1; i <= m; i ++) */
/* 		for(int j = 1; j <= cp; j ++) */
/* 			if(g[i][j]) */
/* 				debug("%d, %d : %d %d\n", i, j, f[i][j], g[i][j]); */

	int ans = 0;
	for(int j = 1; j <= cp; j ++)
		ans += g[m][j];
	ans %= mod;

	printf("%d\n", ans);
}
