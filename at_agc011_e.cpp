#if 0
2019.08.13

称形如 111...111 的数为 MAGIC ，特别的， 0 也是 MAGIC 。
上升数一定可以表示成恰好 9 个 MAGIC 的和。
那么 N 表示成 K 个上升数的和就等价于 9K 个 MAGIC 的和。
即 N = sum(9K) { (10^x - 1) / 9 } 。
化简得 9N + 9K = sum(9K) { 10^x } 。
那么从小到大枚举 K ，每次 K 的增加会使左边加 9 。
考虑右边的数的数位和，假设没有进位显然是 9K ，算上进位，右边的取值是形如 9K - 9X 的数。
那么找到第一个 K 满足左边的数位和不大于 9K 即可。
#endif
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

const int maxn = 1000005;
char s[maxn];
int a[maxn];

int main() {
	scanf("%s", s);
	int n = strlen(s), k = 0, sum = 0;
	for(int i = 0; i < n; i ++) {
		a[i] = (s[n - i - 1] - '0') * 9;
		sum += a[i];
	}
	for(int i = 0; i < n or a[i]; i ++) {
		sum -= a[i] / 10 * 9;
		a[i + 1] += a[i] / 10;
		a[i] %= 10;
		// debug("%d", a[i]);
	}
	// debug(" -> %d\n", sum);
	while(sum > 9 * k) {
		a[0] += 9;
		sum += 9;
		for(int i = 0; a[i] > 9; i ++) {
			sum -= 9;
			a[i + 1] ++;
			a[i] -= 10;
		}
		k ++;
	}
	printf("%d\n", k);
}
