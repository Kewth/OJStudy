/*
 * Author: Kewth

 * Date:
  2020.10.14

 * Solution:
  容易发现可以只走三角形端点，把三角形端点和起点终点拿出来建图然后把点按高度排序，用
个并查集维护即可。

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	/* inline operator ll () { ll x; return scanf("%lld", &x), x; } */
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

/* const int maxn = 100005; */
const int maxn = 2020;
struct point {
	int x, y, z, id;
	inline ll hash () {
		return x * 1000002000001ll + y * 1000001ll + z;
	}
} p1[maxn], p2[maxn], p3[maxn];
bool operator < (point a, point b) { return a.hash() < b.hash(); }

struct vector {
	int x, y;
};
vector operator - (point a, point b) { return {a.x - b.x, a.y - b.y }; }
ll cross (vector a, vector b) { return 1ll * a.x * b.y - 1ll * b.x * a.y; }

std::map<point, int> id;
point iid[maxn * 3];
int ip;
std::vector<int> G[maxn * 3];

inline void init (point &p) {
	read(p.x, p.y, p.z);
	if (!id.count(p)) id[p] = ++ ip;
	p.id = id[p];
	iid[p.id] = p;
}

void add (point u, point v) {
	G[u.id].push_back(v.id);
	G[v.id].push_back(u.id);
}

void extra_link (point p, int n) {
	if (!G[p.id].empty()) return;
	for (int i = 1; i <= n; i ++) {
		ll c1 = cross(p - p1[i], p2[i] - p1[i]);
		ll c2 = cross(p - p2[i], p3[i] - p2[i]);
		ll c3 = cross(p - p3[i], p1[i] - p3[i]);
		if ((c1 >= 0 and c2 >= 0 and c3 >= 0) or
				(c1 <= 0 and c2 <= 0 and c3 <= 0)) {
			add(p, p1[i]);
			add(p, p2[i]);
			add(p, p3[i]);
		}
	}
}

int per[maxn * 3], fa[maxn * 3], ok[maxn * 3];
int find (int x) {
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
bool cmp (int u, int v) {
	return iid[u].z == iid[v].z ? u < v : iid[u].z < iid[v].z;
}

int ans[maxn * 3], ap;
bool dfs (int u, int t) {
	if (!ok[u]) debug("ERROR\n");
	ok[u] = 0;
	if (u == t) return ans[++ ap] = t, 1;
	for (int v : G[u])
		if (ok[v] and dfs(v, t))
			return ans[++ ap] = u, 1;
	return 0;
}

int main () {
	/* freopen("hiking.in", "r", stdin); */
	/* freopen("hiking.out", "w", stdout); */

	int n = read;
	for (int i = 1; i <= n; i ++) {
		init(p1[i]);
		init(p2[i]);
		init(p3[i]);
		add(p1[i], p2[i]);
		add(p1[i], p3[i]);
		add(p2[i], p3[i]);
	}

	point s, t;
	init(s);
	init(t);
	extra_link(s, n);
	extra_link(t, n);

	for (int u = 1; u <= ip; u ++)
		per[u] = u, fa[u] = u;
	std::sort(per + 1, per + ip + 1, cmp);
	int lim = 0;
	while (find(s.id) != find(t.id)) {
		int u = per[++ lim];
		ok[u] = 1;
		for (int v : G[u])
			if (cmp(v, u))
				fa[find(v)] = u;
	}

	dfs(s.id, t.id);
	printf("%d\n", ap);
	for (int i = ap; i; i --)
		printf("%d %d %d\n", iid[ans[i]].x, iid[ans[i]].y, iid[ans[i]].z);
}
