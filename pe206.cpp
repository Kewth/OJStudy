/*
 * Author: Kewth

 * Date:
  2020.10.29

 * Solution:
 * 折半搜索

  到枚举平方数左边若干个数位，设右边一半未确定的数全部填 0 的结果为 A ，全部填 9 的
结果为 B 。那么只需要枚举 sqrt(A) 到 sqrt(B) 之间的数，然后计算平方并检查即可。

  而只要左边确定的数位长度超过了一半，sqrt(A) 到 sqrt(B) 之间的数就至多只有一个了。

 * Digression:

  又被 PE+ 的 "easy problem" 给教育了，这题卡了我一年，最终在 PE 上打了爆搜看了讨论
才搞明白这个牛逼折半。

  Eigenray 真是救星啊！

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

int a[100];
__int128 po[100];

__int128 sqrt (__int128 x) {
	__int128 s = __int128(sqrtl(ld(x)));
	while ((s + 1) * (s + 1) <= x)
		++ s;
	while (s * s > x)
		-- s;
	return s;
}

void force (int i, int N, int shit, __int128 A) {
	if (i == -1) {
		__int128 s = sqrt(A);
		if (s * s == A)
			printf("%lld\n", ll(s)), exit(0);
		return;
	}
	if (!shit) {
		__int128 s = sqrt(A - 1) + 1, B = A, C;
		for (int k = i; k >= 0; k -= 2)
			B += 9 * po[k];
		/* if ((s + 1) * (s + 1) <= B) */
		/* 	debug("test\n"); */
		while ((C = s * s) <= B) {
			for (int k = 0; k <= i; k ++, C /= 10)
				if (!(k & 1) and a[k] != C % 10)
					goto fail;
			printf("%lld\n", ll(s)), exit(0);
fail:;
		 ++ s;
		}
		return;
	}
	for (int x = 0; x < 10; x ++)
		a[i] = x, force(i - 2, N, shit - 1, A + x * po[i]);
}

int main () {
#ifdef PE
	int n = 10, tmp = 0;
	for (int i = n * 2 - 2; i >= 0; i -= 2) a[i] = (++ tmp) % 10;
#else
	int n = read;
	for (int i = n * 2 - 2; i >= 0; i -= 2) a[i] = read;
#endif
	int N = n * 2 - 2;
	po[0] = 1;
	for (int i = 1; i <= N; i ++) po[i] = po[i - 1] * 10;
	__int128 A = 0;
	for (int i = N; i >= 0; i -= 2)
		A += a[i] * po[i];
	force(N - 1, N, 7, A);
}
