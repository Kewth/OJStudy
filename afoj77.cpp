#if 0
2019.08.11

贪心，每个点在可以加的油中按费用选最小的加到可以走为止，
到下个点的时候把当前剩下的可以加的油转移过去即可。
#endif
#include <cstdio>
#include <queue>
#define debug(...) // fprintf(stderr, __VA_ARGS__)

typedef std::pair<int, int> Par;
typedef long long lolong;
inline int input() {
	int x = 0, c = getchar();
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

struct Queue {
	std::priority_queue<Par> q, e;
	inline void push(Par p) { q.push(p); }
	inline void erase(Par p) { e.push(p); }
	inline Par top() {
		while(not e.empty() and e.top() == q.top()) {
			q.pop();
			e.pop();
		}
		return q.top();
	}
};

int main() {
	int n = input(), max = input();
	lolong ans = 0;
	Queue q1, q2;
	q1.push(Par(- 1000000000, max));
	q2.push(Par(1000000000, max));
	for(int i = 1, ld = max; i <= n; i ++) {
		int	d = input(), p = input();
		debug("add %d, %d\n", p, max);
		q1.push(Par(- p, max));
		q2.push(Par(p, max));
		int x = 0, last;
		while(x < ld) {
			last = q2.top().first;
			int y = q2.top().second;
			x += y;
			debug("erase %d, %d\n", last, y);
			q1.erase(Par(- last, y));
			q2.erase(Par(last, y));
		}
		if(x > ld) {
			debug("add %d, %d\n", last, x - ld);
			q1.push(Par(- last, x - ld));
			q2.push(Par(last, x - ld));
		}
		x = 0;
		while(x < d) {
			last = - q1.top().first;
			int y = q1.top().second;
			x += y;
			ans += 1ll * last * y;
			debug("use %d, %d\n", last, y);
			q1.erase(Par(- last, y));
			q2.erase(Par(last, y));
		}
		if(x > d) {
			debug("nouse %d, %d\n", last, x - d);
			ans -= 1ll * last * (x - d);
			q1.push(Par(- last, x - d));
			q2.push(Par(last, x - d));
		}
		debug("%lld\n", ans);
		ld = max - d;
	}
	printf("%lld\n", ans);
}

