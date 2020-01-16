#if 0
2020.01.16

单纯形好难啊。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator double () { double x; return scanf("%lf", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 23, maxm = 23;
const double eps = 1e-9;
double a[maxm][maxn];
int id[maxn + maxm];

void pivot(int n, int m, int x, int y) {
	std::swap(id[x], id[n + y]);
	double tmp = - a[y][x];
	for(int i = 0; i <= n; i ++)
		a[y][i] /= tmp;
	a[y][x] = -1 / tmp;
	for(int i = 0; i <= m; i ++)
		if(i != y) {
			tmp = a[i][x];
			a[i][x] = 0;
			for(int j = 0; j <= n; j ++)
				a[i][j] += tmp * a[y][j];
		}
}

const double Infeasible = 2333.333, Unbounded = 6666.666;
double simplex(int n, int m) {
	while(1) {
		int y = 0;
		for(int i = 1; i <= m; i ++)
			if(a[i][0] < -eps)
				y = i;
		if(!y) break;
		int x = 0;
		for(int i = 1; i <= n; i ++)
			if(a[y][i] > eps)
				x = i;
		if(!x) return Infeasible;
		pivot(n, m, x, y);
	}
	while(1) {
		int x = 0;
		for(int i = 1; i <= n; i ++)
			if(a[0][i] > eps and (!x or a[0][i] > a[0][x]))
				x = i;
		if(!x) return a[0][0];
		int y = 0;
		for(int i = 1; i <= m; i ++)
			if(a[i][x] < -eps and (!y or a[i][0] / -a[i][x] < a[y][0] / -a[y][x]))
				y = i;
		if(!y) return Unbounded;
		pivot(n, m, x, y);
	}
}

double Ans[maxn];
int main() {
	int n = read, m = read, t = read;
	for(int i = 1; i <= n; i ++)
		read(a[0][i]);
	for(int i = 1; i <= m; i ++) {
		for(int j = 1; j <= n; j ++) {
			read(a[i][j]);
			a[i][j] *= -1;
		}
		read(a[i][0]);
	}
	for(int i = 1; i <= n + m; i ++)
		id[i] = i;

	double ans = simplex(n, m);
	if(ans == Infeasible) return puts("Infeasible"), 0;
	if(ans == Unbounded) return puts("Unbounded"), 0;
	printf("%lf\n", ans);

	if(t == 1) {
		for(int i = 1; i <= m; i ++)
			if(id[n + i] <= n)
				Ans[id[n + i]] = a[i][0];
		for(int i = 1; i <= n; i ++)
			printf("%.9lf ", Ans[i]);
	}
}
