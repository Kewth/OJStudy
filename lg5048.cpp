#if 0
2019.10.14

朴素的在线区间众数的做法需要记块的前缀的每个数的数量，空间 O(n^1.5) 。
这个用于零散块更新答案，来计算当前的数的出现次数是否比当前答案多。
但事实上没有必要用这个维护所有块区间的所有数的出现次数，
只需要对每个数开 vector 记录所有下标，由于零散块一定在区间的边上，
对于零散块的每个 x ，只需 check 它前面/后面第 tot 个 x 是否在询问区间即可，
其中 tot 是当前众数出现次数。
但是这只能 check 是否比当前答案大，而无法直接更新答案，
考虑枚举零散部分的时候从内向外枚举，那么如果当前能够更新答案，只会让答案增加 1 。
而且 check 不能是询问区间，应该是“当前已经考虑的区间”。

这玩意常数确实不大，反正我是没卡常第一遍就过了。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 500005, maxb = 710;
int a[maxb * maxb], tmp[maxn];
int times[maxb][maxb];
int tot[maxn];
std::vector<int> pos[maxn];
int pid[maxn];
int B;

int main() {
	int n = input(), q = input();
	B = int(sqrt(n) + 1);

	for(int i = 0; i < n; i ++)
		tmp[i] = a[i] = input();

	std::sort(tmp, tmp + n);
	for(int i = 0; i < n; i ++)
		a[i] = int(std::lower_bound(tmp, tmp + n, a[i]) - tmp + 1);

	for(int i = 0; i < n; i ++) {
		pid[i] = pos[a[i]].size();
		pos[a[i]].push_back(i);
	}

	for(int l = 0; l < B; l ++) {
		memset(tot, 0, sizeof tot);
		for(int r = l; r < B; r ++) {
			if(r > l)
				times[l][r] = times[l][r - 1];
			for(int i = 0; i < B; i ++) {
				int x = a[r * B + i];
				if(x)
					times[l][r] = std::max(times[l][r], ++ tot[x]);
			}
		}
	}

	memset(tot, 0, sizeof tot);

	int ans = 0;
	while(q --) {
		int l = (input() ^ ans) - 1;
		int r = (input() ^ ans) - 1;
		int L = l / B + 1, R = r / B - 1;
		/* debug("%d %d\n", l, r); */

		if(L > R) {
			ans = 0;
			for(int i = l; i <= r; i ++)
				ans = std::max(ans, ++ tot[a[i]]);
			for(int i = l; i <= r; i ++)
				tot[a[i]] --;
		}

		else {
			ans = times[L][R];
			for(int i = L * B - 1; i >= l; i --) {
				std::vector<int> &v = pos[a[i]];
				if(pid[i] + ans < v.size() and v[pid[i] + ans] < R * B + B)
					ans ++;
			}
			for(int i = R * B + B; i <= r; i ++) {
				std::vector<int> &v = pos[a[i]];
				if(pid[i] - ans >= 0 and v[pid[i] - ans] >= l)
					ans ++;
			}
		}

		printf("%d\n", ans);
	}
}
