#if 0
2019.07.27

将田忌的马降序，齐王的马升序。
田忌赢的肯定是齐王的一段后缀。
枚举这个后缀长，拿田忌最菜的马拖死这段后缀，然后剩下的升序一个一个打。
这个后缀长是可以二分的，但是最优解并不一定是输的局数最少，只能老老实实枚举。
#endif
#include <cstdio>
#include <algorithm>
#include <climits>

inline int input() {
	int x = 0, c = getchar();
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

const int maxn = 2010;
int a[maxn], b[maxn];

inline bool cmp(int x, int y) {
	return x > y;
}

int check(int x, int n) {
	int res = (x - n) * 200;
	for(int i = 1; i <= x; i ++)
		if(a[x - i + 1] > b[i])
			res += 200;
		else if(a[x - i + 1] < b[i]) {
			res = 233;
			break;
		}
	return res;
}

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++)
		a[i] = input();
	for(int i = 1; i <= n; i ++)
		b[i] = input();
	std::sort(a + 1, a + n + 1, cmp);
	std::sort(b + 1, b + n + 1);
	int ans = INT_MIN;
	for(int x = 0; x <= n; x ++) {
		int c = check(x, n);
		if(c != 233)
			ans = std::max(ans, c);
	}
	printf("%d\n", ans);
}

