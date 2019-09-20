#if 0
2019.09.19

一个数出现次数超过一半的话，它的二进制位的每一位单独考虑也一定超过一半。
那么问题转换为 01 序列，代价是一个 log 。
01 序列求众数直接用前缀和查区间值即可。
另外需要判断无解，求出答案 x 后在 pos[x] 里二分出 x 的数量即可，
其中 pos[x] 是 x 的出现位置集合。
一个坑点是算出来的 x 可能根本不存在。
#endif
#include <cstdio>
#include <vector>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 500005, maxk = 20;
int s[maxk][maxn];
std::vector<int> pos[maxn];

int main() {
	int n = input(), q = input();

	for(int i = 1; i <= n; i ++) {
		int x = input();
		for(int k = 0; k < maxk; k ++)
			s[k][i] = s[k][i - 1] + (x >> k & 1);
		pos[x].push_back(i);
	}

	while(q --) {
		int l = input(), r = input(), ans = 0;

		for(int k = 0; k < maxk; k ++) {
			int x = s[k][r] - s[k][l - 1];
			if((x << 1) > r - l + 1)
				ans |= 1 << k;
		}

		if(ans > n) {
			puts("0");
			continue;
		}

		int lp = int(
				std::lower_bound(pos[ans].begin(), pos[ans].end(), l) - pos[ans].begin());
		int rp = int(
				std::upper_bound(pos[ans].begin(), pos[ans].end(), r) - pos[ans].begin() - 1);

		if(((rp - lp + 1) << 1) > r - l + 1)
			printf("%d\n", ans);
		else
			puts("0");
	}
}
