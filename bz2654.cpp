#if 0
2019.10.28

wqs 二分，将问题放在二维平面上更加直观。
二分一个 k（对应斜率）将所有白边边权减去 k 求出 mst ，
根据得出的 mst 中的白边数量与 need 比较然后调整 k ，
最后即可弄出恰好 need 条边的 mst 得出答案。
需要注意边界，即当前 k 有多种 mst 的方案且使用的白边不同（对应多点共线）。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	operator int () { int x; scanf("%d", &x); return x; }
	template<class T> void operator () (T &x) { x = *this; }
	template<class T, class ...A> void operator () (T &x, A &...a) { x = *this; (*this)(a...); }
} read;

const int maxn = 100005;
int s[maxn], t[maxn], v[maxn], c[maxn], p[maxn];
int fa[maxn];

int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

bool cmp(int x, int y) {
	if(v[x] == v[y]) return c[x] > c[y];
	return v[x] < v[y];
}

int n, m;
int sum;
int check(int k) {
	for(int i = 1; i <= m; i ++)
		v[i] -= k * c[i];

	for(int i = 1; i <= m; i ++)
		p[i] = i;

	for(int i = 1; i <= n; i ++)
		fa[i] = i;

	std::sort(p + 1, p + m + 1, cmp);

	int res = 0;
	sum = 0;

	for(int id = 1; id <= m; id ++) {
		int i = p[id];
		if(find(s[i]) != find(t[i])) {
			/* debug("%d %d %d\n", s[i], t[i], v[i]); */
			res += c[i];
			sum += v[i] + c[i] * k;
			fa[find(s[i])] = find(t[i]);
		}
	}

	for(int i = 1; i <= m; i ++)
		v[i] += k * c[i];

	/* debug("%d : (%d, %d)\n", k, res, sum); */

	return res;
}

int main() {
	read(n, m);
	int need = read;

	for(int i = 1; i <= m; i ++) {
		s[i] = read + 1;
		t[i] = read + 1;
		v[i] = read;
		c[i] = 1 - read;
	}

	int l = - 100, r = 100;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(check(mid) >= need)
			r = mid;
		else
			l = mid + 1;
	}

	int d = check(l) - need;
	sum -= d * l;

	printf("%d\n", sum);
}
