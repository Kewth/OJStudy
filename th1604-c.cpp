#if 0
2019.06.29

朴素 DP 设 f[i][j] 表示第 i 轮在 j 的先手必胜性。
一行一行转移，每一行把连续的 1 看做一个区间，
第 i 行转移时把 i + 1 行的区间左移，右移 i 得到两行新区间 a, b 。
将 a, b 用类似于归并排序中间的方法算交后翻转即可（a, b 都是递增的）。
注意常数，vector 会被卡。
#endif
#include <cstdio>
#include <vector>

inline int input() { int x; scanf("%d", &x); return x; }

struct Win {
	int l, r;
	Win(int l, int r): l(l), r(r) {}
	Win() {}
};

const int maxn = 1000006;
bool ok[maxn];
Win f[maxn], g[maxn], ta[maxn], tb[maxn];
int fp, gp, ap, bp;

int n = input();
inline void try_add(int l, int r, Win *ff, int &pp) {
	if(l <= r)
		ff[++ pp] = Win(std::max(1, l), std::min(r, n));
}

/* inline void print(std::vector<Win> &f) { */
/* 	int last = 0; */
/* 	for(Win w : f) */
/* 		fprintf(stderr, " %d-%d", w.l, w.r); */
/* 	fprintf(stderr, "\n"); */
/* 	for(Win w : f) { */
/* 		for(int i = last + 1; i < w.l; i ++) */
/* 			fprintf(stderr, "0"); */
/* 		for(int i = w.l; i <= w.r; i ++) */
/* 			fprintf(stderr, "1"); */
/* 		last = w.r; */
/* 	} */
/* 	for(int i = last + 1; i <= n; i ++) */
/* 		fprintf(stderr, "0"); */
/* 	fprintf(stderr, "\n"); */
/* } */

int main() {
	for(int i = n - 1; i; i --) {
		ap = bp = 0;
		try_add(1, i, tb, bp);
		for(int j = 1; j <= fp; j ++) {
			try_add(f[j].l - i, f[j].r - i, ta, ap);
			try_add(f[j].l + i, f[j].r + i, tb, bp);
		}
		try_add(n + 1 - i, n, ta, ap);
		gp = 0;
		int p1 = 1, p2 = 1;
		while(p1 <= ap and p2 <= bp) {
			Win *a = ta, *b = tb;
			bool rev = false;
			if(a[p1].l > b[p2].l) {
				std::swap(p1, p2);
				std::swap(a, b);
				rev = true;
			}
			if(a[p1].r < b[p2].l)
				p1 ++;
			else if(b[p2].r <= a[p1].r) {
				try_add(b[p2].l, b[p2].r, g, gp);
				p2 ++;
			} else {
				try_add(b[p2].l, a[p1].r, g, gp);
				p1 ++;
			}
			if(rev) {
				std::swap(p1, p2);
				std::swap(a, b);
			}
		}
		fp = 0;
		int last = 0;
		for(int j = 1; j <= gp; j ++) {
			try_add(last + 1, g[j].l - 1, f, fp);
			last = g[j].r;
		}
		try_add(last + 1, n, f, fp);
		/* print(a); */
		/* print(b); */
		/* print(f); */
		/* fprintf(stderr, "\n"); */
	}
	for(int j = 1; j <= fp; j ++)
		for(int i = f[j].l; i <= f[j].r; i ++)
			ok[i] = true;
	int q = input();
	while(q --)
		printf("%d", ok[input()]);
	puts("");
}
