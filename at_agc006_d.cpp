#if 0
2019.07.24

假设最终答案为 x ，那么其他的数其实可以分为三种：x ，小于 x 和大于 x 。
只需要关注与 x 的大小，把小于 x 的全设为 -INF ，大于 x 的全设为 INF ，得出的结果一定仍是 x 。

但这仍然难以处理，考虑枚举一个值 x ，把所有数分为两种：小于等于 x (0) 和大于 x (1) 。
如此将原数列转换为 01 串，若最后剩下的是 0 ，那么答案一定小于 x ，否则答案一定大于 x 。
那么 x 的值可以二分，接下来问题转换为 01 串上求最后剩下的数。

首先，如果两个相等的值相邻，那么在之后的操作中这两个位置的值始终不变。
那么如果中间的值 a[mid] 与 a[mid - 1] 或 a[mid + 1] 相等，即中间的值是 xx?  或 ?xx 形式，最后的结果一定是 a[mid] ，即 x。
否则 a[mid - 1] 到 a[mid + 1] 一定是 xyx 形式。
那么考虑 a[mid - 2] 到 a[mid + 2] ，若为 xxyx? 形式，一次操作后转换为 xx? 形式，最后结果一定是 x 。
?xyxx 形式同理，否则一定是 xyxyx 形式。

以此类推，从中间向两边找到第一个相邻且相等的 a[i] = a[i + 1] ，那么 a[i] 即最后的结果。
如果不存在此 a[i] ，那么就是 0101...01010 的形式，最终结果是 a[n] 。
#endif
#include <cstdio>
#include <algorithm>
#include <climits>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() {
	int c = getchar(), x = 0;
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

const int maxn = 200005;
int a[maxn];
bool b[maxn];

bool check(int x, int n) {
	// debug("check %d\n", x);
	for(int i = 1; i <= n; i++)
		b[i] = a[i] > x;
	int mid = (1 + n) >> 1;
	for(int i = 0; i < mid; i ++) {
		if(b[mid + i] == b[mid + i + 1])
			return b[mid + i];
		if(b[mid - i] == b[mid - i - 1])
			return b[mid - i];
	}
	return b[n];
}

int main() {
	int n = input() * 2 - 1, min = INT_MAX, max = 0;
	for(int i = 1;  i <= n; i ++) {
		a[i] = input();
		min = std::min(a[i], min);
		max = std::max(a[i], max);
	}
	int l = min, r = max;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(check(mid, n))
			l = mid + 1;
		else
			r = mid;
	}
	printf("%d\n", l);
}

