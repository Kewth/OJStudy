#if 0
2019.12.08

两个人 pk ，之前 pk 树上的深度分别为 x, y，那么 pk 后赢者的 pk 树深度为 max(x, y) + 1 。
在关系树上 dp ，求出每个点的 pk 树深度，这个值和选择子树 pk 的顺序有关，
贪心选择 pk 树深度最小的一个个转移即可。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005;
int head[maxn], nxt[maxn];

int dfs(int u) {
	std::vector<int> ve;
	for(int i = head[u]; i; i = nxt[i])
		ve.push_back(dfs(i));
	std::sort(ve.begin(), ve.end());

	int res = 0;
	for(int x : ve)
		res = std::max(x, res) + 1;
	return res;
}

int main() {
	int n = read;
	for(int i = 2; i <= n; i ++) {
		int f = read;
		nxt[i] = head[f];
		head[f] = i;
	}

	printf("%d\n", dfs(1));
}
