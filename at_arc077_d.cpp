#if 0
2019.09.18

观察偶串 SS 变换后的形式，事实上是 STST ，其中 T 是 S 的最小循环节。
那么设 g(S) = ST ，则有 f(SS) = g(S)g(S) ， f^k(SS) = g^k(S)g^k(S) 。
考虑 g^k(S) 的变换过程。

当 |T| | |S| 时，有 g(S) = ST, g^2(S) = STS, g^3(S) = STSST ...
容易得出递推式 g^k(S) = g^{k-1}(S) + g^{k-2}(S) 。

否则，有 g(S) = ST, g^2(S) = STT, g^2(S) = STTT ...
容易得出递推式 g^k(S) = g^{k-1}(S) + T 。

第一种情况下 g^k(S) 的长度增长很快，和斐波那契类似，
因此有用的 g^k(S) 很少，可以预处理出每个 g^k(S) 的字母构成。
假设要求 f..f(S) 的前 n 位，那么找到超过 n/2 的最小 g^k(S) ，
这个 g^k(S) 一定是 f..f(S) 的前半段，统计进去，
剩下的部分长 n - |g^k(S)| ，一定是 f..f(S) 后半段的前缀，即前半段的前缀，转为子问题。
由于每次长度至少减少一半，这样统计的次数是 O(log) 的。

第二种情况下 g^k(S) 长度增长呈等差数列，无法处理，
但是注意到上述算法中并不关心 g^k(S) 具体的 k 是多少，
因此可以按照第一种情况的递推式算，这样每个 g^k(S) 对应的实际上是一个 g^i(S) 满足 i > k 。
而只要 g^k(S) 能对应一个真正的 g^i(S) ，上述的算法就能保证正确性。
#endif
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 100005, maxk = 26;
struct Val {
	lolong a[maxk];
	lolong len;
	void operator += (Val an) {
		for(int i = 0; i < maxk; i ++)
			a[i] += an.a[i];
		len += an.len;
	}
	Val(): len(0) { memset(a, 0, sizeof a); }
};
char s[maxn << 1];
int fail[maxn];
Val g[100];

void solve(lolong n, Val &ans) {
	/* debug("%lld\n", n); */
	if(n <= g[0].len) {
		for(int i = 1; i <= n; i ++)
			ans.a[s[i] - 'a'] ++;
		ans.len += n;
		return;
	}

	int p = 0;
	while((g[p].len << 1) < n)
		p ++;
	ans += g[p];

	solve(n - g[p].len, ans);
}

int main() {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1)) >> 1;

	fail[0] = -1;
	for(int i = 1; i <= n; i ++) {
		int j = fail[i];
		while(~j and s[j + 1] != s[i + 1])
			j = fail[j];
		fail[i + 1] = j + 1;
	}

	int k = n - fail[n];
	lolong l = linput(), r = linput();

	for(int i = 1; i <= n; i ++)
		g[0].a[s[i] - 'a'] ++;
	g[0].len = n;

	g[1] = g[0];
	for(int i = 1; i <= k; i ++)
		g[1].a[s[i] - 'a'] ++;
	g[1].len = n + k;

	for(int i = 2; (g[i - 1].len << 1) < r; i ++) {
		g[i] = g[i - 1];
		g[i] += g[i - 2];
	}

	Val a, b;
	solve(l - 1, a);
	solve(r, b);
	/* debug("%lld %lld\n", a.len, b.len); */

	for(int i = 0; i < maxk; i ++)
		printf("%lld ", b.a[i] - a.a[i]);
	puts("");
}
