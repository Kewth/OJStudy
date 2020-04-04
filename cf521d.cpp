#if 0
2020.01.31

对于一个点，三种操作一定是先赋值再加值再乘值使得最后结果最大。

对于赋值操作，一个点最多进行一次，
那么一个点的赋值操作只保留最大的一个后可以直接转换一个加法操作。

对于加法操作，一个点选择的操作一定是最大的若干个，
不妨要求选择加法操作必须从大到小执行，
这样就可以确定一个点加法操作的相对顺序，
从而一个加法操作执行前对应的权值是确定的，可以直接转换为乘法操作。

对于乘法操作，直接从大到小选择执行即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 100005;
struct modify {
	int o, t, id;
	ll x, y;
};

bool cmp(modify a, modify b) {
	if(a.o == b.o)
		// return a.x * b.y > b.x * a.y;
		return ld(1) * a.x / a.y > ld(1) * b.x / b.y;
	return a.o < b.o;
}

ll a[maxn];
modify mo[maxn];
bool vis[maxn];
int type[maxn];

int main() {
	int n = read, m = read, lim = read;
	for(int i = 1; i <= n; i ++)
		a[i] = read;

	for(int i = 1; i <= m; i ++) {
		type[i] = mo[i].o = read;
		mo[i].t = read;
		mo[i].x = read;
		mo[i].y = 1;
		mo[i].id = i;
	}

	std::sort(mo + 1, mo + m + 1, cmp);

	for(int i = 1; mo[i].o == 1; i ++)
		if(!vis[mo[i].t]) {
			vis[mo[i].t] = 1;
			mo[i].o = 2;
			mo[i].x -= a[mo[i].t];
		} else {
			mo[i].o = 3;
			mo[i].x = 0;
		}

	std::sort(mo + 1, mo + m + 1, cmp);

	for(int i = 1; mo[i].o == 2; i ++) {
		mo[i].o = 3;
		mo[i].x += a[mo[i].t];
		mo[i].y = a[mo[i].t];
		a[mo[i].t] = mo[i].x;
	}

	std::sort(mo + 1, mo + m + 1, cmp);

	while(mo[lim].x < mo[lim].y)
		-- lim;

	for(int i = 1; i <= lim; i ++)
		mo[i].o = type[mo[i].id];
	std::sort(mo + 1, mo + m + 1, cmp);

	printf("%d\n", lim);
	for(int i = 1; i <= lim; i ++)
		printf("%d ", mo[i].id);
	puts("");
}
