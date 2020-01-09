#if 0
2020.01.09

通过 SAM 间接枚举所有本质不同的子串，

对于第一种询问，如果一个长为 l 的子串出现了 k 次，就对 ans1[l] 有 C(k, 2) 的贡献。
而 SAM 一个节点所代表的子串中出现次数是相同的，长度是连续的，
因此对 ans1 的贡献就是一个区间加法，可以用差分前缀和实现。

对于第二种询问，如果一个长为 l 的子串的左端点权值最大次大最小次小值都知道，
那么对 ans2[l] 的贡献也容易知道，这个贡献是个取 max 。
但是 SAM 一个节点所代表子串的左端点却是不同的，
然而只需要把串翻转一下，使得串的权值只与右端点有关，
这样 SAM 一个节点所代表子串的右端点权值最大次大最小次小值都完全相同，
因此对 ans2 的贡献就是一个区间取 max ，可以用线段树实现。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 300005, maxk = 26, inf = 1000000000;
struct Data {
	int max, semax, min, semin;
	Data(): max(-inf), semax(-inf), min(inf), semin(inf) { }
	Data(int x): max(x), semax(-inf), min(x), semin(inf) { }
	void operator += (Data an) {
		int a[8] = {max, semax, an.max, an.semax, min, semin, an.min, an.semin};
		std::sort(a, a + 4);
		semax = a[2];
		max = a[3];
		std::sort(a + 4, a + 8);
		min = a[4];
		semin = a[5];
	}
	inline ll get() {
		return std::max(1ll * max * semax, 1ll * min * semin);
	}
};
int ch[maxn << 1][maxk], len[maxn << 1], fa[maxn << 1];
int times[maxn << 1], cp = 1;
Data val[maxn << 1];
std::vector<int> G[maxn << 1];

int insert(int pre, int x) {
	int now = ++ cp;
	len[now] = len[pre] + 1;
	while(pre and !ch[pre][x]) {
		ch[pre][x] = now;
		pre = fa[pre];
	}
	if(pre) {
		int preto = ch[pre][x];
		if(len[preto] == len[pre] + 1)
			fa[now] = preto;
		else {
			int sp = ++ cp;
			len[sp] = len[pre] + 1;
			fa[sp] = fa[preto];
			for(int i = 0; i < maxk; i ++)
				ch[sp][i] = ch[preto][i];
			while(pre and ch[pre][x] == preto) {
				ch[pre][x] = sp;
				pre = fa[pre];
			}
			fa[now] = fa[preto] = sp;
		}
	} else
		fa[now] = 1;
	return now;
}

void dfs(int u) {
	for(int v : G[u]) {
		dfs(v);
		times[u] += times[v];
		val[u] += val[v];
	}
}

char s[maxn];
int a[maxn];
ll sum[maxn];
ll seg[maxn << 2];
void modify(int now, int L, int R, int l, int r, ll x) {
	if(r < L or l > R) return;
	if(l <= L and R <= r) return seg[now] = std::max(seg[now], x), void();
	int M = (L + R) >> 1;
	modify(now << 1, L, M, l, r, x);
	modify(now << 1 | 1, M + 1, R, l, r, x);
}

ll query(int now, int L, int R, int p) {
	if(L == R) return seg[now];
	int M = (L + R) >> 1;
	if(p <= M) return std::max(seg[now], query(now << 1, L, M, p));
	else return std::max(seg[now], query(now << 1 | 1, M + 1, R, p));
}

int main() {
	std::fill(seg, seg + (maxn << 2), - 1ll * inf * inf);

	int n = read;
	scanf("%s", s + 1);
	for(int i = 1; i <= n; i ++)
		read(a[i]);
	std::reverse(s + 1, s + n + 1);
	std::reverse(a + 1, a + n + 1);
	int last = 1;
	for(int i = 1; i <= n; i ++) {
		last = insert(last, s[i] - 'a');
		times[last] = 1;
		val[last] = a[i];
	}

	for(int i = 2; i <= cp; i ++)
		G[fa[i]].push_back(i);
	dfs(1);

	len[0] = -1;
	for(int i = 1; i <= cp; i ++) {
		ll c = 1ll * times[i] * (times[i] - 1) >> 1;
		sum[len[i]] += c;
		if(times[i] > 1) modify(1, 0, n, len[fa[i]] + 1, len[i], val[i].get());
		if(i > 1) sum[len[fa[i]]] -= c;
	}

	for(int i = n; i; i --)
		sum[i - 1] += sum[i];

	for(int i = 0; i < n; i ++)
		printf("%lld %lld\n", sum[i], sum[i] ? query(1, 0, n, i) : 0);
}
