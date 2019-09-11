#if 0
2019.09.11

PAM 模板，额外记 half[x] 表示 x 状态跳 fail 跑到第一个长度不超过 x 一半的状态。
维护 half 的方法与维护 fail 类似，
统计答案的话枚举所有回文子串用 half 和 len 可以 O(1) 判断是否为双倍回文。
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 500005, maxk = 26;
int ch[maxn][maxk];
int fail[maxn];
int half[maxn];
int len[maxn];
char s[maxn];

int main() {
	int n = input();
	scanf("%s", s + 1);

	len[1] = -1;
	half[2] = 1;
	fail[2] = 1;

	int cp = 2, last = 2;

	int ans = 0;

	for(int i = 1; i <= n; i ++) {
		int pre = last;
		while(fail[pre] and s[i - len[pre] - 1] != s[i])
			pre = fail[pre];

		int &now = ch[pre][s[i] - 'a'];
		if(not now) {
			now = ++ cp;
			len[now] = len[pre] + 2;

			int f;
			f = fail[pre];
			while(fail[f] and s[i - len[f] - 1] != s[i])
				f = fail[f];

			fail[now] = f ? ch[f][s[i] - 'a'] : 2;

			f = half[pre];
			while(fail[f] and (len[f] + 2) * 2 > len[now])
				f = fail[f];
			while(fail[f] and s[i - len[f] - 1] != s[i])
				f = fail[f];

			half[now] = f ? ch[f][s[i] - 'a'] : 2;

			if(len[half[now]] * 2 == len[now] and len[now] % 4 == 0)
				ans = std::max(ans, len[now]);
		}

		last = now;

		/* debug("%d: (%c) f=%d, l=%d\n", now, s[i], fail[now], len[now]); */
	}

	printf("%d\n", ans);
}
