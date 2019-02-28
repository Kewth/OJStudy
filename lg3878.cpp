#if 0
2019.02.28

一开始还准备退火来着。。。
n=30 是折半搜索的范围啊。。。
比较普通的折半搜索题，对于两边的答案用 set 统计即可。

#endif
#include <bits/stdc++.h>

int input() { int res; scanf("%d", &res); return res; }

typedef long long lolong;
const int maxn = 33;
int num[maxn];
std::set<lolong> s[maxn << 1], fs[maxn << 1];

int main() {
	srand(0xccf666);
	int testdata = input();
	while(testdata --) {
		/* fprintf(stderr, "---\n"); */
		int n = input();
		for(int i=0; i<(n<<1); i++) {
			s[i].clear();
			fs[i].clear();
			s[i].insert(INT64_MAX >> 1);
			fs[i].insert(INT64_MAX >> 1);
		}
		for(int i=0; i<n; i++)
			num[i] = input();
		int m = n >> 1;
		for(int S=0; S<(1<<m); S++) {
			lolong sum = 0;
			int cha = 0;
			for(int i=0; i<m; i++)
				if(S >> i & 1) {
					sum += num[i];
					cha ++;
				} else {
					sum -= num[i];
					cha --;
				}
			/* fprintf(stderr, "insert %lld in %d\n", sum, cha); */
			s[n + cha].insert(sum);
			fs[n + cha].insert(- sum);
		}
		int M = m;
		m = n - m;
		lolong ans = INT64_MAX;
		for(int S=0; S<(1<<m); S++) {
			lolong sum = 0, now = INT64_MAX;
			int cha = 0;
			for(int i=0; i<m; i++)
				if(S >> i & 1) {
					sum += num[i + M];
					cha ++;
				} else {
					sum -= num[i + M];
					cha --;
				}
			now = std::min(now, *s[n + cha - 1].lower_bound(sum) - sum);
			now = std::min(now, *s[n + cha].lower_bound(sum) - sum);
			now = std::min(now, *s[n + cha + 1].lower_bound(sum) - sum);
			now = std::min(now, *fs[n + cha - 1].lower_bound(- sum) + sum);
			now = std::min(now, *fs[n + cha].lower_bound(- sum) + sum);
			now = std::min(now, *fs[n + cha + 1].lower_bound(- sum) + sum);
			/* fprintf(stderr, "%lld -> %lld\n", sum, now); */
			if(now < 0)
				now = - now; // 不知道为什会有负数。。。
			ans = std::min(ans, now);
		}
		printf("%lld\n", ans);
	}
}
