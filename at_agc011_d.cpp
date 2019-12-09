#if 0
2019.12.08

这。。。O(k) 能过？我本来只是想验证个猜想来着，一不小心就 AC 了。。。

不难归纳出串 S 经过一次碰撞后有两种情况：
1) S 的开头就是 A ，球直接弹飞，S 的开头变为 B
2) S 的开头不是 A ，球一定可以经过所有点，此后 S 取反后循环左移一位即为新的 S

关于 2) 的证明：
首先球如果刚跨过第 i 个点时第 i 个点一定是 A ，
因为能跨过它说明之前该点为 B ，那么跨过后就变成了 A 。
那么分两种情况：
i) A -> B ，直接变为 A A ->
ii) A -> A ，来回碰撞后变为 B A ->
不难发现每次第 i 个点就变成了第 i + 1 个点的相反。
对于边界，由于碰撞之前开头一定是 B ，碰撞之后结尾一定是 A ，所以也是成立的。

那么把 S 看作一个环，记一个反转标记和起点位置即可 O(k) 模拟，常数极小。

正解的话也很简单，事实上 S 的转移是 pho 形的，且链的长度是 2n 的因子，环的长度是 2 的因子．
令 k = 2n + (k - 2n) % 2 即可（仅适用于 k > 2n ）．
具体证明不会．
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 200005;
char s[maxn];

int main() {
	int n = read, k = read;
	scanf("%s", s + 1);

	if(k > (n << 1)) {
		k -= n << 1;
		k &= 1;
		k += n << 1;
	}

	int p = 1, A = 'A';
	while(k --) {
		if(s[p] == A)
			s[p] = 'A' + 'B' - s[p];
		else {
			A = 'A' + 'B' - A;
			++ p;
			if(p > n) p = 1;
		}
	}

	for(int i = p; i <= n; i ++)
		printf("%c", "BA"[s[i] == A]);
	for(int i = 1; i < p; i ++)
		printf("%c", "BA"[s[i] == A]);
	puts("");
}
