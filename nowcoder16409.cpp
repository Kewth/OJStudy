#if 0
2020.02.23
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 1010;
int a[maxn], b[maxn];
bool open[maxn];

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++) {
		a[i] = read;
		b[i] = read;
	}

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			if(i != j and b[i] == a[j])
				open[j] = 1;

	int ans = 0;
	for(int i = 1; i <= n; i ++)
		if(!open[i])
			++ ans;

	printf("%d\n", ans);
}
