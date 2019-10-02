#if 0
2019.10.02

在 T 串后面填加特殊字符 $ ，那么实际上就是要在 S 中找到最长的一个字典序比 T 大的后缀。
枚举答案后缀与 T 的最长公共前缀，假设为 U ，
那么只要 U 后面添加一个比 T[|U|] 大的字符后的 U2 仍是 S 的子串，就可以更新答案，
更新的值为 U2 的第一个出现位置。

如果从小到大枚举 U ，那么涉及到的子串转移只有在尾部添加字符，
对 S 建出 SAM ，U 的长度增加可以在 SAM 上直接转移，
然后枚举比 T[|U|] 大的字符 x 添加在 U 后头，同样在 SAM 上转移。
为了更新答案，只需维护 SAM 每个点的第一个出现位置即可。
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 200005, maxq = 5050, maxk = 26;
char s[maxn], t[maxn];
int ch[maxn << 1][maxk], len[maxn << 1], fa[maxn << 1];
int first[maxn << 1];

int build(int n) {
	int p = 1, last = 1;
	for(int i = 1; i <= n; i ++) {
		int x = s[i] - 'a';
		int now = ++ p;
		first[now] = i;
		len[now] = len[last] + 1;

		int pre = last;
		while(pre and !ch[pre][x]) {
			ch[pre][x] = now;
			pre = fa[pre];
		}

		if(pre) {
			int preto = ch[pre][x];
			if(len[preto] == len[pre] + 1)
				fa[now] = preto;
			else {
				int sp = ++ p;
				first[sp] = first[preto];
				len[sp] = len[pre] + 1;

				fa[sp] = fa[preto];
				for(int j = 0; j < maxk; j ++)
					ch[sp][j] = ch[preto][j];

				while(pre and ch[pre][x] == preto) {
					ch[pre][x] = sp;
					pre = fa[pre];
				}

				fa[preto] = sp;
				fa[now] = sp;
			}
		}

		else
			fa[now] = 1;

		last = now;
	}

	/* for(int i = 1; i <= p; i ++) { */
	/* 	debug("%d: %d %d\n", i, len[i], first[i]); */
	/* 	for(int x = 0; x < maxk; x ++) */
	/* 		if(ch[i][x]) */
	/* 			debug("-%c> %d\n", 'a' + x, ch[i][x]); */
	/* } */

	return p;
}

int main() {
	int q = input();
	scanf("%s", s + 1);

	int n = int(strlen(s + 1));

	build(n);

	while(q --) {
		scanf("%s", t + 1);
		int m = int(strlen(t + 1));
		int now = 1;
		int ans = n + 1;

		for(int i = 1; i <= m; i ++) {
			int nx = t[i] - 'a';
			for(int x = nx + 1; x < maxk; x ++) {
				int to = ch[now][x];
				if(to)
					ans = std::min(ans, first[to] - i + 1);
			}
			now = ch[now][nx];
		}

		if(ans + m - 1 > n)
			puts("-1");
		else
			printf("%d\n", ans - 1);
	}
}
