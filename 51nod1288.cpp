#if 0
2019.11.05

带悔贪心，用 set 维护当前可以后悔选择的加油站。
#endif
#include <cstdio>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> Par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 100005;
std::set<Par> set;

int main() {
	int n = read, max = read;
	ll ans = 0;
	int tot = 0;

	for(int i = 1; i <= n; i ++) {
		int d = read, p = read;
		if(d > max) return puts("-1"), 0;
		set.insert(Par(p, max));
		tot += max;

		while(tot > max) {
			std::set<Par>::iterator it = -- set.end();
			if(tot - it -> second >= max) {
				tot -= it -> second;
				set.erase(it);
			}
			else {
				Par insert = Par(it -> first, it -> second - (tot - max));
				tot = max;
				set.erase(it);
				set.insert(insert);
			}
		}

		tot -= d;
		while(d) {
			std::set<Par>::iterator it = set.begin();
			if(it -> second < d) {
				ans += 1ll * it -> first * it -> second;
				d -= it -> second;
				set.erase(it);
			}
			else {
				Par insert = Par(it -> first, it -> second - d);
				ans += 1ll * it -> first * d;
				d = 0;
				set.erase(it);
				set.insert(insert);
			}
		}

		/* debug("%lld\n", ans); */
	}

	printf("%lld\n", ans);
}
