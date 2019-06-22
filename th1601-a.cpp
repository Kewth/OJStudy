#if 0
2019.06.21

答案为 (n - g[i]) 的和，其中 g[i] 为满足 j > i 且 i, j 相连的 j 的数量。
证明：j > i 且与 i 相连的点会成为完全图，从后往前染色即可得此结论。

i, j 相连当且仅当 i, j 在原图相连或原图小于 i 的点中存在联通块 u
满足 u 与 i, j 都在原图相连，可以通过反证得出。
由此可以从左往右扫，用 set 维护 s[i] 表示 g[i] 由哪些点构成，
处理 i 后，把 s[i] 与 s[min(s[i])] 合并，那么 i 点就可以不管了。
#endif
#include <cstdio>
#include <set>

inline int input() { int x; scanf("%d", &x); return x; }

typedef long long lolong;
const int maxn = 300000, mod = 998244353;
std::set<int> s[maxn];

int main() {
	int n = input(), m = input();
	for(int i = 0; i < m; i ++) {
		int x = input() - 1, y = input() - 1;
		if(x > y) std::swap(x, y);
		s[x].insert(y);
	}
	lolong ans = 1;
	for(int i = 0; i < n; i ++) {
		(ans *= (n - int(s[i].size()))) %= mod;
		int j = *s[i].begin();
		if(s[i].size() > s[j].size())
			std::swap(s[i], s[j]);
		for(std::set<int>::iterator it = s[i].begin();
				it != s[i].end(); it ++)
			s[j].insert(*it);
		s[j].erase(j);
	}
	printf("%lld\n", ans);
}
