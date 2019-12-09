#if 0
2019.12.08

不难发现每个点的权值就是有连边关系的点的 mex 。
如果没有环，根据拓扑序一定可以得出一个合法的 mex 。
考虑有环，先将环外的点 mex 求出来并初步算出环上点的 mex ，
考虑环上的点的 mex ，当且仅当环上有奇数个点且当前 mex 全部相同时无解。
#endif
#include <cstdio>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 200005;
int p[maxn];
int deg[maxn];
int mex[maxn];
int stack[maxn], sp;
std::set<int> set[maxn];

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		++ deg[p[i] = read];

	for(int i = 1; i <= n; i ++)
		if(!deg[i])
			stack[++ sp] = i;

	while(sp) {
		int x = stack[sp --];

		while(set[x].count(mex[x]))
			++ mex[x];

		set[p[x]].insert(mex[x]);

		-- deg[p[x]];
		if(!deg[p[x]])
			stack[++ sp] = p[x];
	}

	int tot = 0;
	for(int i = 1; i <= n; i ++)
		if(deg[i]) {
			while(set[i].count(mex[i]))
				++ mex[i];
			/* debug("%d : %d\n", i, mex[i]); */
			++ tot;
			set[0].insert(mex[i]);
		}

	if((tot & 1) and set[0].size() == 1) puts("IMPOSSIBLE");
	else puts("POSSIBLE");
}
