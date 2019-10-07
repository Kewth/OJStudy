#if 0
2019.10.07

改题自闭了玩一玩通信。
A 直接把 s 扔给 B 的话需要 2n 次通信，而且这样小 B 没有任何通信。
让两人同时维护一个 has 表示已经考虑 s 已经考虑过的前缀。
B 每次告诉 A 应该输出 s[has + 1] 还是 s[has + 2] 即可，
但是最坏情况下，当 B 的下标都 > n 时，这样需要 1.5n 次通信。

注意到如果 s 随机， 通信次数还是很优秀的，期望 1.33n 次。
两人约定一个随机数种子，将 s 随机打乱，按照打乱的顺序进行上述算法即可。
#endif
#include <cstdio>
#include <algorithm>

const int maxn = 1010;
int p[maxn];
char s[maxn];
int r[maxn << 1];
int ip[maxn << 1];

int main() {
	int n, m;
	FILE *get = fopen("bob.in", "r");
	FILE *out = fopen("bob.out", "w");

	fscanf(get, "%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		fscanf(get, "%d", p + i);

	srand(19491001);
	for(int i = 1; i <= (n << 1); i ++)
		r[i] = i;
	std::random_shuffle(r + 1, r + (n << 1) + 1);

	for(int i = 1; i <= n; i ++)
		ip[p[i]] = i;

	/* for(int i = 1; i <= (n << 1); i ++) */
	/* 	fprintf(stderr, "%d\n", r[i]); */

	int now = 0, has = 0;
	while(now < n) {
		/* fprintf(stderr, "[%c]", "10"[bool(ip[r[has + 1]])]); */
		putchar("10"[bool(ip[r[has + 1]])]);
		fflush(stdout);

		char c = char(getchar());
		if(c == EOF)
			break;
		if(c != '0' and c != '1')
			continue;

		if(ip[r[has + 1]])
			has ++;
		else
			has += 2;

		/* fprintf(stderr, "(%d,%d,%d)\n", has, r[has], ip[r[has]]); */

		if(ip[r[has]]) {
			s[ip[r[has]]] = c;
			now ++;
		}
	}

	fputs(s + 1, out);
}
