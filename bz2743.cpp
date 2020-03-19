#if 0
2020.01.20

对于一段区间，令每个颜色第二个出现的点的贡献为 1 。
将询问按左端点排序，对于一个左端点，可以确定所有点的贡献，
那么该左端点的询问就是一个前缀和。
而左端点右移会有点的贡献改变，
记 nxt[i] 表示比 i 大的最小的与 i 同色的点，
利用 nxt 容易求得具体是什么点的贡献改变，
那么用树状数组维护每个点的贡献即可。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct Inputer {
	static char buffer[64 * 1024 * 1024], *p;
	inline operator int () { return int(strtol(p, &p, 10)); }
	inline operator ll () { return strtoll(p, &p, 10); }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
	Inputer() { fread(buffer, 1, sizeof buffer, stdin); }
} read;
char *Inputer::p = Inputer::buffer;
char Inputer::buffer[] = {};

const int maxn = 2000005;
int a[maxn];
int nxt[maxn];
int last[maxn];
int bit[maxn];
std::vector<par> qu[maxn];
int ans[maxn];

inline int query(int p) {
	int res = 0;
	for(int k = p; k; k -= k & -k)
		res += bit[k];
	return res;
}

inline void add(int p, int x, int n) {
	for(int k = p; k <= n; k += k & -k)
		bit[k] += x;
}

int main() {
	int n = read, c = read, q = read;
	for(int i = 1; i <= n; i ++)
		read(a[i]);

	for(int i = 1; i <= c; i ++)
		last[i] = n + 1;
	nxt[n + 1] = n + 1;
	for(int i = n; i; i --) {
		nxt[i] = last[a[i]];
		last[a[i]] = i;
	}

	for(int i = 1; i <= q; i ++) {
		int l = read, r = read;
		qu[l].push_back(par(r, i));
	}

	for(int i = 1; i <= c; i ++)
		add(nxt[last[i]], 1, n);

	for(int i = 1; i <= n; i ++) {
		for(par p : qu[i])
			ans[p.second] = query(p.first);
		add(nxt[i], -1, n);
		add(nxt[nxt[i]], 1, n);
	}

	for(int i = 1; i <= q; i ++)
		printf("%d\n", ans[i]);
}
