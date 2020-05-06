#if 0
2020.05.06

  群论基础不行啊。
  问题就是求所有区间的置换构成的群的大小的和，枚举右端点 r ，维护所有 [l, r] 构成的群本质
不同的左端点 l 。根据拉格朗日定理，相邻两个 l 对应的群的大小成倍数关系，那么 l 的数量是
O(logk!) 的。在群内维护组成它的原来的置换（基置换？），这个数量同理也是 O(logk!) 的，每次
在群内加入新置换就从置换的单位元开始 bfs ，每次试乘所有原来的置换即可。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxi = 128;
int id_to_per[maxi][6];
int mul[maxi][maxi];
int code_to_id[54322];

int getcode (int *a) {
	int c = 0;
	for (int i = 1, j = 10000; i <= 5; i ++, j /= 10)
		c += a[i] * j;
	return c;
}

int force_mul (int a, int b) {
	int c = 0;
	for (int i = 1, j = 10000; i <= 5; i ++, j /= 10)
		c += id_to_per[a][id_to_per[b][i]] * j;
	return code_to_id[c];
}

struct group {
	std::vector<int> bas;
	bool ing[maxi];
	int pos, size;
	void build () {
		std::queue<int> q;
		std::fill(ing, ing + maxi, 0);
		q.push(1);
		ing[1] = 1;
		size = 1;
		while (!q.empty()) {
			int P = q.front();
			q.pop();
			for (int Q : bas) {
				int R = mul[P][Q];
				if (!ing[R]) {
					q.push(R);
					ing[R] = 1;
					++ size;
				}
			}
		}
	}
};

bool operator != (group a, group b) {
	for (int i = 1; i <= 120; i ++)
		if (a.ing[i] != b.ing[i])
			return 1;
	return 0;
}

int main () {
	int p[6];
	for (int i = 1; i <= 5; i ++)
		p[i] = i;
	int id = 0;
	do {
		int code = getcode(p);
		code_to_id[code] = ++ id;
		for (int i = 1; i <= 5; i ++)
			id_to_per[id][i] = p[i];
	} while (std::next_permutation(p + 1, p + 6));

	for (int i = 1; i <= id; i ++)
		for (int j = 1; j <= id; j ++)
			mul[i][j] = force_mul(i, j);

	int n = read, m = read;
	ll ans = 0;
	std::vector<group> las, now;

	for (int i = 1; i <= n; i ++) {
		int a[6];
		for (int j = 1; j <= m; j ++) read(a[j]);
		for (int j = m + 1; j <= 5; j ++) a[j] = j;
		int code = getcode(a);
		int P = code_to_id[code];
		group Pg;
		Pg.bas.push_back(P);
		Pg.build();
		Pg.pos = i;
		las.push_back(Pg);
		now.clear();
		for (group g : las) {
			if (!g.ing[P]) {
				g.bas.push_back(P);
				g.build();
			}
			if (now.empty() or g != now.back())
				now.push_back(g);
		}
		int ls = 0;
		for (group g : now) {
			/* debug("%d -> %d : %d\n", g.pos, i, g.size); */
			ans += (g.size - ls) * (i - g.pos + 1);
			ls = g.size;
		}
		las = now;
	}

	printf("%lld\n", ans);
}
