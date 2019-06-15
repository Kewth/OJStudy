#if 0
2019.06.15

贪心。
若有正有负，先拿负数减正数，减到只剩一个正数后拿它减去所有负数。
这样答案是 sum(abs(a[i])), 一定是最优的。
如果全是正，拿最小值减去最大值，同上。
如果全是负，那最大值减去最小值，同上。
但尼玛有 0 就贼难判，靠，差评，这玩意卡我 11 次罚时。
#endif
#include <cstdio>
#include <algorithm>
#include <cassert>

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100050;
int a[maxn];
int ansx[maxn], ansy[maxn], ap;
int fg = 0;
inline int flag(int x) {
	if(x > 0) return 1;
	if(x < 0) return -1;
	return fg;
}

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++)
		a[i] = input();
	std::sort(a + 1, a + n + 1);
	if(n == 1) {
		printf("%d\n", a[1]);
		return 0;
	} else if(a[1] == 0 and a[n] == 0) {
		puts("0");
		for(int i = 1; i < n; i ++)
			puts("0 0");
		return 0;
	}
	if(a[1] == 0)
		fg = -1;
	else if(a[n] == 0)
		fg = 1;
	if(flag(a[1]) == 1) {
		ansx[++ ap] = a[1];
		ansy[ap] = a[n];
		a[1] = a[1] - a[n];
		n --;
		std::sort(a + 1, a + n + 1);
		if(a[1] == 0)
			fg = -1;
		else if(a[n] == 0)
			fg = 1;
	} else if(flag(a[n]) == -1) {
		ansx[++ ap] = a[n];
		ansy[ap] = a[1];
		a[1] = a[n] - a[1];
		n --;
		std::sort(a + 1, a + n + 1);
		if(a[1] == 0)
			fg = -1;
		else if(a[n] == 0)
			fg = 1;
	}
	int first = 0;
	for(int i = 1; i <= n; i ++)
		if(flag(a[i]) == 1) {
			first =	i;
			break;
		}
	assert(first);
	for(int i = first + 1; i <= n; i ++) {
		ansx[++ ap] = a[1];
		ansy[ap] = a[i];
		a[1] = a[1] - a[i];
	}
	for(int i = 1; i < first; i ++) {
		ansx[++ ap] = a[first];
		ansy[ap] = a[i];
		a[first] = a[first] - a[i];
	}
	printf("%d\n", a[first]);
	for(int i = 1; i <= ap; i ++)
		printf("%d %d\n", ansx[i], ansy[i]);
}
