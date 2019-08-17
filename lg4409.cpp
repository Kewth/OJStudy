#if 0
2019.07.24

一开始以为是贪心，后来发现是假的。
应该二分答案，check 从 2 到 n 求出每个点最小最大分别可以选多少与 1 相同的。
最后若 min[n] = 0 则答案可行。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() {
	int c = getchar(), x = 0;
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

const int maxn = 20005;
int a[maxn];
int min[maxn], max[maxn];

bool check(int x, int n) {
	// debug(" check %d\n", x);
	for(int i = 2; i <= n; i ++) {
		min[i] = std::max(0, a[1] + a[i] + a[i - 1] - max[i - 1] - x);
		max[i] = std::min(a[i], a[1] - min[i - 1]);
		if(min[i] > max[i]) return false;
		// debug("%d-%d\n", min[i], max[i]);
	}
	return not min[n];
}

int main() {
	int n = input();
	int l = 1, r = 200000;
	for(int i = 1; i <= n; i ++) {
		a[i] = input();
		// 这不仅是剪枝，必须要这样才能保证 check 正确性
		l = std::max(l, a[i] + a[i - 1]);
	}
	min[1] = max[1] = a[1];
	while(l < r) {
		int mid = (l + r) >> 1;
		if(check(mid, n))
			r = mid;
		else
			l = mid + 1;
	}
	printf("%d\n", l);
}
