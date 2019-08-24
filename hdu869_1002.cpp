#if 0
2019.08.23

由于 a 是个排列，对于每个 a[i] = x 设 b[x] = i 。
修改操作相当于删掉一个点，在 b 上就是令 b[x] = INF 。
询问操作就是找到不小于 k 的最小 x 满足 b[x] > r 。
先不考虑修改，处理询问，发现一次二分后问题转换为 rmq ，
具体地，二分 x 判断答案是否在 [k, x] 内，那么 check 就是求 b[k:x] 的最大值。
用线段树维护最大值的话，不仅能解决这个问题，还能轻松处理修改。
但是套上二分是 O(log^2n) 的。
考虑使用 ST 表，虽然 ST 表不支持修改，但是对于修改操作有其他处理方法。
把删掉的点加入到 set 里边，那么询问中二分时直接把上界设为大于 k 的最小删除数即可。
#endif
#include <cstdio>
#include <set>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 500005, maxk = 20;
int st[maxn][maxk];
int a[maxn];
int highbit[maxn << 1];
int num[maxn];

int query(int l, int r) {
	int x = highbit[(r - l) + 1];
	return std::max(st[l][x], st[r - (1 << x) + 1][x]);
}

int main() {
	int T = input();

	while(T --) {
		int n = input(), q = input();

		for(int i = 1; i <= n; i ++) {
			num[i] = input();
			st[num[i]][0] = a[num[i]] = i;
		}

		for(int k = 0; k < maxk and (1 << k) <= n; k ++)
			for(int i = (1 << k); i < (1 << (k + 1)); i ++)
				highbit[i] = k;

		for(int k = 1; k < maxk and (1 << k) <= n; k ++)
			for(int i = 1; i <= n; i ++)
				st[i][k] = std::max(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);

		int ans = 0;
		std::set<int> erase;
		erase.insert(n + 1);

		while(q --) {
			int typ = input();

			if(typ == 1) {
				int pos = input() ^ ans;
				erase.insert(num[pos]);
			}

			else if(typ == 2) {
				int R = input() ^ ans, k = input() ^ ans;

				int l = k, r = *erase.lower_bound(k);
				while(l < r) {
					int mid = (l + r) >> 1;

					/* debug("%d-%d: %d\n", k, mid, query(k, mid)); */

					if(query(k, mid) <= R)
						l = mid + 1;
					else
						r = mid;
				}

				printf("%d\n", ans = l);
			}
		}
	}
}
