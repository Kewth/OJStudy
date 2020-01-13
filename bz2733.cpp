#if 0
2020.01.13

求第 k 大值域线段树，合并操作就是线段树合并，顺便用并查集维护一下联通块即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator char () { char x[3]; return scanf("%s", x), x[0]; }
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005;
struct Tree {
	int lti, rti;
	int tot;
};
Tree pool[maxn * 20];
int pp;
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]

int kth(int now, int L, int R, int k) {
	if(L == R) return L;
	int M = (L + R) >> 1;
	if(k <= lt.tot) return kth(self.lti, L, M, k);
	return kth(self.rti, M + 1, R, k - lt.tot);
}

void lain(int &now, int L, int R, int p) {
	if(!now) now = ++ pp;
	++ self.tot;
	if(L == R) return;
	int M = (L + R) >> 1;
	if(p <= M) lain(self.lti, L, M, p);
	else lain(self.rti, M + 1, R, p);
}

void merge(int &now, int &an, int L, int R) {
	if(self.tot < pool[an].tot) std::swap(now, an);
	self.tot += pool[an].tot;
	if(L == R or !an) return;
	int M = (L + R) >> 1;
	merge(self.lti, pool[an].lti, L, M);
	merge(self.rti, pool[an].rti, M + 1, R);
}

int fa[maxn];
int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

int a[maxn], p[maxn];
int T[maxn];
int main() {
	int n = read, m = read;
	for(int i = 1; i <= n; i ++) {
		read(a[i]);
		p[a[i]] = i;
	}

	for(int i = 1; i <= n; i ++)
		fa[i] = i;
	for(int i = 1; i <= n; i ++)
		lain(T[i], 1, n, a[i]);

	for(int i = 1; i <= m; i ++) {
		int x = find(read), y = find(read);
		if(x != y) {
			merge(T[x], T[y], 1, n);
			fa[y] = x;
		}
	}

	int q = read;
	while(q --) {
		char op = read;
		if(op == 'Q') {
			int x = find(read), k = read;
			if(k <= pool[T[x]].tot)
				printf("%d\n", p[kth(T[x], 1, n, k)]);
			else
				puts("-1");
		} else if(op == 'B') {
			int x = find(read), y = find(read);
			if(x != y) {
				merge(T[x], T[y], 1, n);
				fa[y] = x;
			}
		}
	}
}
