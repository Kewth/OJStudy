#if 0
2019.07.25

考虑枚举约数，发现可以整除分块，
然后问题转换为求一段自然数的异或和，
利用前缀和转换为求 1 ~ n 的异或和，
将 2xor3, 4xor5, 6xor7... 分成一组，归纳一下就可以 O(1) 算出 1 ~ n 的异或和。
#endif
#include <cstdio>

typedef long long lolong;
inline lolong input() {
	lolong x = 0;
	int c = getchar();
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

lolong f(lolong n) {
	switch(n % 4) {
		case 0: return n;
		case 1: return 1;
		case 2: return n ^ 1;
		case 3: return 0;
	}
}

int main() {
	lolong n = input();
	lolong ans = 0;
	for(lolong l = 1, r; l <= n ; l = r + 1) {
		r = n / (n / l);
		if(n / l & 1)
			ans ^= f(r) ^ f(l - 1);
	}
	printf("%lld\n", ans);
}
