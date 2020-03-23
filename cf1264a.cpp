#if 0
2020.03.22

首先有牌的人是段前缀，所有权值相同的人拿到的牌相同。
贪心，金牌尽量少，然后银牌在超过金牌的前提下也要尽量少，然后铜牌尽量多。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 400005;
int a[maxn];

int main () {
	int T = read;
	while (T --) {
		int n = read;
		for (int i = 1; i <= n; i ++)
			read(a[i]);
		a[n + 1] = -1;
		int m = 1;
		while (a[m + 1] == a[1])
			++ m;
		int k = m + m + 1;
		if (k > n) {
			puts("0 0 0");
			continue;
		}
		while (a[k + 1] == a[m + m + 1])
			++ k;
		int q = k + m + 1;
		if (q > n) {
			puts("0 0 0");
			continue;
		}
		while (a[q + 1] == a[k + m + 1])
			++ q;
		if (q > n / 2) {
			puts("0 0 0");
			continue;
		}
		while (1) {
			int p = q + 1;
			while (a[p + 1] == a[q + 1])
				++ p;
			if (p <= n / 2)
				q = p;
			else
				break;
		}
		printf("%d %d %d\n", m, k - m, q - k);
	}
}
