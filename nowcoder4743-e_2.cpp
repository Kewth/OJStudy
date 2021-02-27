/*
 * Author: Kewth

 * Date:
  2021.02.14

 * Solution:

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

ll cost (int x, int m) {
	int h = x / m, z = x % m;
	return 1ll * z * (h + 1) * (h + 1) + 1ll * (m - z) * h * h;
}

struct Stone {
	int x, m;
	ll nxt;
	Stone (int x): x(x), m(1) {
		nxt = cost(x, m) - cost(x, m + 1);
	}
	void GetNxt () {
		m += 1;
		nxt = cost(x, m) - cost(x, m + 1);
	}
};
inline bool operator < (Stone a, Stone b) { return a.nxt < b.nxt; }


const int maxn = 405;
int a[maxn];

ll solve (int n, int m) {
	ll res = 0;
	std::priority_queue<Stone> q;
	for (int i = 1; i <= n; i ++) {
		res += cost(a[i], 1);
		q.push(Stone(a[i]));
		-- m;
	}
	while (m --) {
		Stone s = q.top();
		q.pop();
		res -= s.nxt;
		s.GetNxt();
		q.push(s);
	}
	return res;
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= n; i ++) read(a[i]);
	debug("%lld\n", solve(n, m));
	int q = read;
	while (q --) {
		int i = read;
		read(a[i]);
		printf("%lld\n", solve(n, m));
	}
}
