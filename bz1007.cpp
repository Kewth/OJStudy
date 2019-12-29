#if 0
2019.12.28

可见的直线构成了下凸包，求出下凸包即可。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 50005;
struct line {
	int A, B, id;
};
line seg[maxn];
int ans[maxn], ap;
line stack[maxn];
double begin[maxn];
int sp;

double cross(line x, line y) {
	return double(y.B - x.B) / (x.A - y.A);
}

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++) {
		read(seg[i].A, seg[i].B);
		seg[i].id = i;
	}

	std::sort(seg + 1, seg + n + 1, [](line x, line y) {
				if(x.A == y.A) return x.B > y.B;
				return x.A < y.A;
			});

	for(int i = 1; i <= n; i ++)
		if(seg[i].A != seg[i - 1].A) {
			while(sp and cross(seg[i], stack[sp]) <= begin[sp] + 1e-9)
				-- sp;
			if(!sp) begin[sp + 1] = - INFINITY;
			else begin[sp + 1] = cross(seg[i], stack[sp]);
			stack[++ sp] = seg[i];
		}

	while(sp)
		ans[++ ap] = stack[sp --].id;

	std::sort(ans + 1, ans + ap + 1);
	for(int i = 1; i <= ap; i ++)
		printf("%d ", ans[i]);
}
