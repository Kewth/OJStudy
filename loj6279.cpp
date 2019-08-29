#if 0
2019.08.28

分块 + 懒标记 + 排序 + 二分
#endif
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <climits>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100500, maxb = 333;
int s[maxb][maxb];
int sort[maxb][maxb];
int lazy[maxb];

int b, ans;

void add_one(int l, int r, int c) {
	for(int i = l; i <= r; i ++)
		s[i / b][i % b] += c;
	for(int i = 0; i < b; i ++)
		sort[l / b][i] = (s[l / b][i] += lazy[l / b]);
	lazy[l / b] = 0;
	std::sort(sort[l / b], sort[l / b] + b);
}

void add_all(int l, int r, int c) {
	for(int i = l; i <= r; i ++)
		lazy[i] += c;
}

void query_one(int l, int r, int c) {
	for(int i = l; i <= r; i ++)
		if(s[i / b][i % b] < c - lazy[i / b])
			ans = std::max(ans, s[i / b][i % b] + lazy[i / b]);
}

void query_all(int l, int r, int c) {
	for(int i = l; i <= r; i ++)
		if(sort[i][0] < c - lazy[i])
			ans = std::max(ans,
					*(std::lower_bound(sort[i], sort[i] + b, c - lazy[i]) - 1) + lazy[i]);
}

int main() {
	int n = input(), q = n;

	b = int(sqrt(n) + 1);

	for(int i = 0; i < b; i ++)
		sort[n / b][i] = s[n / b][i] = INT_MAX;
	for(int i = 0; i < n; i ++)
		sort[i / b][i % b] = s[i / b][i % b] = input();
	for(int i = 0; i < b; i ++)
		std::sort(sort[i], sort[i] + b);

	while(q --) {
		int typ = input(), l = input() - 1, r = input() - 1, c = input();

		if(typ == 0) {
			if(l / b == r / b)
				add_one(l, r, c);
			else {
				add_one(l, l / b * b + b - 1, c);
				add_all(l / b + 1, r / b - 1, c);
				add_one(r / b * b, r, c);
			}
		}

		else {
			ans = INT_MIN;
			if(l / b == r / b)
				query_one(l, r, c);
			else {
				query_one(l, l / b * b + b - 1, c);
				query_all(l / b + 1, r / b - 1, c);
				query_one(r / b * b, r, c);
			}
			printf("%d\n", ans == INT_MIN ? -1 : ans);
		}

		/* for(int i = 0; i < n; i ++) */
		/* 	debug(" %d", s[i / b][i % b] + lazy[i / b]); */
		/* debug("\n"); */
		/* for(int i = 0; i < n; i ++) */
		/* 	debug(" %d", sort[i / b][i % b] + lazy[i / b]); */
		/* debug("\n"); */
		/* debug("\n"); */
	}
}
