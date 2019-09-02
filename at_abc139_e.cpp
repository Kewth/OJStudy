#if 0
2019.09.01

直接模拟，每个人开 set 记录有谁正等着和他干。
每次如果一个人最先打的在 set 里头，就干，否则加到那个人的 set 里头。
#endif
#include <cstdio>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1010;
int a[maxn][maxn];
int ap[maxn];
int last[maxn];
std::set<int> wait[maxn];

int n;
void update(int x) {
	if(ap[x] == n)
		return;

	int y = a[x][ap[x]];

	if(wait[x].count(y)) {
		wait[x].erase(y);

		int now = std::max(last[x], last[y]) + 1;
		last[x] = last[y] = now;

		ap[x] ++;
		ap[y] ++;

		update(x);
		update(y);
	}

	else {
		wait[y].insert(x);
	}
}

int main() {
	n = input();

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j < n; j ++)
			a[i][j] = input();

	for(int i = 1; i <= n; i ++)
		ap[i] = 1;

	for(int i = 1; i <= n; i ++)
		update(i);

	bool empty = true;
	for(int i = 1; i <= n; i ++)
		if(not wait[i].empty())
			empty = false;

	if(empty) {
		int ans = 0;
		for(int i = 1; i <= n; i ++)
			ans = std::max(ans, last[i]);
		printf("%d\n", ans);
	}

	else
		puts("-1");
}
