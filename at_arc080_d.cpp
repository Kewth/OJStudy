#if 0
2020.05.03

  差分，那么区间翻转可以转换为翻转两个点，设两个点的距离为 d ，有三种情况：
  1) d 是奇质数，代价为 1
  2) d 是偶数，根据哥德巴赫猜想，代价为 2
  3) d 是奇合数，代价为 3
  将所有数按奇偶分类，对于第一种情况建二分图，求最大匹配，在剩下的点中最多只会有一对
需要用第三种边。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 205;
int a[maxn], ap;
int match[maxn];
bool vis[maxn];
bool nop[10000005];

bool find (int p) {
	for (int i = 1; i <= ap; i ++)
		if (!vis[i] and a[i] & 1 and !nop[std::abs(a[i] - a[p])]) {
			vis[i] = 1;
			if (!match[i] or find(match[i])) {
				match[i] = p;
				return 1;
			}
		}
	return 0;
}

int main () {
	int N = 10000000;
	nop[1] = 1;
	for (int i = 2; i <= N; i ++)
		if (!nop[i]) {
			if (i <= N / i)
				for (int j = i * i; j <= N; j += i)
					nop[j] = 1;
		}

	int n = read;
	for (int i = 1, las = -1; i <= n; i ++) {
		int x = read;
		if (x - 1 == las)
			a[ap] = x;
		else {
			a[++ ap] = x - 1;
			a[++ ap] = x;
		}
		las = x;
	}

	int tot = 0;
	for (int i = 1; i <= ap; i ++)
		if (!(a[i] & 1)) {
			std::fill(vis, vis + ap + 1, 0);
			tot += find(i);
		}

	int A = - tot, B = - tot;
	for (int i = 1; i <= ap; i ++)
		a[i] & 1 ? ++ A : ++ B;

	printf("%d\n", ap - tot + (A & 1));
}
