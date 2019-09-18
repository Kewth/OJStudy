#if 0
2019.09.18

建 SAM ，维护 SAM 上每个点的出现次数。
求第 k 大可以在 SAM 上跑，需要维护每个点的 size 表示从该状态出发一共可以到达的子串数目。
t = 0 时钦定所有状态出现次数为 1 即可。
#endif
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 500005, maxk = 26;
char s[maxn], ans[maxn];
int ap;
int ch[maxn << 1][maxk];
int fa[maxn << 1];
int du[maxn << 1];
int len[maxn << 1];
int times[maxn << 1];
lolong size[maxn << 1];
int stack[maxn << 1], stp;

void dfs(int now) {
	if(size[now])
		return;
	size[now] = times[now];
	for(int x = 0; x < maxk; x ++)
		if(ch[now][x]) {
			/* debug("%d -> %d\n", now, ch[now][x]); */
			dfs(ch[now][x]);
			size[now] += size[ch[now][x]];
		}
	/* debug("%d : %lld\n", now, size[now]); */
}

void kth(int now, int k) {
	/* debug("%d in %lld (%d)\n", k, size[now], times[now]); */
	if(k <= times[now])
		return;
	k -= times[now];
	for(int x = 0; x < maxk; x ++)
		if(ch[now][x]) {
			if(k <= size[ch[now][x]]) {
				ans[++ ap] = char('a' + x);
				kth(ch[now][x], k);
				return;
			}
			k -= size[ch[now][x]];
		}
}

int main() {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1));
	int t = input(), k = input();

	int p = 1, last = 1;
	for(int i = 1; i <= n; i ++) {
		int x = s[i] - 'a';
		int now = ++ p;
		len[now] = len[last] + 1;
		times[now] = 1;

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

	for(int i = 1; i <= p; i ++)
		du[fa[i]] ++;

	for(int i = 1; i <= p; i ++)
		if(!du[i])
			stack[++ stp] = i;

	if(!t)
		for(int i = 1; i <= p; i ++)
			times[i] = 1;

	else
		while(stp) {
			int x = stack[stp --];
			/* debug("%d : %d\n", x, times[x]); */
			times[fa[x]] += times[x];
			du[fa[x]] --;
			if(!du[fa[x]])
				stack[++ stp] = fa[x];
		}

	times[1] = 0;
	dfs(1);
	kth(1, k);

	if(ap)
		puts(ans + 1);
	else
		puts("-1");

	/* for(int i = 1; i <= p; i ++) */
	/* 	debug("%d: %d, %d, fa=%d, t=%d\n", i, ch[i][0], ch[i][1], fa[i], times[i]); */
}
