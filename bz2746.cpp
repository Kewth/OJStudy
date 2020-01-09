#if 0
2020.01.09

对于两个询问串 a, b ，答案串 s 是它们的公共后缀，又在 Trie 树中出现过。
这个 s 自然就是 a, b 在 ACAM 的 fail 树上的 lca 。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 1000005, maxk = 26, maxl = 20, mod = 1000000007;
int ch[maxn][maxk], cp = 1;
ll hash[maxn];
std::vector<int> find[maxn];
int fa[maxn][maxl];
int deep[maxn];

void insert(char *s, int id) {
	int now = 1;
	find[id].push_back(now);
	for(int i = 0; s[i]; i ++) {
		int &to = ch[now][s[i] - 'a'];
		if(!to) {
			to = ++ cp;
			hash[to] = (hash[now] * 26 + s[i] - 'a') % mod;
		}
		now = to;
		find[id].push_back(now);
	}
}

void build() {
	std::queue<int> q;
	q.push(1);
	for(int x = 0; x < maxk; x ++)
		ch[0][x] = 1;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		deep[u] = deep[*fa[u]] + 1;
		for(int k = 1; k < maxl; k ++)
			fa[u][k] = fa[fa[u][k - 1]][k - 1];
		for(int x = 0; x < maxk; x ++) {
			int &v = ch[u][x];
			if(v) {
				*fa[v] = ch[*fa[u]][x];
				q.push(v);
			} else
				v = ch[*fa[u]][x];
		}
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

char s[maxn];
int main() {
	int n = read;
	for(int i = 1; i <= n; i ++) {
		scanf("%s", s);
		insert(s, i);
	}

	build();

	int q = read;
	while(q --) {
		int ai = read, ap = read, bi = read, bp = read;
		int a = find[ai][unsigned(ap)];
		int b = find[bi][unsigned(bp)];
		printf("%lld\n", hash[lca(a, b)]);
	}
}
