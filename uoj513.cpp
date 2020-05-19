#if 0
2020.05.18

  第二个操作就是依次把每个白点的连边全部翻转，那么可以发现这个操作至多只需要进行一次。
  考虑什么样的图可以通过 m 次第一个操作变得合法，首先由于每次操作的对象是一个简单环，那
一个可能合法的图每个点的带权度数必须是偶数。而且只要满足这个条件，就一定能通过不超过 m
次操作把图变得合法。因为考虑有权的边构成的子图，由于每个点的度数为偶数，一定存在欧拉回
路，而欧拉回路一定可以被分解为 O(m) 个简单环。
  那么可以列出一个异或方程，设 x_i 表示第 i 个点是否被第二个操作选中，那么由于每个点经过
第二个操作后带权度数都要是偶数，可以对每个点列出一个方程，判断异或方程组是否有解即可。
  只需要判断方程组是否有解，可以不用高斯消元，用线性基即可，方程组有解当且仅当 1 不能被
这些方程线性表示。
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef size_t si;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 305;
typedef std::bitset<maxn> bs;
bs ma[maxn], bas[maxn];

bool insert (bs x, int n) {
	for (int k = 1; k <= n; k ++)
		if (x.test(si(k))) {
			if (bas[k].any())
				x ^= bas[k];
			else
				return bas[k] = x, 1;
		}
	return x.test(si(n + 1)) == 0;
}

int main () {
	int T = read;
	while (T --) {
		int n = read, m = read;
		for (int i = 1; i <= n; i ++)
			bas[i].reset(), ma[i].reset();

		for (int i = 1; i <= m; i ++) {
			int u = read, v = read, w = read;
			ma[u].set(si(v));
			ma[v].set(si(u));
			ma[u].flip(si(u));
			ma[v].flip(si(v));
			if (w) {
				ma[u].flip(si(n + 1));
				ma[v].flip(si(n + 1));
			}
		}

		for (int i = 1; i <= n; i ++)
			if (!insert(ma[i], n)) {
				puts("no");
				goto fail;
			}
		puts("yes");
fail:;
	}
}
