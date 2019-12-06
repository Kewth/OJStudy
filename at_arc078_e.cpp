#if 0
2019.12.06

假设已知 N 的长度 len ，考虑如何搞出 N 。
不难想到二分，但如果询问一个长度为 len 的 x ，那么得到的一定是 yes ，
因为相同长度的两个数的字典序比较和值比较无异。
但只要询问 10x ，10x 的长度为 len + 1 ，值一定比 N 大，
那么得到 yes 当且仅当 x 的值不比 N 小，可以据此二分。

现在的问题是得到 N 的长度，事实上只需要拿 10 的整次幂一个一个试即可。
特别的是当 N 是 10 的整次幂的情况无法据此得出长度，需要特判。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

bool query(ll x) {
	printf("? %lld\n", x);
	fflush(stdout);
	static char s[10];
	scanf("%s", s);
	return *s == 'Y';
}

int main() {
	ll test = 1;

	while(test <= 100000000000ll and query(test))
		test *= 10;

	if(test > 100000000000ll) {
		test = 9;
		while(!query(test))
			test = test * 10 + 9;
		printf("! %lld\n", test / 10 + 1);
		return 0;
	}

	ll l = test / 10, r = test - 1;
	while(l < r) {
		ll mid = (l + r) >> 1;
		if(query(mid * 10))
			r = mid;
		else
			l = mid + 1;
	}

	printf("! %lld\n", l);
}
