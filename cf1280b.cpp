#if 0
2020.03.18

分类讨论题，首先可以发现只要存在 A 答案就不会超过 4 。
考虑什么时候答案为 0 ，显然是所有点都是 A 。
那么考虑什么时候通过恰好一次操作会使得答案为 0 ，显然是存在某一边全是 A 。
以此类推。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100;
char s[maxn][maxn];

bool check(int n, int m) {
	for(int i = 1; i <= n; i ++) {
		bool ok = 1;
		for(int j = 1; j <= m; j ++)
			ok &= s[i][j];
		if(ok) return 1;
	}
	for(int i = 1; i <= m; i ++) {
		bool ok = 1;
		for(int j = 1; j <= n; j ++)
			ok &= s[j][i];
		if(ok) return 1;
	}
	return 0;
}

int main() {
	int T = read;
	while(T --) {
		int n = read, m = read;
		for(int i = 1; i <= n; i ++)
			scanf("%s", s[i] + 1);

		int a = 0, b = 0, c = 0, d = 0, x = 0;
		for(int i = 1; i <= m; i ++)
			a += s[1][i] == 'A';
		for(int i = 1; i <= n; i ++)
			b += s[i][m] == 'A';
		for(int i = 1; i <= m; i ++)
			c += s[n][i] == 'A';
		for(int i = 1; i <= n; i ++)
			d += s[i][1] == 'A';
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				x += s[i][j] == 'A';

		if(x == n * m) {
			puts("0");
			continue;
		}

		if(a == m or b == n or c == m or d == n) {
			puts("1");
			continue;
		}

		if(s[1][1] == 'A' or s[1][m] == 'A' or s[n][1] == 'A' or s[n][m] == 'A' or
				check(n, m)) {
			puts("2");
			continue;
		}

		if(a or b or c or d) {
			puts("3");
			continue;
		}

		if(x) {
			puts("4");
			continue;
		}

		puts("MORTAL");
	}
}
