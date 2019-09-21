#if 0
2019.09.20

线段树分治，里头存带撤销的并查集。
#endif
#include <cstdio>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 5005, maxq = 500005;
int head[maxq * 3], nxt[maxq * 40], edge[maxq * 40], hp;
int tot[maxq * 3];
int query[maxq * 3];

void add(int now, int L, int R, int l, int r, int e) {
	if(r < L or l > R)
		return;

	if(l <= L and R <= r) {
		nxt[++ hp] = head[now];
		head[now] = hp;
		edge[hp] = e;
		return;
	}

	int M = (L + R) >> 1;
	add(now << 1, L, M, l, r, e);
	add(now << 1 | 1, M + 1, R, l, r, e);
}

void ask(int now, int L, int R, int p, int e) {
	tot[now] ++;
	if(L == R) {
		query[now] = e;
		return;
	}
	int M = (L + R) >> 1;
	if(p <= M)
		ask(now << 1, L, M, p, e);
	else
		ask(now << 1 | 1, M + 1, R, p, e);
}

int fa[maxn], deep[maxn];
int tmp[maxq];

inline int find(int x) {
	while(fa[x] != x)
		x = fa[x];
	return x;
}

void solve(int now, int L, int R) {
	if(!tot[now])
		return;

	for(int i = head[now]; i; i = nxt[i]) {
		int x = edge[i] / maxn, y = edge[i] % maxn;
		x = find(x);
		y = find(y);
		if(x != y) {
			if(deep[x] > deep[y])
				fa[y] = x;
			else if(deep[x] < deep[y])
				fa[x] = y;
			else {
				fa[x] = y;
				deep[y] ++;
			}
		}
		edge[i] = x * maxn + y;
	}

	if(L == R) {
		int x = query[now] / maxn, y = query[now] % maxn;
		/* debug("%d : %d %d|%d %d\n", now, x, y, find(x), find(y)); */
		if(find(x) == find(y))
			puts("Y");
		else
			puts("N");
	}

	else {
		int M = (L + R) >> 1;
		solve(now << 1, L, M);
		solve(now << 1 | 1, M + 1, R);
	}

	int p = 0;
	for(int i = head[now]; i; i = nxt[i])
		tmp[++ p] = edge[i];

	for(int i = p; i; i --) {
		int x = tmp[i] / maxn, y = tmp[i] % maxn;
		if(x != y) {
			if(fa[x] == y)
				fa[x] = x;
			if(fa[y] == x)
				fa[y] = y;
		}
	}
}

int main() {
	int n = input(), q = input();

	std::map<int, int> last;

	for(int i = 1; i <= q; i ++) {
		int op = input(), x = input(), y = input();
		if(x > y)
			std::swap(x, y);
		if(op == 0)
			last[x * maxn + y] = i;
		else if(op == 1) {
			add(1, 1, q, last[x * maxn + y], i, x * maxn + y);
			last.erase(x * maxn + y);
		}
		else
			ask(1, 1, q, i, x * maxn + y);
	}

	for(auto pr : last)
		add(1, 1, q, pr.second, q, pr.first);

	for(int i = 1; i <= n; i ++)
		fa[i] = i;

	solve(1, 1, q);
}
