#if 0
2020.05.01

同异或粽子。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned int ui;
typedef std::pair<ui, int> par;
typedef unsigned long long ull;

struct {
	inline operator ui () { ui x; return scanf("%u", &x), x; }
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 500005, maxk = 32;
int ch[maxn * (maxk + 1)][2], size[maxn * (maxk + 1)], cp;
int rk[maxn];
ui num[maxn];

void insert (int &now, ui x, int k) {
	if (!now) now = ++ cp;
	++ size[now];
	if (k >= 0)
		insert(ch[now][x >> k & 1], x, k - 1);
}

ui query (int now, ui x, int r, int k) {
	if (k < 0) return 0;
	int t = x >> k & 1;
	if (r <= size[ch[now][t]])
		return query(ch[now][t], x, r, k - 1);
	return 1u << k | query(ch[now][!t], x, r - size[ch[now][t]], k - 1);
}

int main () {
	int n = read, m = read, t = 0;
	for (int i = 1; i <= n; i ++)
		insert(t, num[i] = read, maxk - 1);

	std::priority_queue<par, std::vector<par>, std::greater<par> > q;
	for (int i = 1; i <= n; i ++)
		q.push(par(query(t, num[i], ++ ++ rk[i], maxk - 1), i));

	for (int i = 1; i <= m * 2; i ++) {
		par p = q.top();
		q.pop();
		/* debug("%u %d\n", p.first, p.second); */
		if (i & 1) printf("%u ", p.first);
		int id = p.second;
		q.push(par(query(t, num[id], ++ rk[id], maxk - 1), id));
	}
	puts("");
}
