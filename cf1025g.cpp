#if 0
2020.05.16

  学到许多，处理期望问题的又一利器。
  对于一个状态 S ，定义一个势能函数 f(S) ，对于每个 S 能一步操作转移到的状态 T ，f(T) 的
期望和 f(S) 的差是个非零常数，那么通过初始状态和最终状态的势能函数差值就能求出操作数的期
望。
  对于本题，单独考虑每个红点，如果其挂了 k 个白点，设其势能为 g(k) ，然后令一个状态的势
能为所有红点的势能的和。
  然后每次操作选中两个红点，分别挂了 x, y 个白点，如果总能满足对于这对红点操作后它们两个
的势能期望变化量为常数问题就能解决了。也就是说要满足下面这个式子与 x, y 无关且非零：
    g(x) + g(y) - (x g(0) + g(y + 1) + y g(0) + g(x + 1)) / 2
  不难得到 g(x) = 2^x - 1 。

  更严谨的，设随机变量 X_i 为 i 次操作后的势能和减去 i ，那么由于势能每次期望加一，那么
X_{i+1} 的条件期望就是 X_i 的值，也就是说 X 是鞅，要求的是停时 T 的期望，根据停时定理，
有 E(X_T) = X_0 ，另外有 X_T = 2^{n-1} - 1 - T ，由于 X_0 已知，根据这两个方程就可以求出
T 的期望了。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 505, mod = 1000000007;
int a[maxn];
int tot[maxn];
ll f[maxn];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) {
		read(a[i]);
		if (a[i] != -1) ++ tot[a[i]];
	}

	for (int i = 1; i <= n; i ++)
		f[i] = (f[i - 1] * 2 + 1) % mod;

	ll begin = 0;
	for (int i = 1; i <= n; i ++)
		begin += f[tot[i]];
	begin %= mod;
	ll end = f[n - 1];
	printf("%lld\n", (end - begin + mod) % mod);
}
