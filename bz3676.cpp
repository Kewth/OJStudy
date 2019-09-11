#if 0
2019.09.10

PAM 模板，每个状态被走到会使其 fail 树祖先的所有状态出现次数 +1 ，树上差分即可。
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 300005, maxk = 26;
int ch[maxn][maxk];
int fail[maxn];
int len[maxn];
int times[maxn];
char s[maxn];

int main() {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1));

	fail[1] = 0;
	len[1] = -1;
	fail[2] = 1;
	len[2] = 0;

	int cp = 2, last = 2;

	for(int i = 1; i <= n; i ++) {
		int pre = last;
		while(fail[pre] and s[i - len[pre] - 1] != s[i])
			pre = fail[pre];

		int &now = ch[pre][s[i] - 'a'];
		if(not now) {
			now = ++ cp;
			len[now] = len[pre] + 2;

			pre = fail[pre];
			while(fail[pre] and s[i - len[pre] - 1] != s[i])
				pre = fail[pre];

			fail[now] = pre ? ch[pre][s[i] - 'a'] : 2;
		}

		last = now;
		times[last] ++;

		/* debug("%d: (%c) f=%d, l=%d\n", now, s[i], fail[now], len[now]); */
	}

	lolong ans = 0;

	for(int i = cp; i > 2; i --) {
		times[fail[i]] += times[i];
		ans = std::max(ans, 1ll * len[i] * times[i]);
	}

	printf("%lld\n", ans);
}
