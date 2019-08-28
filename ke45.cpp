#if 0
2019.08.28

最后的胜负关系只与最后相遇的点有关。
那么每个点有三种状态 -1/0/1 分别表示在这个点上相遇会导致 lose/tie/win 。

假设 n 是奇数，那么后手总有办法让最后在中点相遇，方法是对称操作。
那么 n 是偶数的时候，先手选了一个后变为奇数后手，
那么相当于先手可以选择在两个中点相遇。
而如果先手不希望在中点相遇，后手也同样可以用对称操作使先手在中点相遇。
那么 n 是偶数的情况就能很好算出答案了。

n 是奇数的话，得考虑三个中点，先手可以转移到两个偶数后手的情况。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 10005;
lolong s[maxn];

int main() {
	int T = input();

	while(T --) {
		int n = input();
		for(int i = 1; i <= n; i ++)
			s[i] = s[i - 1] + input();

		if(n & 1) {
			lolong a = s[n / 2] - (s[n] - s[n / 2 - 1]);
			lolong b = s[n / 2 + 1] - (s[n] - s[n / 2]);
			lolong c = s[n / 2 + 2] - (s[n] - s[n / 2 + 1]);

			debug("%lld %lld %lld\n", a, b, c);

			if((a > 0 and b > 0) or (b > 0 and c > 0))
				puts("win");
			else if(a == 0 or b == 0 or c == 0)
				puts("tie");
			else
				puts("lose");
		}

		else {
			lolong a = s[n / 2] - (s[n] - s[n / 2 - 1]);
			lolong b = s[n / 2 + 1] - (s[n] - s[n / 2]);
			if(a > 0 or b > 0)
				puts("win");
			else if(a == 0 or b == 0)
				puts("tie");
			else
				puts("lose");
		}
	}
}
