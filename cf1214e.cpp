#if 0
2019.09.04

把 di 最大的点对 (x, y) 拿出来，弄出一条链，考虑在这条链上挂上其他点对。

设 a[i] 表示这条主链上的第 i 个点。
对于第一个未确定的 a[k] ，选上当前 di 最大的 (x, y) ，
直接令 a[k] = x ，在 a[k + di - 1] 下面挂上 y 即可。
特别的是如果挂在了主链的末端下面，需要延长主链，
由于选取的 di 不增，每次 y 最远也就挂在主链一端，不会有没地方挂的情况。

由于 di <= n ，主链的 a 一定可以全部确定。
接下来对于剩下的每个 di, (x, y) ，x 挂 a[1] y 挂 a[di - 1] 即可，特判 di = 1 的点对。
#endif
#include <cstdio>
#include <stack>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 200005;
std::stack<int> D[maxn << 1];
int a[maxn << 1];
std::stack<int> A[maxn << 1];

int main() {
	int n = input();

	int max = 0;

	for(int i = 1; i <= n; i ++) {
		int d = input();
		D[d].push(i);
		max = std::max(max, d);
	}

	a[1] = D[max].top() * 2;
	a[max + 1] = D[max].top() * 2 - 1;
	D[max].pop();

	int now = 2;

	for(int d = max; d; d --)
		while(not D[d].empty()) {
			int x = D[d].top();
			D[d].pop();

			if(now <= max) {
				a[now] = x * 2;
				A[now + d].push(x * 2 - 1);
				now ++;
			}

			else {
				if(d == 1) {
					D[d].push(x);
					break;
				}
				A[0].push(x * 2);
				A[d].push(x * 2 - 1);
			}
		}

	while(not D[1].empty()) {
		int x = D[1].top();
		D[1].pop();
		printf("%d %d\n", a[1], x * 2);
		printf("%d %d\n", x * 2, x * 2 - 1);
	}

	int en = max + 1;
	while(not A[en + 1].empty()) {
		++ en;
		a[en] = A[en].top();
		A[en].pop();
	}

	for(int i = 1; i < en; i ++)
		printf("%d %d\n", a[i], a[i + 1]);

	for(int i = 2; i <= en; i ++)
		while(not A[i].empty()) {
			printf("%d %d\n", a[i - 1], A[i].top());
			A[i].pop();
		}

	while(not A[0].empty()) {
		printf("%d %d\n", a[1], A[0].top());
		A[0].pop();
	}
}
