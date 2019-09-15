#if 0
2019.09.15

游戏的状态可以用三个数表示： (a, b, c) ，
其中 a, b 是左右问号数， c 是左右确定的数的差（有向）。
设 f[a][b] 表示该状态下先手必胜（如果 a + b 为奇数，Bicarp 先手）的 c 的取值范围。
初始状态 f[0][0] = 0 。
不难归纳出当 a + b 为偶数时 f[a][b] = 9a - 9 (a + b) / 2 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005;
char s[maxn << 1];

int main() {
	int n = input() >> 1;
	scanf("%s", s + 1);

	int a = 0, b = 0, c = 0;
	for(int i = 1; i <= n; i ++)
		if(s[i] == '?')
			a ++;
		else
			c -= s[i] - '0';

	for(int i = n * 2; i > n; i --)
		if(s[i] == '?')
			b ++;
		else
			c += s[i] - '0';

	if(c * 2 == 9 * a - 9 * b)
		puts("Bicarp");
	else
		puts("Monocarp");
}
