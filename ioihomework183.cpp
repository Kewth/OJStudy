/*
 * Author: Kewth

 * Date:
  2020.11.18

 * Solution:
  In blog.

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005, maxk = 31;
par a[maxk + 1];
std::vector<int> v[maxn];
std::map<int, int> id;
int ip;

inline void add (int i, int x) {
	int &j = id[x];
	if (!j) j = ++ ip;
	v[j].push_back(i);
}

inline int query (int l, int r, int x) {
	if (!id.count(x) or l > r) return 0;
	auto &V = v[id[x]];
	return int(std::upper_bound(V.begin(), V.end(), r) -
		std::lower_bound(V.begin(), V.end(), l));
}

int main () {
	for (int k = 0; k < maxk; k ++)
		a[k] = par(0, k);
	add(0, 0);
	int n = read;
	ll ans = 0;
	for (int i = 1, p = 0; i <= n; i ++) {
		int x = read;
		p ^= x;
		for (int k = 0; k < maxk; k ++)
			if (!(x >> a[k].second & 1))
				a[k].first = i;
		std::sort(a, a + maxk);
		ans += query(0, a[0].first - 1, p);
		a[maxk].first = i;
		int f = 0;
		for (int k = 0; k < maxk; k ++) {
			f |= 1 << a[k].second;
			ans += query(a[k].first, a[k + 1].first - 1, p ^ f);
		}
		add(i, p);
	}
	printf("%lld\n", ans);
}
