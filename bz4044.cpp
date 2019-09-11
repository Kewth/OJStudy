#if 0
2019.09.11

PAM 处理出所有回文子串状态，考虑 DP ，设 f[i] 表示构造 i 状态的最小代价。
最终的串一定是由一个回文串加暴力操作得来，故答案为 min(f[i] + n - len[i]) 。

考虑转移，事实上 f[i] 的转移涉及到所有 i 状态的回文子串，
因为 i 状态的最优构造方式可能是两种：
1) 一个回文子串 j 加上暴力操作得来。
2) 如果是偶串，可能是由一半（不超过一半的回文子串 j 加暴力）复制而来。
3) 如果是偶串，由转移自 i 的状态 k 加一而来（复制到 k 前先加一个）
对于 1) 2) 枚举 j 无论是实现还是复杂度上都是难以接受的。

但事实上对于 1) 2) ，如果 f[i] 的最优转移 j 不是后缀也不是前缀，
那么这个转移都会被 3) 覆盖。
因此对于 1) 2) 不需要枚举 j 只要考虑 i 的后缀即可，

记录 half[i] 表示跳 fail 到第一个长度不大于 i 的一半的状态，
那么 1) 2) 可以通过 fail 和 half 实现。
#endif
#include <cstdio>
#include <algorithm>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 500005, maxk = 4;
int ch[maxn][maxk];
int fail[maxn];
int half[maxn];
int len[maxn];
int dp[maxn];
char s[maxn];
int toi[256];

int main() {
	toi['A'] = 0;
	toi['T'] = 1;
	toi['C'] = 2;
	toi['G'] = 3;

	len[1] = -1;
	half[2] = 1;
	fail[2] = 1;
	dp[2] = 1;

	int T = input();

	while(T --) {
		scanf("%s", s + 1);
		int n = int(strlen(s + 1));

		int cp = 2, last = 2;

		int ans = n;

		for(int i = 1; i <= n; i ++) {
			int pre = last;
			while(fail[pre] and s[i - len[pre] - 1] != s[i])
				pre = fail[pre];

			int &now = ch[pre][toi[int(s[i])]];
			if(not now) {
				now = ++ cp;
				len[now] = len[pre] + 2;

				int f;
				f = fail[pre];
				while(fail[f] and s[i - len[f] - 1] != s[i])
					f = fail[f];

				fail[now] = f ? ch[f][toi[int(s[i])]] : 2;

				f = half[pre];
				while(fail[f] and (len[f] + 2) * 2 > len[now])
					f = fail[f];
				while(fail[f] and s[i - len[f] - 1] != s[i])
					f = fail[f];

				half[now] = f ? ch[f][toi[int(s[i])]] : 2;

				dp[now] = dp[fail[now]] + len[now] - len[fail[now]];
				if(not (len[now] & 1))
					dp[now] = std::min(dp[now], dp[pre] + 1);
				if(not (len[now] & 1))
					dp[now] = std::min(dp[now],
							dp[half[now]] + (len[now] >> 1) - len[half[now]] + 1);

				ans = std::min(ans, dp[now] + n - len[now]);
			}

			last = now;

			/* debug("%d: (%c) f=%d, h=%d, l=%d, d=%d\n", */
			/* 		now, s[i], fail[now], half[now], len[now], dp[now]); */
		}

		printf("%d\n", ans);

		for(int i = 1; i <= cp; i ++)
			for(int k = 0; k < maxk; k ++)
				ch[i][k] = 0;
	}
}
