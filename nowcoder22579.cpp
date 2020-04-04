#if 0
2020.02.22

分治，每次划分成两半，左边的后缀和右边的前缀拼起来的结果。
假设左边选了 i 个，右边选了 j 个，这个贡献就是 lss[i] + rss[j] + i * rs[j] 。
其中 lss, rss 表示带权后缀和，前缀和，rs 表示右边的前缀和。
不难发现当 i 确定后右边的 j 的贡献是一次函数的形式。
那么把右边的每个 j 看作二维平面上的点 (- rs[j], rss[j]) ，求出凸包，
枚举左边的 i 的时候用一条斜率递增的直线去截这个凸包即可。
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

const int maxn = 200005;
int a[maxn];
struct Dot {
	ll x, y;
} d[maxn], s[maxn];
struct Vector {
	ll x, y;
};

Vector operator - (Dot A, Dot B) {
	return {A.x - B.x, A.y - B.y};
}

ll ans = - 1000000000000000000;
void solve(int l, int r) {
	if(l == r) return ans = std::max(ans, ll(a[l] = read)), void();

	int mid = (l + r) >> 1;
	solve(l, mid);
	solve(mid + 1, r);

	d[mid] = {0, 0};
	for(int i = mid + 1; i <= r; i ++) {
		d[i].x = d[i - 1].x - a[i];
		d[i].y = d[i - 1].y + a[i] * (i - mid);
	}

	std::sort(d + mid + 1, d + r + 1, [](Dot A, Dot B) {
				return A.x == B.x ? A.y < B.y : A.x < B.x;
			});

	int p = 0;
	Vector las = {0, 0};
	for(int i = mid + 1; i <= r; i ++) {
		Vector now = d[i] - s[p];
		while(p > 1 and now.y * las.x >= las.y * now.x) {
			-- p;
			now = d[i] - s[p];
			las = s[p] - s[p - 1];
		}
		s[++ p] = d[i];
		las = now;
	}

	ll sum = 0, ssum = 0;
	for(int i = mid; i >= l; i --) {
		sum += a[i];
		ssum += sum;
		int k = mid - i + 1;
		while(p > 1 and s[p].y - k * s[p].x <= s[p - 1].y - k * s[p - 1].x)
			-- p;
		ans = std::max(ans, ssum + s[p].y - k * s[p].x);
	}
}

int main() {
	int n = read;
	solve(1, n);
	printf("%lld\n", ans);
}
