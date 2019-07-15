#if 0
2019.07.14

如果 n = 1 ，答案当然不存在。
如果 n > 1 且 n 为奇数，考虑以 1 为中心连接其他点，
对于 x 和 x + 1 （x 为偶数）有 x ^ (x + 1) = 1 ，
那么这样连接： (x) - (x + 1) - (1) - (x) - (x + 1) 即可满足 x 和 x + 1 的条件。
以这种方式将所有 x 连接在 1 上即可。
如果 n 是偶数，先用上述方法构造 n - 1 的情况，
然后只剩 n ，令 n = a ^ b ^ 1 ，那么一个 n 连接靠近 1 的 a 另一个连接靠近 1 的 b 即可，
如果不存在这样的 a, b ，那么就是无解的。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

int main() {
	int n = input();
	if(n == 1) puts("No");
	else if(n & 1) {
		puts("Yes");
		for(int i = 2; i + 1 <= n; i += 2) {
			printf("%d %d\n", i, i + 1);
			printf("%d %d\n", i + 1, 1);
			printf("%d %d\n", 1, i + n);
			printf("%d %d\n", i + n, i + n + 1);
		}
		printf("%d %d\n", n + 1, 2);
	} else {
		bool ok = false;
		for(int i = 2; i < n and not ok; i ++)
			if((i ^ n ^ 1) < n) {
				puts("Yes");
				if(i & 1)
					printf("%d %d\n", n, i);
				else
					printf("%d %d\n", n, i + n);
				if((i ^ n ^ 1) & 1)
					printf("%d %d\n", n + n, i ^ n ^ 1);
				else
					printf("%d %d\n", n + n, (i ^ n ^ 1) + n);
				ok = true;
			}
		if(ok) {
			for(int i = 2; i + 1 <= n; i += 2) {
				printf("%d %d\n", i, i + 1);
				printf("%d %d\n", i + 1, 1);
				printf("%d %d\n", 1, i + n);
				printf("%d %d\n", i + n, i + n + 1);
			}
			printf("%d %d\n", n + 1, 2);
		} else
			puts("No");
	}
}
