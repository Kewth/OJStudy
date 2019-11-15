#if 0
2019.06.29

后缀前缀可以分别考虑，就是说可以先按后缀限制删点再按前缀限制删点，
这样得到的方案一定是最优的。
把 C, T 看做 1, -1 ，单独考虑前缀限制，那么答案就是区间内的 |最小前缀和| 。
区间最小前缀和可以用线段树维护，但是问题是需要先删掉不满足后缀限制的点。

如何求出区间内不满足后缀限制的点？朴素想法是从右向左模拟，
但也可以从左向右，用一个栈维护以当前点为右端点的向左时不满足后缀限制的点，
（ update: 应该是单调栈维护当前点为右端点向左单调递减且小于 0 的后缀和）
若当前点为 -1 ，显然不满足限制，压栈，
否则为 1 ，可以抵消一个不满足限制的点，退栈。

离线询问，把询问 [l, r] 挂在 r 点上，
从左向右维护栈，同时维护不在栈内的点的线段树，
那么搜到 i 点时就可以得到挂在 i 点的询问的答案了。
#endif
#include <cstdio>
#include <vector>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef std::pair<int, int> par;
inline int input() { int x; scanf("%d", &x); return x; }

struct Data {
	int minpre, sum;
	Data(): minpre(0), sum(0) {}
};
Data operator + (Data l, Data r) {
	Data res;
	res.minpre = std::min(l.minpre, l.sum + r.minpre);
	res.sum = l.sum + r.sum;
	return res;
}

class Tree {
private:
	int L, R;
	Tree *lt, *rt;
	Data val;
public:
	Data query(int l, int r) {
		if(l > R or r < L) return Data();
		if(l <= L and R <= r) return val;
		return lt -> query(l, r) + rt -> query(l, r);
	}
	void add(int p, int x) {
		if(p < L or p > R) return;
		if(L == R) {
			val.sum += x;
			val.minpre = std::min(val.sum, 0);
			return;
		}
		lt -> add(p, x);
		rt -> add(p, x);
		val = lt -> val + rt -> val;
		/* debug("%d-%d: %d, %d\n", L, R, val.minpre, val.sum); */
	}
	Tree(int l, int r): L(l), R(r), val() {
		if(l == r) {
			lt = rt = nullptr;
			return;
		}
		int mid = (l + r) >> 1;
		lt = new Tree(l, mid);
		rt = new Tree(mid + 1, r);
	}
};

const int maxn = 500005;
int a[maxn];
int ans[maxn];
int st[maxn], st_size;
std::vector<par> qu[maxn];

int main() {
	int n = input();
	for(int i = 0; i < n; i ++) {
		int c = getchar();
		while(c != 'C' and c != 'T') c = getchar();
		a[i] = c == 'C' ? 1 : -1;
	}
	int q = input();
	for(int i = 0; i < q; i ++) {
		int l = input() - 1, r = input() - 1;
		qu[r].push_back(par(l, i));
	}
	Tree T(0, n - 1);
	for(int i = 0; i < n; i ++) {
		if(a[i] == -1)
			st[st_size ++] = i;
		else {
			if(st_size) {
				/* debug("add %d, %d\n", st.top(), -1); */
				T.add(st[-- st_size], -1);
			}
			/* debug("add %d, %d\n", i, 1); */
			T.add(i, 1);
		}
		for(par que : qu[i])
			ans[que.second] = st_size
				- int(std::lower_bound(st, st + st_size, que.first) - st)
				- T.query(que.first, i).minpre;
	}
	for(int i = 0; i < q; i ++)
		printf("%d\n", ans[i]);
}
