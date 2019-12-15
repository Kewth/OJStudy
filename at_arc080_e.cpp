#if 0
2019.12.14

贪心地逐个确定 q 的每个值。
q[1] 一定是 p 中奇数位的值，找到其中最小的一个，设为 p[i] ，
那么 q[1] = p[i] ，同理找到 i 之后的 j 使得 q[2] = p[j] 最小。
这样就确定了最后添加的一对 p 。
剩下的 p 被分为三段：[1, i), (i, j), (j, n] ，三段之间互不影响。
这三段都能用同样的方法找到一个新的 p[i] ，选其中最小的作为 q[3] 即可。

据此归纳出一般方法，用堆维护当前的每一段，每次取出 p[i] 最小的一段，并得出 j ，
然后该段被分为至多三个段，重新添加到堆中，直到所有段都处理完毕。
用线段树快速查找对应最小的 p[i] 即可。
#endif
#include <cstdio>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 200005;
int p[maxn], q[maxn];
int val[2][maxn << 2];

inline int min(int x, int y) { return p[x] < p[y] ? x : y; }

void build(int now, int L, int R) {
	if(L == R) return val[L & 1][now] = min(val[L & 1][now], L), void();
	int M = (L + R) >> 1;
	build(now << 1, L, M);
	build(now << 1 | 1, M + 1, R);
	for(int i = 0; i < 2; i ++)
		val[i][now] = min(val[i][now << 1], val[i][now << 1 | 1]);
}

int query(int now, int L, int R, int l, int r, int o) {
	if(l > r or l > R or r < L) return 0;
	if(l <= L and R <= r) return val[o][now];
	int M = (L + R) >> 1;
	return min(query(now << 1, L, M, l, r, o), query(now << 1 | 1, M + 1, R, l, r, o));
}

int n;
struct Range {
	int l, r, p;
	Range(int l, int r): l(l), r(r), p(query(1, 1, n, l, r, l & 1)) { }
};
bool operator < (Range x, Range y) { return p[x.p] > p[y.p]; }

int main() {
read(n);
	for(int i = 1; i <= n; i ++)
		read(p[i]);
	p[0] = 1000000000;

	build(1, 1, n);

	std::priority_queue<Range> qu;
	qu.push(Range(1, n));

	int qp = 0;
	while(!qu.empty()) {
		Range rg = qu.top();
		qu.pop();
		if(rg.l > rg.r) continue;

		int p1 = rg.p;
		int p2 = query(1, 1, n, p1, rg.r, !(p1 & 1));

		q[++ qp] = p[p1];
		q[++ qp] = p[p2];

		qu.push(Range(rg.l, p1 - 1));
		qu.push(Range(p1 + 1, p2 - 1));
		qu.push(Range(p2 + 1, rg.r));
	}

	for(int i = 1; i <= n; i ++)
		printf("%d ", q[i]);
	puts("");
}
