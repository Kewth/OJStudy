#if 0
2020.05.12

  分治，统计端点在两边的区间数，一个区间合法当且仅当 max - min = r - l 。
  分类讨论，如果最大值和最小值在同一边，枚举那一边的端点简单判断即可。如果最大值在
左边而最小值在右边，枚举左端点，同时用双指针维护右端点的可行区间，然后根据 max[i] -
min[j] = j - i ，维护一个桶即可统计 max[i] + i = min[j] + j 的合法区间数。最大值在
右边而最小值在左边同理，就是统计 max[i] - i = min[j] - j 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 1000005;
int a[maxn], ans;
int min[maxn], max[maxn];
int t[maxn << 1];

void solve (int l, int r) {
	if (l == r) return ++ ans, void();
	int mid = (l + r) >> 1;
	solve(l, mid);
	solve(mid + 1, r);

	/* int bak = ans; */

	max[mid] = min[mid] = a[mid];
	max[mid + 1] = min[mid + 1] = a[mid + 1];
	for (int i = mid - 1; i >= l; i --) {
		min[i] = std::min(a[i], min[i + 1]);
		max[i] = std::max(a[i], max[i + 1]);
	}
	for (int i = mid + 2; i <= r; i ++) {
		min[i] = std::min(a[i], min[i - 1]);
		max[i] = std::max(a[i], max[i - 1]);
	}

	for (int i = mid; i >= l; i --) {
		int j = i + max[i] - min[i];
		if (mid < j and j <= r and max[j] < max[i] and min[j] > min[i])
			++ ans;
	}

	for (int i = mid + 1; i <= r; i ++) {
		int j = i - max[i] + min[i];
		if (l <= j and j <= mid and max[j] < max[i] and min[j] > min[i])
			++ ans;
	}

	int L = mid + 1, R = mid;
	for (int i = mid; i >= l; i --) {
		while (R + 1 <= r and max[R + 1] < max[i]) ++ R, ++ t[R + min[R]];
		while (L <= r + 1 and min[L] > min[i]) -- t[L + min[L]], ++ L;
		ans += std::max(0, t[i + max[i]]);
	}

	while (L > mid + 1) -- L, ++ t[L + min[L]];
	while (R > mid) -- t[R + min[R]], -- R;

	for (int i = mid; i >= l; i --) {
		while (R + 1 <= r and min[R + 1] > min[i]) ++ R, ++ t[maxn + max[R] - R];
		while (L <= r + 1 and max[L] < max[i]) -- t[maxn + max[L] - L], ++ L;
		ans += std::max(0, t[maxn + min[i] - i]);
	}

	while (L > mid + 1) -- L, ++ t[maxn + max[L] - L];
	while (R > mid) -- t[maxn + max[R] - R], -- R;

/* 	debug("solve %d %d | %d %d -> %d\n", l, mid, mid + 1, r, ans - bak); */
}

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) read(a[i]);
	solve(1, n);
	printf("%d\n", ans);
}
