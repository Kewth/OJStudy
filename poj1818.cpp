#if 0
2019.07.24

假设已知最后的 winner 是 x ，考虑如何根据 x 倒推出每场比赛的双方。
x 能赢的值在 [x - k, INF) 范围内，贪心的选取区间内最小的值（使得之后的值更好安排），
如果碰到点的范围内的值都被选了，那说明这个 winner 是错误的。
winner 明显存在单调性，可以二分，用 set 维护当前的可选值，可以 lower_bound 出区间内最小值。
#endif
#include <cstdio>
#include <set>
#include <cassert>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() {
	int c = getchar(), x = 0;
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

const int maxn = 4100;
int a[maxn], b[maxn];
std::set<int> s;

bool check(int x, int n, int k) {
	/* for(int i = 1; i <= x; i ++) */
	/* 	debug(" %d", a[i]); */
	/* debug("\n"); */
	if(x == n)
		return true;
	for(int i = 1; i <= x; i ++) {
		// FIXME: poj 玄学 TLE
		b[i] = *s.lower_bound(a[i] - k);
		if(b[i] == n + 1)
			return false;
		s.erase(b[i]);
	}
	for(int i = x; i; i --) {
		a[i * 2] = b[i];
		a[i * 2 - 1] = a[i];
	}
	return check(x << 1, n, k);
}

int main() {
	int n = input(), k = input();
	int l = 1, r = n;
	while(l < r) {
		int mid = (l + r + 1) >> 1;
		a[1] = mid;
		s.clear();
		for(int i = 1; i <= n + 1; i ++)
			if(i != mid)
				s.insert(i);
		if(check(1, n, k))
			l = mid;
		else
			r = mid - 1;
	}
	printf("%d\n", l);
}

