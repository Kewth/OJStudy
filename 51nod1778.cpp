#if 0
2019.07.29

把式子中的组合数用卢卡斯定理拆开，
然后除以 m 的可以提出来与 sigma 无关，模 m 的可以 O(mlog) 暴力算。
51nod 比较毒瘤，暴力过程中可以发现前一半和后一半是对称的，可以只算一半，卡一半的常数。
#endif
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() {
	int c = getchar(), x = 0;
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

const int maxn = 1000006;
char s[maxn];
int mod;

inline lolong power(lolong x, int k) {
	if(x < 0) x += mod;
	if(k < 0) k += mod - 1;
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

lolong fuck(int n, int k) {
	lolong res = 0, C = 1;
	for(int i = 0; i <= (n - 1) / 2; i ++) {
		res += C * power(power(i, k) - power(n - i, k), 2) * 2 % mod;
		// n < mod
		(C *= n - i) %= mod;
		(C *= power(i + 1, -1)) %= mod;
	}
	if(n / 2 == n - n / 2)
		res += C * power(power(n / 2, k) - power(n / 2, k), 2) % mod;
	return res % mod;
}

int main() {
	scanf("%s", s);
	int k = input(), len = strlen(s);
	mod = input();
	int a = 0, b = 0;
	for(int i = 0; i < len; i ++) {
		a *= 10;
		b = b * 10 + s[i] - '0';
		a += b / mod;
		b %= mod;
		a %= mod - 1;
	}
	// debug("%d, %d\n", a, b);
	printf("%lld\n", power(2, a) * fuck(b, k) % mod);
}
