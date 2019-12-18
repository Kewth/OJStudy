#if 0
2019.12.17

只放两种值，一种是 k ，一种是 b (k > 0, b < 0) ，要求最大化所有值的和。
考虑在每个满足 x % w = y % h = 0 的 (x, y) 上放 b ，
这样每个 wxh 的子矩阵都会包含恰好一个 b ，且 b 的数量最少，
要每个每个 wxh 的子矩阵和小于 0 ，就是满足 (wh - 1)k + b < 0 ，
为了让 b 尽可能大，令 b = (1 - wh)k - 1 。
那么接下来再最大化 k ，因为要满足 b >= -1e9 ，也就是满足 (1 - wh)k >= 1 - 1e9 ，
令 k = (1e9 - 1) / (1 - wh) 即可，这样如果最大化的和仍小于 0 ，说明不合法。
需要特判的是 wh = 1 的情况。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 505;
int a[maxn][maxn];

int main() {
	int H = read, W = read, h = read, w = read;
	if(w * h == 1) return puts("No"), 0;
	int k = (1000000000 - 1) / (w * h - 1);

	ll sum = 0;
	for(int i = 1; i <= H; i ++)
		for(int j = 1; j <= W; j ++) {
			if(i % h == 0 and j % w == 0)
				a[i][j] = k - w * h * k - 1;
			else
				a[i][j] = k;
			sum += a[i][j];
		}

	if(sum > 0) {
		puts("Yes");
		for(int i = 1; i <= H; i ++) {
			for(int j = 1; j <= W; j ++)
				printf("%d ", a[i][j]);
			puts("");
		}
	} else
		puts("No");
}
