#if 0
2020.05.08

  问题可以看做三维数点，直接做 3 个 log ，众所周知扫描线或者 cdq 分治可以干掉一维做到两
个 log ，但不在讨论范围内。
  这个问题比较特殊，数点是数最小值，并且是数某一个维度的最小值，那么在该维度上使用扫描
线的同时可以贪心，具体的，按时间从小到大加入元素，如果扫描的是被询问的元素，那么在所有
当前被扫描到的另外两个维度满足条件的未确定答案的询问元素的答案就是当前扫描到这个元素。
用一个数据结结构维护所有未确定答案的询问元素，每扫描一个被询问元素就逐个查询满足条件的
询问元素确定答案并删除之，每扫描一个询问元素就加入这个数据结构。
  这个数据结构只关心另外两个维度，需要在二维空间中支持：
  1) 查询一个矩形内的任意一个点
  2) 加入一个点
  3) 删除一个矩形内的任意一个点
  乍一看还是要两个 log ，但事实上由于此时点没有任何权值标识，可以将一个维度用键值，另一
个维度用权值放在一个一维数据结构内维护起来，一颗普通的线段树就足以胜任。
#endif
#include <cstdio>
#include <algorithm>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 400005;
struct shit {
	int l, r, t, i, o;
} a[maxn << 1];
int ans[maxn];
int tmp[maxn];
par seg[maxn << 2], INF = par(1000000000, 1000000000);
std::set<par> set[maxn];

void insert (int now, int L, int R, int p, par x) {
	if (L == R) {
		set[p].insert(x);
		seg[now] = *set[p].begin();
		return;
	}
	int M = (L + R) >> 1;
	if (p <= M) insert(now << 1, L, M, p, x);
	else insert(now << 1 | 1, M + 1, R, p, x);
	seg[now] = std::min(seg[now << 1], seg[now << 1 | 1]);
}

void pop (int now, int L, int R, int p) {
	if (L == R) {
		set[p].erase(set[p].begin());
		seg[now] = *set[p].begin();
		return;
	}
	int M = (L + R) >> 1;
	if (p <= M) pop(now << 1, L, M, p);
	else pop(now << 1 | 1, M + 1, R, p);
	seg[now] = std::min(seg[now << 1], seg[now << 1 | 1]);
}

par query (int now, int L, int R, int l, int r) {
	if (r < L or l > R) return INF;
	if (l <= L and R <= r) return seg[now];
	int M = (L + R) >> 1;
	return std::min(query(now << 1, L, M, l, r),
			query(now << 1 | 1, M + 1, R, l, r));
}

void build (int now, int L, int R) {
	seg[now] = INF;
	if (L == R)
		return set[L].insert(INF), void();
	int M = (L + R) >> 1;
	build(now << 1, L, M);
	build(now << 1 | 1, M + 1, R);
}

int main () {
	int n = read, m = read, p = 0;
	for (int i = 1; i <= n; i ++) {
		a[++ p].o = 1;
		read(a[p].l, a[p].r, a[p].t);
		a[p].i = p;
	}
	for (int i = 1; i <= m; i ++) {
		a[++ p].o = 2;
		read(a[p].l, a[p].r, a[p].t);
		a[p].i = p;
	}

	int t = 0;
	for (int i = 1; i <= p; i ++) {
		tmp[++ t] = a[i].l;
		tmp[++ t] = a[i].r;
	}

	std::sort(tmp + 1, tmp + t + 1);
	for (int i = 1; i <= p; i ++) {
		a[i].l = int(std::lower_bound(tmp + 1, tmp + t + 1, a[i].l) - tmp);
		a[i].r = int(std::lower_bound(tmp + 1, tmp + t + 1, a[i].r) - tmp);
	}

	std::sort(a + 1, a + p + 1, [] (shit x, shit y) {
				return x.t == y.t ? x.o > y.o : x.t < y.t;
			});

	build(1, 1, t);

	for (int i = 1; i <= p; i ++) {
		if (a[i].o == 1) {
			par x = query(1, 1, t, a[i].l, a[i].r);
			while (x.first <= a[i].r) {
				int j = x.second;
				ans[a[j].i] = a[i].i;
				pop(1, 1, t, a[j].l);
				x = query(1, 1, t, a[i].l, a[i].r);
			}
		}
		if (a[i].o == 2)
			insert(1, 1, t, a[i].l, par(a[i].r, i));
	}

	for (int i = n + 1; i <= n + m; i ++)
		printf("%d ", ans[i] ? ans[i] : -1);
	puts("");
}
