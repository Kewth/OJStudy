#if 0
2019.09.15

交换 s, t 两个字母可以拆成两步：把 s/t 的一个 a 变成 b ，把 t/s 的一个 b 变成 a 。
只要 s/t 中 a 变 b 的数量与 t/s 中 b 变 a 的数量相同，就是合法的。
那么从左到右扫，扫到 s, t 不一样的位置就把一方变成另一方，
优先变 s ，如果能和一个已经变 s 的操作合成一个交换操作就变 t 。
到最后可能还会剩下两个变 s 的操作没被合成，且一定是一个变 a 一个变 b 。
随便在 t 中选一个字母变两次从而得到两个操作与上述操作合成两个交换操作即可。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 200005;
char s[maxn], t[maxn];
int ans_x[maxn << 1], ans_y[maxn << 1], ap;

int main() {
	int n = input();
	scanf("%s", s + 1);
	scanf("%s", t + 1);

	int cnt[2] = {0, 0};
	for(int i = 1; i <= n; i ++)
		cnt[s[i] - 'a'] ++;
	for(int i = 1; i <= n; i ++)
		cnt[t[i] - 'a'] ++;

	if(cnt[0] % 2 and cnt[1] % 2) {
		puts("-1");
		return 0;
	}

	int que[2] = {0, 0};
	for(int i = 1; i <= n; i ++)
		if(s[i] != t[i]) {
			if(not que[s[i] - 'a'])
				que[s[i] - 'a'] = i;
			else {
				ap ++;
				ans_x[ap] = que[s[i] - 'a'];
				ans_y[ap] = i;
				que[s[i] - 'a'] = 0;
			}
		}

	if(que[0] and que[1]) {
		ap ++;
		ans_x[ap] = que[1 - (t[1] - 'a')];
		ans_y[ap] = 1;
		ap ++;
		ans_x[ap] = que[t[1] - 'a'];
		ans_y[ap] = 1;
	}

	printf("%d\n", ap);
	for(int i = 1; i <= ap; i ++)
		printf("%d %d\n", ans_x[i], ans_y[i]);
}
