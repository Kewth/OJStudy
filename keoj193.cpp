#if 0
2020.05.27

  才知道反串建 SAM 有一个很优秀的性质，任意一个节点对应的子串在所有子串中的字典序排名是
连续的。那么只要把反串的 SAM 的所有节点按字典序排序，就能间接把所有子串排序。而对 SAM 的
节点排序，只需要在 parent 树上 dfs ，每次先走字典序小的儿子，得到的先序遍历序就是排序的
结果。
  排序后记录前缀和信息，对于询问二分到对应的位置即可，复杂度 O(n + qlogn) 。
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
#include <cstring>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 500005, maxk = 26;
char s[maxn];

int ch[maxn << 1][maxk], len[maxn << 1], fa[maxn << 1];
int times[maxn << 1], any[maxn << 1], cp = 1;
std::vector<int> G[maxn << 1];

int insert (int pre, int x) {
	int now = ++ cp;
	len[now] = len[pre] + 1;
	times[now] = 1;
	while (pre and !ch[pre][x]) {
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
			for (int i = 0; i < maxk; i ++)
				ch[sp][i] = ch[preto][i];
			while (pre and ch[pre][x] == preto) {
				ch[pre][x] = sp;
				pre = fa[pre];
			}
			fa[now] = fa[preto] = sp;
		}
	} else
		fa[now] = 1;
	return now;
}

int nodesa[maxn << 1], np;
ll pre[maxn << 1];

void dfs1 (int u) {
	for (int v : G[u]) {
		dfs1(v);
		times[u] += times[v];
		any[u] = any[v];
	}
}

void dfs2 (int u) {
	nodesa[++ np] = u;
	std::sort(G[u].begin(), G[u].end(), [u] (int x, int y) {
				return s[any[x] + len[u]] < s[any[y] + len[u]];
			});
	for (int v : G[u])
		dfs2(v);
}

void rebuild () {
	for (int i = 2; i <= cp; i ++)
		G[fa[i]].push_back(i);
	dfs1(1);
	dfs2(1);
	for (int i = 1; i <= np; i ++) {
		int u = nodesa[i];
		pre[i] = pre[i - 1] + 1ll * times[u] *
			(len[u] + len[fa[u]] + 1) * (len[u] - len[fa[u]]) / 2;
	}
}

int main () {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1));

	int now = 1;
	for (int i = n; i; i --) {
		now = insert(now, s[i] - 'a');
		any[now] = i;
	}
	rebuild();

	int q = read;
	while (q --) {
		ll p = read;
		int get = int(std::lower_bound(pre + 1, pre + np + 1, p) - pre);

		p -= pre[get - 1];
		int u = nodesa[get];
		int l = len[fa[u]] + 1, r = len[u];
		while (l < r) {
			int mid = (l + r) >> 1;
			if (p <= 1ll * times[u] * (mid + len[fa[u]] + 1) * (mid - len[fa[u]]) / 2)
				r = mid;
			else
				l = mid + 1;
		}

		p -= 1ll * times[u] * (l + len[fa[u]]) * (l - len[fa[u]] - 1) / 2;
		p = (p - 1) % l + 1;
		putchar(s[any[u] + p - 1]);
	}
	puts("");
}
