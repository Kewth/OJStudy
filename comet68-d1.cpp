#if 0
2019.10.01

枚举做完的试卷数量，然后对于剩下的试卷贪心选时间最少的做，
将题目按时间排序，二分能做完的题目即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 100005;
lolong t[maxn];
lolong pret[maxn];

int main() {
	int q = input();
	while(q --) {
		int n = input(), m = input(), k = input();
		lolong T = linput();

		for(int i = 1; i <= m; i ++)
			t[i] = input();
		std::sort(t + 1, t + m + 1);
		for(int i = 1; i <= m; i ++)
			pret[i] = pret[i - 1] + t[i];

		lolong sum = pret[m];

		if(T / sum >= n) {
			printf("%lld\n", 1ll * (m + k) * n);
			continue;
		}

		lolong nowt = T % sum;
		lolong ans = 0;

		for(int s = T / sum; s >= 0; s --) {
			int l = 0, r = m;
			while(l < r) {
				int mid = (l + r + 1) >> 1;
				if((n - s) * pret[mid] <= nowt)
					l = mid;
				else
					r = mid - 1;
			}
			lolong nt = nowt - (n - s) * pret[l];
			ans = std::max(ans, 1ll * (n - s) * l + nt / t[l + 1] + 1ll * s * (m + k));
			nowt += sum;
		}
		printf("%lld\n", ans);
	}
}
