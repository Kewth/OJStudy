#if 0
2019.08.28

分块 + 莫队 + map + set
然而会 T 。
离散化，代替掉 map 。
分块 + 莫队 + set
然而会 T 。

发现 set 难以替换的原因在于处理删点的时候，如果答案更改必须求一个最小值，
这样的话必须把可能的答案都存起来。
避开删点，利用到莫队的一个小 trick ，每次左端点都从块右边往左移在移回来，
这样可以把删除操作转成撤销操作（甚至可以不用更新答案），就不需要 set 了。

分块 + 莫队
#endif
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#define debug(...) // fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

struct Query {
	int l, r, id;
};
const int maxn = 100505, maxb = 333;
int a[maxn];
std::vector<Query> qu[maxb];
int tmp[maxn];
int anslist[maxn];
int map[maxn];

int b, ans;

inline int cmp(Query x, Query y) {
	return x.r < y.r;
}

void add(int p) {
	int x = a[p];
	map[x] ++;
	if(map[x] > map[ans] or (map[x] == map[ans] and x < ans))
		ans = x;
	debug("add %d -> %d(%d)\n", p, ans, tmp[ans]);
}

inline void undo(int p) {
	map[a[p]] --;
	debug("undo %d\n", p);
}

int main() {
	int n = input();

	b = int(sqrt(n + 1) + 1);

	for(int i = 1; i <= n; i ++)
		tmp[i] = a[i] = input();

	for(int i = 1; i <= n; i ++) {
		Query q;
		q.l = input();
		q.r = input();
		q.id = i;
		qu[q.l / b].push_back(q);
	}

	std::sort(tmp + 1, tmp + n + 1);

	for(int i = 1; i <= n; i ++)
		a[i] = int(std::lower_bound(tmp + 1, tmp + n + 1, a[i]) - tmp);

	for(int i = 0; i < b; i ++) {
		std::sort(qu[i].begin(), qu[i].end(), cmp);

		int last = i * b + b - 1;
		for(size_t j = 0; j < qu[i].size(); j ++) {
			int l = qu[i][j].l, r = qu[i][j].r;

			debug("%d %d\n", l, r);

			if(r / b == i) {
				for(int p = l; p <= r; p ++)
					add(p);
				for(int p = l; p <= r; p ++)
					undo(p);
				anslist[qu[i][j].id] = tmp[ans];
				ans = 0;
			}

			else {
				while(last < r)
					add(++ last);
				int bak = ans;
				debug("set bak = %d\n", tmp[bak]);
				for(int p = l; p / b == l / b; p ++)
					add(p);
				for(int p = l; p / b == l / b; p ++)
					undo(p);
				anslist[qu[i][j].id] = tmp[ans];
				ans = bak;
			}
		}

		while(last / b != i)
			undo(last --);
		ans = 0;
	}

	for(int i = 1; i <= n; i ++)
		printf("%d\n", anslist[i]);
}
