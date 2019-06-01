#if 0
2019.06.01

哥德巴赫猜想。
这里把 1 看做质数。
若 n 为质数，答案为 1 。
否则 n 为不小于 4 的合数 ，分奇偶。
n 为偶数时，一定可以拆分成两个质数的和，答案为 2 。
n 为奇数时，可以拆分成 n - 1 和 1 ，n - 1 可以拆成两个质数，此时答案为 3 。
同时 n 也可以拆成 n - 2 和 2 ，若 n - 2 是一个质数，答案为 2 。
#endif
#include <cstdio>

bool is_prime(int n) {
	for(int x = 2; x * x <= n; x ++)
		if(not (n % x))
			return false;
	return true;
}

int main() {
	int n;
	scanf("%d", &n);
	if(is_prime(n)) puts("1");
	else if(not (n & 1)) puts("2");
	else if(is_prime(n - 2)) puts("2");
	else puts("3");
}
