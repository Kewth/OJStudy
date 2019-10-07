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
#include <cstdlib>
#include <algorithm>

const int maxn = 1010;
char s[maxn];
int p[maxn];
int r[maxn << 1];

int main() {
	int n, m;
	FILE *get = fopen("alice.in", "r");
	fscanf(get, "%d%d%s", &n, &m, s + 1);

	srand(19491001);
	for(int i = 1; i <= (n << 1); i ++)
		r[i] = i;
	std::random_shuffle(r + 1, r + (n << 1) + 1);

	/* for(int i = 1; i <= (n << 1); i ++) */
	/* 	fprintf(stderr, "%d\n", r[i]); */

	int has = 0;
	while(has <= (n << 1)) {
		int x = getchar() - '0' + 1;
		if(x == EOF - '0' + 1) break;
		if(x != 1 and x != 2) continue;
		has += x;
		putchar(s[r[has]]);
		fflush(stdout);
	}
}
