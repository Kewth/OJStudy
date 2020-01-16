#if 0
2020.01.16

不妨统计 m 个子集有序的情况。
设 f[m] 表示方案，考虑第 m 个子集的选取。
由于要满足所有子集的“异或”为空集，
事实上只要前 m - 1 个子集确定后第 m 个子集也确定了。
前 m - 1 个随便选，方案数为 A(K, m - 1) ，其中 K 是子集数量，即 2^n - 1 。
但是这样不能保证合法，有两种非法情况需要减去：
1) 前 m - 1 个子集“异或”为空集，这样的方案数为 f[m - 1]
2) 第 m 个子集与前面第 x 个子集相同。
考虑 2) 这样的方案，除了第 x, m 个子集外其他子集的“异或”仍然为空集，
相当于先选出 m - 2 个“异或”为空集的子集，然后插入第 x 个子集，
方案数为 f[m - 2] (K - m + 2) (m - 1)
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1000005, mod = 100000007;
struct num {
	int val;
	num(int val = 0): val(val) { }
};
inline num operator * (num x, num y) { return num(1ll * x.val * y.val % mod); }
inline num& operator *= (num &x, num y) { return x = x * y; }
inline num operator + (num x, num y) { int v = x.val + y.val; return num(v >= mod ? v - mod : v); }
inline num& operator += (num &x, num y) { return x = x + y; }
inline num operator - (num x, num y) { int v = x.val - y.val; return num(v < 0 ? v + mod : v); }
inline num& operator -= (num &x, num y) { return x = x - y; }
inline num operator ^ (num x, int k) {
	num res = 1;
	while(k) {
		if(k & 1) res *= x;
		x *= x;
		k >>= 1;
	}
	return res;
}
inline num& operator ^= (num &x, int k) { return x = x ^ k; }
inline num operator / (num x, num y) { return x * (y ^ (mod - 2)); }
inline num& operator /= (num &x, num y) { return x = x / y; }

num A[maxn], f[maxn];
int main() {
	int n = read, m = read;

	num po = (num(2) ^ n) - 1;
	A[0] = 1;
	for(int i = 1; i <= m; i ++)
		A[i] = A[i - 1] * (po - i + 1);

	f[0] = 1;
	f[1] = 0;
	for(int i = 2; i <= m; i ++)
		f[i] = A[i - 1] - f[i - 1] - f[i - 2] * (po - i + 2) * (i - 1);

	num fac = 1;
	for(int i = 1; i <= m; i ++)
		fac *= i;

	printf("%d\n", (f[m] / fac).val);
}
