#if 0
2020.05.03

  建 SAM ，考虑对于第 i 个分界，求出有 f[i] 个串会被割开。
  那么对于每个串，其对 f 的贡献就是一个区间和，而对于 SAM 的每个节点，其对 f 的贡献就是
一个区间等差数列，二次差分即可。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005, maxk = 10, mod = 1000000007;
int ch[maxn << 1][maxk], len[maxn << 1], fa[maxn << 1];
int first[maxn << 1], last[maxn << 1], cp = 1;
char s[maxn];
std::vector<int> G[maxn << 1];

int insert (int pre, int x) {
	int now = ++ cp;
	len[now] = len[pre] + 1;
	std::fill(ch[now], ch[now] + maxk, 0);
	while (pre && !ch[pre][x]) {
		ch[pre][x] = now;
		pre = fa[pre];
	}
	if (pre) {
		int preto = ch[pre][x];
		if (len[preto] == len[pre] + 1)
			fa[now] = preto;
		else {
			int sp = ++ cp;
			len[sp] = len[pre] + 1;
			fa[sp] = fa[preto];
			first[sp] = 1000000000;
			last[sp] = 0;
			for (int i = 0; i < maxk; i ++)
				ch[sp][i] = ch[preto][i];
			while (pre && ch[pre][x] == preto) {
				ch[pre][x] = sp;
				pre = fa[pre];
			}
			fa[now] = fa[preto] = sp;
		}
	} else
		fa[now] = 1;
	return now;
}

ll ans[maxn], Ans;

void dfs (int u) {
	for (int v : G[u]) {
		dfs(v);
		first[u] = std::min(first[u], first[v]);
		last[u] = std::max(last[u], last[v]);
	}
	if (!last[u]) return;
	if (first[u] == 1000000000) return;
	int l = last[u] - len[u] + 1, r = last[u] - len[fa[u]];
	if (l < first[u]) {
		r = std::min(r, first[u] - 1);
		ans[first[u]] -= r - l + 1;
		ans[first[u] + 1] += r - l + 1;
		ans[l] += 1;
		ans[r + 1] -= 1;
	}
	Ans += len[u] - len[fa[u]];
}

void rebuild () {
	for (int i = 1; i <= cp; i ++)
		G[i].clear();
	for (int i = 2; i <= cp; i ++)
		G[fa[i]].push_back(i);
	dfs(1);
}

int main () {
	int T = read;
	while (T --) {
		int n = read;
		cp = 1;
		int sam = 1;
		scanf("%s", s + 1);
		std::fill(ch[1], ch[1] + maxk, 0);
		for (int i = 1; i <= n; i ++) {
			sam = insert(sam, s[i] - '0');
			first[sam] = last[sam] = i;
		}
		std::fill(ans, ans + n + 1, 0);
		Ans = 0;
		rebuild();
		for (int i = 1; i <= n; i ++) ans[i] += ans[i - 1];
		for (int i = 1; i <= n; i ++) ans[i] += ans[i - 1];
		ll Final = 0, coe = 1;
		for (int i = n - 1; i; i --) {
			(Final += (Ans - ans[i]) % mod * coe) %= mod;
			(coe *= 100013) %= mod;
		}
		printf("%lld\n", Final);
		/* for (int i = 1; i < n; i ++) */
		/* 	debug(" %lld", Ans - ans[i]); */
		/* debug("\n"); */
	}
}
