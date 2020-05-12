#if 0
2020.05.12

  限制就是要对于任意两个模 n 意义下不同的数，变换后在模 n 意义下仍然不同。
  把 0 到 n - 1 拿出来变换看是不是模 n 两两不同即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005;
int b[maxn];

int main () {
	int T = read;
	while (T --) {
		int n = read;
		std::fill(b, b + n, 0);
		for (int i = 0; i < n; i ++) {
			int x = read, y = (i + x) % n;
			if (y < 0) y += n;
			b[y] = 1;
		}
		for (int i = 0; i < n; i ++)
			if (!b[i]) {
				puts("NO");
				goto done;
			}
		puts("YES");
done:;
	}
}
