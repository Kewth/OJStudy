#if 0
2020.02.29

建 AC 自动机，子串统计转换为对于每个前缀统计后缀，那么询问转换为：
给定若干点（每个前缀），对于每个点，求出其跳 fail 能到达多少满足
id 在 [l, r] 之间的单词节点。

把询问 [l, r] 拆成 [1, l - 1] 和 [1, r] 两个，然后将询问按 r 排序。
由于 r 升序，可以一个一个考虑单词节点产生的影响。

设串长和为 m ，对于参数 B ，把询问分成两类：

给定点数（串长）小于 B 。
这部分在每次询问都 O(B) 枚举所有给定点，然后求 fail 树祖先的贡献和。
每个点的贡献影响的是一颗子树，对应的就是 dfs 序一段区间。
而查询只需要单点查询，将 dfs 序分块，这部分可以做到 O(q B + n sqrt(m)) 。

给定点数（串长）不小于 B 。
这部分不能枚举所有点，但是这部分询问串的种数不超过 m / B 。
对于这类每个询问串，把贡献方式反过来，
初始设所有给定点的权值为 1 ，每加入一个点就求 fail 树上的子树和，
这个子树和就是这个点的贡献。
那么只需要对每个串预处理子树和即可，这部分可以做到 O(q + m^2 / B) 。

综上，设 n, m, q 同阶，B = O(sqrt(n)) 时总复杂度 O(n sqrt(n) + n logn) 。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005, S = 340, B = 340;

struct Que {
	int r, k, id, o;
} qu[maxn << 1];
char s[maxn];
int ch[maxn][26], from[maxn], fail[maxn], tp = 1;
int pos[maxn];
std::vector<int> G[maxn];
int id[maxn], size[maxn], ip;

void get_fail() {
	std::queue<int> q;
	q.push(1);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		G[fail[u]].push_back(u);
		for(int x = 0; x < 26; x ++)
			if(ch[u][x]) {
				int p = fail[u];
				while(p and !ch[p][x])
					p = fail[p];
				fail[ch[u][x]] = p ? ch[p][x] : 1;
				q.push(ch[u][x]);
			}
	}
}

void dfs(int u, int *val) {
	if(!id[u]) id[u] = ++ ip;
	for(int v : G[u]) {
		dfs(v, val);
		val[u] += val[v];
	}
}

const int AB = 340;
struct Array {
	int a[maxn], t[AB];
	void add(int l, int r) {
		// debug("%d %d\n", l, r);
		if(l / AB == r / AB)
			for(int i = l; i <= r; i ++)
				++ a[i];
		else {
			for(int i = l; i / AB == l / AB; i ++)
				++ a[i];
			for(int i = r; i / AB == r / AB; i --)
				++ a[i];
			for(int i = l / AB + 1; i < r / AB; i ++)
				++ t[i];
		}
	}
	inline int get(int k) { return a[k] + t[k / AB]; }
} ar;

int big[S], bid[maxn], bp;
int bval[S][maxn];
ll ans[maxn], bans[S];

void add(int k) {
	int p = pos[k];
	ar.add(id[p], id[p] + size[p] - 1);
	for(int i = 1; i <= bp; i ++)
		bans[i] += bval[i][p];
}

int main() {
	int n = read, q = read;
	for(int i = 1; i <= n; i ++) {
		int &now = pos[i] = 1, len = 0;
		scanf("%s", s);
		for(int &j = len; s[j]; j ++) {
			int &to = ch[now][s[j] - 'a'];
			if(!to) from[to = ++ tp] = now;
			now = to;
		}
		if(len >= B)
			big[bid[i] = ++ bp] = i;
	}

	get_fail();
	for(int i = 1; i <= tp; i ++)
		size[i] = 1;
	dfs(1, size);

	// for(int i = 1; i <= tp; i ++)
		// debug("%d: {%d %d} fa=%d id=%d sz=%d\n",
				// i, ch[i][0], ch[i][1], fail[i], id[i], size[i]);

	for(int i = 1; i <= bp; i ++) {
		for(int x = pos[big[i]]; x; x = from[x])
			bval[i][x] = 1;
		dfs(1, bval[i]);
	}

	for(int i = 1; i <= q; i ++) {
		int l = read, r = read, k = read;
		qu[i * 2 - 1] = {l - 1, k, i, -1};
		qu[i * 2] = {r, k, i, 1};
	}

	std::sort(qu + 1, qu + q * 2 + 1, [](Que a, Que b) {
				return a.r < b.r;
			});

	int now = 0;
	for(int i = 1; i <= q * 2; i ++) {
		int r = qu[i].r, k = qu[i].k, I = qu[i].id, o = qu[i].o;
		while(now < r)
			add(++ now);
		if(bid[k])
			ans[I] += bans[bid[k]] * o;
		else
			for(int x = pos[k]; x; x = from[x])
				ans[I] += ar.get(id[x]) * o;
	}

	for(int i = 1; i <= q; i ++)
		printf("%lld\n", ans[i]);
}
