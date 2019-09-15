#if 0
2019.09.15

考虑加所有字符串构成的 Trie 。
将边按字典序排好并求出所有点子树的叶子节点数量 size 后，就可以 dfs 求第 k 大了。
但是点数是 B(26) * 26 的，这个数甚至可以爆 long long 。
当前的瓶颈在于求所有点的 size 。

事实上许多点的 size 相同，这些点的子树甚至一模一样。
合法的字符串实际上就是 A, B, C .. Z 第一次出现的位置递增。
那么可以用两个值区分子树相同的点：深度和祖先已经使用的字母数。

设 size[i][j] 表示子树内深度为 i ，祖先已经用了 j 个字母的点的 size 。
DP 枚举子树求值即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
typedef __int128 big;
/* typedef unsigned long long big; */
inline int input() { int x; scanf("%d", &x); return x; }
inline big binput() {
	big x = 0;
	int c = getchar();
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

const int maxn = 30;
big size[maxn][maxn];
char ans[maxn];

void write(big x) {
	char put[130];
	int p = 128;
	put[p] = 0;
	while(x) {
		put[-- p] = '0' + (x % 10);
		x /= 10;
	}
	debug("%s\n", put + p);
}

int main() {
	for(int j = 0; j < 26; j ++)
		size[0][j] = 1;
	for(int i = 1; i <= 26; i ++)
		for(int j = 0; j < 26; j ++) {
			for(int k = 0; k <= j; k ++)
				size[i][j] += size[i - 1][j + (k == j and k < 25)];
		}

	/* for(int i = 1; i <= 26; i ++) */
	/* 	write(size[i][0]); */

	int T = input();
	for(int t = 1; t <= T; t ++) {
		int n = input(), p = 0;
		/* debug("%d\n", t); */
		big k = binput();
		int i = n, j = 0;
		/* if(k == size[i][j]) */
		/* 	return 1; */
		while(i) {
			/* debug("%d %d %s\n", i, j, ans); */
			/* big shit = 0; */
			/* for(int c = 0; c <= j; c ++) { */
			/* 	int toj = j + (c == j and c < 25); */
			/* 	shit += size[i - 1][toj]; */
			/* 	/1* debug("%llu of %llu\n", size[i - 1][toj], shit); *1/ */
			/* } */
			for(int c = 0; c <= j; c ++) {
				int toj = j + (c == j and c < 25);
				/* debug("try %llu %llu\n", k, size[i - 1][toj]); */
				if(k <= size[i - 1][toj]) {
					ans[p ++] = char('A' + c);
					i --;
					j = toj;
					break;
				}
				k -= size[i - 1][toj];
			}
		}
		ans[p] = 0;
		printf("Case #%d: %s\n", t, ans);
	}
}
