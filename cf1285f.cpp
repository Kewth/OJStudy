/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.08

 * Solution:
 * 添加限制，维护有效值，莫比乌斯函数

    不妨把所有数的因数都加入序列，然后求序列内互质的数的乘积的最大值。从大到小加数，
加入 x 的时候，如果当前最大的与 x 互质的数是 y ，那么可以发现对任意 x < k < y ，k 在
之后都一定无法使得答案变大（因为与之相乘的数一定比 x 小），那么可以用栈维护当前加入
的数，然后如果当前栈顶栈顶删掉后仍然有与 x 互质的数，就可以一直弹栈，弹完后就能得到
对应的 y 。

    那么就需要维护当前的栈，支持查询有多少数与 x 互质，莫比乌斯反演一波显然就是
sum(mu[d] tot[d]) ，只需要维护 tot[d] ，即 d 的倍数的数量即可。

 * Digression:
  妙啊，用一个我完全想不到的角度处理问题。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005;
std::vector<int> factor[maxn];
bool has[maxn];
int stack[maxn], sp;
int tot[maxn];
int mu[maxn], minp[maxn];

int query (int x) {
	int res = 0;
	for (int d : factor[x])
		/* debug("  %d: %d %d\n", d, mu[d], tot[d]), */
		res += mu[d] * tot[d];
	/* debug("  query %d -> %d\n", x, res); */
	return res;
}

void insert (int x) {
	for (int d : factor[x])
		++ tot[d];
	/* debug("insert %d\n", x); */
}

void erase (int x) {
	for (int d : factor[x])
		-- tot[d];
	/* debug("erase %d\n", x); */
}

int gcd (int a, int b) {
	if (!b) return a;
	return gcd(b, a % b);
}

int main () {
	int n = 0;
	for (int i = read; i; i --) {
		int x = read;
		has[x] = 1;
		n = std::max(n, x);
	}

	mu[1] = 1;
	minp[1] = 1;
	for (int i = 1; i <= n; i ++) {
		if (!minp[i]) minp[i] = i;
		if (minp[i] != minp[i / minp[i]])
			mu[i] = - mu[i / minp[i]];
		for (int j = i; j <= n; j += i) {
			factor[j].push_back(i);
			has[i] |= has[j];
			if (!minp[j] and i > 1)
				minp[j] = i;
		}
	}

	ll ans = n;
	for (int x = n; x; x --)
		if (has[x]) {
			while (sp and query(x) - (gcd(x, stack[sp]) == 1) > 0)
				erase(stack[sp --]);
			if (sp)
				ans = std::max(ans, 1ll * x * stack[sp] / gcd(x, stack[sp]));
			insert(stack[++ sp] = x);
		}

	printf("%lld\n", ans);
}
