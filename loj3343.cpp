/*
 * Author: Kewth

 * Date:
  2020.09.07

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
#include <vector>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 2000005;
int ls[maxn], rs[maxn];
struct tree {
	tree *l, *r;
	tree (int u) {
		l = r = nullptr;
		if (ls[u]) l = new tree(ls[u]);
		if (rs[u]) r = new tree(rs[u]);
	}
	inline bool only () { return l == nullptr and r == nullptr; }
};

bool check (std::vector<tree> &ts) {
	if (ts.empty()) return 0;
	for (tree t : ts)
		if (t.only())
			return 1;
	std::vector<tree> l, r, L, R;
	for (tree t : ts) {
		if (t.l) {
			if (t.r == nullptr)
				l.push_back(*t.l);
			else if (t.r -> only())
				L.push_back(*t.l);
		}
		if (t.r) {
			if (t.l == nullptr)
				r.push_back(*t.r);
			else if (t.l -> only())
				R.push_back(*t.r);
		}
	}
	return check(l) and check(r) and check(L) and check(R);
}

int main () {
#ifndef LOCAL
	freopen("surreal.in", "r", stdin);
	freopen("surreal.out", "w", stdout);
#endif

	int T = read;
	while (T --) {
		std::vector<tree> ts;
		int m = read;
		while (m --) {
			for (int i = 1, n = read; i <= n; i ++) read(ls[i], rs[i]);
			ts.push_back(tree(1));
		}
		if (check(ts))
			puts("Almost Complete");
		else
			puts("No");
	}
}
