#if 0
2019.09.02

将地板分成四个小正方形，公主所在的正方形扔掉成了一个子问题拿下去递归，
剩下三个可以用一个地毯连起来，选上那个地毯，相当于站了三个公主，分别形成三个子问题。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

void solve(int x1, int y1, int len, int x, int y) {
	if(len == 1)
		return;

	/* debug("%d %d %d %d %d\n", x1, y1, len, x, y); */

	int mid = len >> 1;
	int id = 0;

	if(x < x1 + mid and y < y1 + mid) {
		id = 1;
		printf("%d %d", x1 + mid, y1 + mid);
	} else if(x < x1 + mid) {
		id = 2;
		printf("%d %d", x1 + mid, y1 + mid - 1);
	} else if(y < y1 + mid) {
		id = 3;
		printf("%d %d", x1 + mid - 1, y1 + mid);
	} else {
		id = 4;
		printf("%d %d", x1 + mid - 1, y1 + mid - 1);
	}

	printf(" %d\n", id);

	if(id == 2)
		solve(x1, y1 + mid, mid, x, y);
	else
		solve(x1, y1 + mid, mid, x1 + mid - 1, y1 + mid);

	if(id == 3)
		solve(x1 + mid, y1, mid, x, y);
	else
		solve(x1 + mid, y1, mid, x1 + mid, y1 + mid - 1);

	if(id == 1)
		solve(x1, y1, mid, x, y);
	else
		solve(x1, y1, mid, x1 + mid - 1, y1 + mid - 1);

	if(id == 4)
		solve(x1 + mid, y1 + mid, mid, x, y);
	else
		solve(x1 + mid, y1 + mid, mid, x1 + mid, y1 + mid);
}

int main() {
	int n = 1 << input();
	int x = input(), y = input();
	solve(1, 1, n, x, y);
}
