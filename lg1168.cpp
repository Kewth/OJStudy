#if 0
2019.09.24

感觉这个挺神的，竟然是个绿题，洛谷评级果然只看码量。
我管他叫对顶堆，维护一个大根堆一个小根堆，满足大根堆的值都比小根堆小。
那么查中位数的时候就相互传 top 直到两边 size 相差 1 即可。
#endif
#include <cstdio>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005;

int main() {
	std::priority_queue<int> q1, q2;
	int n = input();

	for(int i = 1; i <= n; i ++) {
		int x = input();
		if(q1.empty() or x > q1.top())
			q2.push(- x);
		else
			q1.push(x);

		if(i & 1) {
			while(q1.size() > q2.size() + 1) {
				q2.push(- q1.top());
				q1.pop();
			}

			while(q2.size() > q1.size() + 1) {
				q1.push(- q2.top());
				q2.pop();
			}

			if(q1.size() > q2.size())
				printf("%d\n", q1.top());
			else
				printf("%d\n", - q2.top());
		}
	}
}
