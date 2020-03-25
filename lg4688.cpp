#if 0
2020.03.24

妙啊。
屁，又卡空间，有瘾？
考虑算相交部分的数量，莫队套 bitset 即可。
#endif
#include <cstdio>
#include <algorithm>
#include <bitset>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 100005, SHIT = 34000;
int a[maxn], tmp[maxn];
std::bitset<maxn> b, Ans[SHIT];
size_t pos[maxn];
struct Query {
	int l, r, o, id;
} qu[maxn * 3], que[maxn * 3];
int ans[maxn];

void add (int x) {
	b[pos[a[x]] ++] = 1;
}

void remove (int x) {
	b[-- pos[a[x]]] = 0;
}

void solve (int n, int q, int l, int r) {
	int p = 0;
	for (int i = 1; i <= q; i ++)
		if (l <= qu[i].id and qu[i].id <= r)
			que[++ p] = qu[i];

	for (int i = 1; i <= p; i ++)
		ans[que[i].id] += que[i].r - que[i].l + 1;

	int B = 500;
	std::sort(que + 1, que + p + 1, [&] (Query x, Query y) {
				if (x.l / B == y.l / B)
					return x.l / B & 1 ? x.r > y.r : x.r < y.r;
				return x.l < y.l;
			});

	for (int i = 1; i <= n; i ++)
		pos[a[i]] = size_t(a[i]);
	b.reset();

	for (int i = 0; i <= r - l; i ++)
		Ans[i].set();

	int L = 1, R = 0;
	for (int i = 1; i <= p; i ++) {
		while (L > que[i].l) add(-- L);
		while (R < que[i].r) add(++ R);
		while (L < que[i].l) remove(L ++);
		while (R > que[i].r) remove(R --);
		if (l <= que[i].id and que[i].id <= r)
		Ans[que[i].id - l] &= b;
	}
}

int main () {
	int n = read, q = read;
	for (int i = 1; i <= n; i ++)
		tmp[i] = a[i] = read;
	std::sort(tmp + 1, tmp + n + 1);
	for (int i = 1; i <= n; i ++)
		a[i] = int(std::lower_bound(tmp + 1, tmp + n + 1, a[i]) - tmp);

	for (int i = 1; i <= q * 3; i ++)
		read(qu[i].l, qu[i].r), qu[i].o = i % 3, qu[i].id = (i - 1) / 3 + 1;

	for (int i = 1; i <= q; i += SHIT) {
		solve(n, q * 3, i, i + SHIT - 1);
		for (int j = i; j < i + SHIT and j <= q; j ++)
			printf("%d\n", ans[j] -= Ans[j - i].count() * 3);
	}

	/* for (int i = 1; i <= q; i ++) { */
	/* 	debug("%lu ", Ans[i].count()); */
	/* 	for (size_t j = 1; j <= 5; j ++) */
	/* 		debug("%d", int(Ans[i][j])); */
	/* 	debug("\n"); */
	/* } */
}
