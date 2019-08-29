#if 0
2019.08.29

出现偶数次的数有个特点：异或和为 0 。
那么 k = 1 的时候答案就是异或和。
k = 2 的时候记 a[i] 表示二进制 i 位为 1 的所有数的异或和，偶数次的还是没影响。
记答案为 x, y 那么 a[i] 的值只有三种可能： x, y, x xor y 。
如果 a[i] 的第 i 位为 0 ，那么一定是 x xor y 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

int main() {
	int n = input(), k = input();

	if(k == 1) {
		int ans = 0;
		while(n --)
			ans ^= input();
		printf("%d\n", ans);
	}

	else {
		int a[31];
		for(int i = 0; i < 31; i ++)
			a[i] = 0;
		while(n --) {
			int x = input();
			for(int i = 0; i < 31; i ++)
				if(x >> i & 1)
					a[i] ^= x;
		}

		int x = -1, y = -1;
		for(int i = 0; i < 31; i ++)
			if(a[i] >> i & 1) {
				if(x == -1)
					x = a[i];
				else if(y == -1 and x != a[i])
					y = a[i];
			}

		if(x < y)
			printf("%d %d\n", x, y);
		else
			printf("%d %d\n", y, x);
	}
}
