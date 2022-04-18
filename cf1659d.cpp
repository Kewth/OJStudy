/*
 * Author: Kewth

 * Date:
  2022.04.17

 * Solution:
  将序列一行行写下来，对于第 i 列：前 i - 1 行都是 a[i] ，第 i 行
到第 n 行前面一段是 1 后面一段是 0 。
  记 L[i] 表示第 i 列 i 到 n 行的 1 的个数，则

  1. C[i] == a[i] * (i - 1) + L[i]
  2. L[i] >= L[i - 1] - 1

  然后横向来看也有一定性质，总之性质很多，随便找几条即可。

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 200005;
int a[maxn], c[maxn], L[maxn];

int main () {
	int T = read;
	while (T --) {
		int n = read, j = 0;
		for (int i = 1; i <= n; i ++) {
			read(c[i]);
			if (L[j] + j - 1 < i) {
				++ j;
				if (j == i and L[i - 1] == 0 and c[i] > 0)
					a[i] = 1;
				else
					a[i] = 0;
			}
			else
				a[i] = 1;
			L[i] = c[i] - a[i] * (i - 1);
			printf("%d ", a[i]);
		}
		puts("");
	}
}
