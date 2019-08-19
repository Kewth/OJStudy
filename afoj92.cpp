#if 0
2019.08.19

将点和区间分别排序，用扫描线 + 优先队列维护贪心。
具体地，扫描线扫点，优先队列里维护经过扫描线的可选区间，
由于扫描线左边的点已经选完，那么优先队列的区间只需关注右端点，
那么当前点最好的选择自然是选右端点最小的区间。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef std::pair<int, int> Par;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 200005;
Par L[maxn];
int X[maxn];

int main() {
	int n = input(), m = input();
	for(int i = 1; i <= n; i ++) {
		L[i].first = input();
		L[i].second = input();
	}
	for(int i = 1; i <= m; i ++)
		X[i] = input();
	std::sort(L + 1, L + n + 1);
	std::sort(X + 1, X + m + 1);
	std::priority_queue<int> q;
	int ans = 0;
	for(int i = 1, j = 1; i <= m; i ++) {
		while(j <= n and L[j].first <= X[i])
			q.push(- L[j ++].second);
		while(not q.empty() and - q.top() < X[i])
			q.pop();
		if(not q.empty()) {
			ans ++;
			q.pop();
		}
	}
	printf("%d\n", ans);
}
