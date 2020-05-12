#if 0
2020.05.12

  把多边形拆开，拆成角和边交替的环，那么一个位置能引出一条对称轴，当且仅当从这个位置把
环断开后序列是回文。那么把环倍长，用 manacher 找有多少长度满足条件的回文串即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 100005;
int px[maxn], py[maxn];
ll s[maxn << 3];
int r[maxn << 3];

void manacher (int n) {
	int M = 0, R = 0;
	ll MAGIC1 = 89237545602, MAGIC2 = 12894769827;
	s[0] = MAGIC1;
	s[n + 1] = MAGIC2;
	for (int i = 1; i <= n; i ++) {
		r[i] = i <= R ? std::min(r[M - (i - M)], R - i) : 0;
		while (s[i - r[i] - 1] == s[i + r[i] + 1]) ++ r[i];
		if (i + r[i] > R)
			M = i, R = i + r[i];
	}
}

int main () {
	int T = read;
	while (T --) {
		int n = read;
		for (int i = 1; i <= n; i ++)
			read(px[i], py[i]);
		px[n + 1] = px[1];
		px[0] = px[n];
		py[n + 1] = py[1];
		py[0] = py[n];

		int m = 0;
		for (int i = 1; i <= n; i ++) {
			int x1 = px[i] - px[i - 1], y1 = py[i] - py[i - 1];
			int x2 = px[i + 1] - px[i], y2 = py[i + 1] - py[i];
			s[++ m] = 1ll * x1 * y2 - 1ll * x2 * y1;
			s[++ m] = 1ll * x2 * x2 + 1ll * y2 * y2;
		}

		for (int i = 1; i <= m; i ++)
			s[i + m] = s[i];
		m <<= 1;

		manacher(m);

		int ans = 0;
		for (int i = 1; i <= m; i ++) {
			int len = 1 + r[i] * 2;
			if (len >= m / 2 - 1)
				++ ans;
		}
		ans >>= 1;
		printf("%d\n", ans);
	}
}
