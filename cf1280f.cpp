#if 0
2020.03.20

Why cycle?
What does it mean?

把棋盘上看做一个环，棋盘上的数看做一个环排列。
那么假设不能在中间进行上下移动，E 始终只能在环上走，换言之环排列始终不变。
而有了在中点上下移动这个操作，环排列就能够发生改变。
考虑一次中点移动产生的影响，不难发现就是把环排列的某个长为 2k + 1 的子段循环移位。
那么问题转换成对于一个环排列，每次可以选定一个长为 2k + 1 的子段循环移位，
要求最后把环排列变成指定的环排列。
但这还是不够，事实上不难发现，由于 2k + 1 是一个奇数，
通过若干次这样的循环移位可以构造一个更强大的操作：把长为 3 的子段循环移位。
那么问题比较简单了，一个一个数去移动到指定位置，只要当前有不少于 3 个自由的数，
就可以通过循环移位把一个数移动到指定位置。
直到只剩下两个数，如果这两个数恰好到了指定位置，就可行，否则没有合法方案。

不太清楚没有 cycle 这个限制是什么意思，因为这个一直 WA 。
#endif
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () {
		char p[10], *s = p;
		scanf("%s", s);
		if(*s == 'E') return 0;
		return int(strtol(s, &s, 10));
	}
} read;

const int maxn = 100;
int a[maxn];
char ans[100000];
int ap;

inline char *repeat (int k, char c) {
	static char s[maxn];
	std::fill(s, s + k, c);
	return s;
}

void move_L (int l, int r) {
	for(int i = l; i < r; i ++)
		std::swap(a[i], a[i + 1]);
}

void move_R (int l, int r) {
	for(int i = r; i > l; i --)
		std::swap(a[i], a[i - 1]);
}

#ifdef LOCAL
int A[maxn][maxn], px, py;
#define x px
#define y py
void f_u () { std::swap(A[x][y], A[x - 1][y]), -- x; }
void f_d () { std::swap(A[x][y], A[x + 1][y]), ++ x; }
void f_l () { std::swap(A[x][y], A[x][y - 1]), -- y; }
void f_r () { std::swap(A[x][y], A[x][y + 1]), ++ y; }
void f_L (int k) { while (k --) f_l(); }
void f_R (int k) { while (k --) f_r(); }
void f_A (int k) { f_u(), f_R(k), f_R(k), f_d(), f_L(k), f_L(k); }
void f_B (int k) { f_R(k), f_R(k), f_u(), f_L(k), f_L(k), f_d(); }
void f_X (int k) { for (int i = 0; i < k; i ++) f_A(k); }
void f_Y (int k) { for (int i = 0; i < k; i ++) f_B(k); }
void f_C (int k) { f_R(k), f_u(), f_R(k), f_d(), f_L(k), f_L(k); }
void f_D (int k) { f_R(k), f_R(k), f_u(), f_L(k), f_d(), f_L(k); }
void f_E (int k) { f_Y(k), f_C(k), f_X(k); }
void f_F (int k) { f_Y(k), f_D(k), f_X(k); }
void f_M (int k) { f_A(k), f_E(k), f_E(k), f_B(k), f_F(k), f_A(k), f_F(k), f_B(k); }
void f_N (int k) { f_A(k), f_E(k), f_B(k), f_E(k), f_A(k), f_F(k), f_F(k), f_B(k); }
#undef x
#undef y
#endif

int main () {
	int T = read;
	while (T --) {
		int k = read, n = 4 * k + 2;
		for (int i = 1; i <= 2 * k + 1; i ++)
			a[i] = read;
		for (int i = 1; i <= 2 * k + 1; i ++)
			a[n - i + 1] = read;

#ifdef LOCAL
		for (int i = 1; i <= 2 * k + 1; i ++)
			A[1][i] = a[i];
		for (int i = 1; i <= 2 * k + 1; i ++)
			A[2][i] = a[n - i + 1];
#endif

		int pos = 0;
		for (int i = 1; i <= n; i ++)
			if (a[i] == 0)
				pos = i;

		ap = 0;
		for (int i = std::max(pos + 1, 2); i <= 2 * k + 1; i ++)
			ans[++ ap] = 'r';
		for (int i = std::max(pos + 1, 2 * k + 2); i <= 2 * k + 2; i ++)
			ans[++ ap] = 'd';
		for (int i = std::max(pos + 1, 2 * k + 3); i <= n; i ++)
			ans[++ ap] = 'l';

		move_L(pos, n --);

		for (int i = 1; i + 2 <= n; i ++) {
			int x = i <= 2 * k + 1 ? i : n - (i - 2 * k - 1) + 1, p = 0;
			for (int j = 1; j <= n; j ++)
				if (a[j] == x)
					p = j;
			int be = 1;
			while (be < p)
				ans[++ ap] = 'A', ++ be;
			while (be >= 3) {
				ans[++ ap] = 'B', -- be;
				ans[++ ap] = 'B', -- be;
				ans[++ ap] = 'N';
			}
			move_R(be, p);
			if (be == 2) {
				ans[++ ap] = 'B', -- be;
				ans[++ ap] = 'M';
				move_L(1, 3);
			}
			ans[++ ap] = 'A';
			move_L(1, n);
#ifdef LOCAL
			ans[++ ap] = '\n';
			/* for(int j = 1; j <= n; j ++) */
			/* 	debug(" %d", a[j]); */
			/* debug("\n"); */
#endif
		}
		ans[++ ap] = 'A';
		ans[++ ap] = 'A';
		ans[++ ap] = 'R';
		ans[++ ap] = 'R';

		if (a[1] == 2 * k + 3 and a[2] == 2 * k + 2) {
			puts("SURGERY COMPLETE");
			ans[ap + 1] = 0;
			puts(ans + 1);
			printf("L %s\n", repeat(k, 'l'));
			printf("R %s\n", repeat(k, 'r'));
			printf("X %s\n", repeat(k, 'A'));
			printf("Y %s\n", repeat(k, 'B'));
			puts("A uRRdLL"); // 向左循环移位
			puts("B RRuLLd"); // 向右循环移位
			/* puts("C RuLdA"); // 中间向左循环移位 */
			/* puts("D uRdLB"); // 中间向右循环移位 */
			puts("C RuRdLL"); // 中间向左循环移位
			puts("D RRuLdL"); // 中间向右循环移位
			puts("E YCX"); // 前缀 2k + 1 向左循环移位
			puts("F YDX"); // 前缀 2k + 1 向右循环移位
			puts("M AEEBFAFB"); // 前缀 3 向左循环移位
			puts("N AEBEAFFB"); // 前缀 3 向右循环移位
			puts("DONE");

#ifdef LOCAL
			px = (pos - 1) / (2 * k + 1) + 1;
			py = (pos - 1) % (2 * k + 1) + 1;
			if (px == 2) py = 2 * k + 1 - py + 1;
			for (int i = 1; i <= ap; i ++) {
				if (ans[i] == 'r') f_r();
				if (ans[i] == 'l') f_l();
				if (ans[i] == 'd') f_d();
				if (ans[i] == 'u') f_u();
				if (ans[i] == 'A') f_A(k);
				if (ans[i] == 'B') f_B(k);
				if (ans[i] == 'M') f_M(k);
				if (ans[i] == 'N') f_N(k);
				if (ans[i] == 'L') f_L(k);
				if (ans[i] == 'R') f_R(k);
				/* debug("op=%c\n", ans[i]); */
				/* if (ans[i] == '\n') continue; */
				/* for (int j = 1; j <= 2; j ++) { */
				/* 	for (int i = 1; i <= 2 * k + 1; i ++) */
				/* 		debug(" %2d", A[j][i]); */
				/* 	debug("\n"); */
				/* } */
			}
			for (int i = 1; i <= 2 * k + 1; i ++)
				if (A[1][i] != i)
					return 1;
			for (int i = 1; i < 2 * k + 1; i ++)
				if (A[2][i] != 2 * k + 1 + i)
					return 1;
			if (A[2][2 * k +  1] != 0)
				return 1;
#endif
		} else
			puts("SURGERY FAILED");
	}
}
