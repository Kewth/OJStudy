#if 0
2019.06.26

要求最小 i 使删掉权值为 i 的边后图仍联通。
删边不好处理，转换为加边，用并查集维护连通性，维护一个联通块数量。
把取值区间分治，分治到 [l, r] 时需保证除 [l, r] 外的边都已经被加上。
分治左区间时把右区间的边加上，
分治右区间时把左区间加的边回退，再加右区间的边。
分治完后把右区间加的边回退。
这样可以满足上述要求且每条边只被使用常数次。
#endif
#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

struct Edge {
	int u, v;
};

const int maxn = 1000005, maxv = 100005;
std::vector<Edge> ve[maxv];
int fa[maxn], deep[maxn], block;

inline int find(int x) {
	if(fa[x] == x) return x;
	return find(fa[x]);
}

inline void merge(int x, int y) {
	if(x == y) return;
	/* debug("merge %d %d\n", x, y); */
	block --;
	if(deep[x] < deep[y])
		fa[x] = y;
	else if(deep[x] > deep[y])
		fa[y] = x;
	else {
		fa[x] = y;
		deep[y] ++;
	}
}

inline void undo(int x, int y) {
	if(x == y) return;
	/* debug("undo %d %d\n", x, y); */
	if(fa[y] == y) std::swap(x, y);
	fa[y] = y;
	block ++;
	// TODO : deep[x] = ?
}

int ans(int l, int r) {
	/* debug("%d-%d::\n", l, r); */
	/* for(int u = 1; u <= 10; u ++) */
	/* 	debug(" %d", find(u)); */
	/* debug(" b%d\n", block); */
	if(l == r)
		return block == 1 ? l : -1;
	int mid = (l + r) >> 1;
	std::stack<Edge> st;
	auto merge_it = [&](int l, int r) {
		for(int i = l; i <= r; i ++)
			for(Edge e : ve[i]) {
				Edge el;
				el.u = find(e.u);
				el.v = find(e.v);
				merge(el.u, el.v);
				st.push(el);
			}
	};
	auto undo_it = [&]() {
		while(not st.empty()) {
			undo(st.top().u, st.top().v);
			st.pop();
		}
	};
	merge_it(mid + 1, r);
	int res = ans(l, mid);
	undo_it();
	/* debug("%d-%d::again\n", l, r); */
	/* for(int u = 1; u <= 10; u ++) */
	/* 	debug(" %d", find(u)); */
	/* debug(" b%d\n", block); */
	if(res == -1) {
		/* block = tmp; */
		merge_it(l, mid);
		res = ans(mid + 1, r);
		undo_it();
	}
	/* debug("%d-%d : %d\n", l, r, res); */
	return res;
}

int main() {
	int n = input(), m = input();
	for(int i = 0; i < m; i ++) {
		Edge e;
		e.u = input();
		e.v = input();
		ve[input()].push_back(e);
	}
	for(int u = 1; u <= n; u ++)
		fa[u] = u;
	block = n;
	printf("%d\n", std::max(ans(0, maxv - 1), 0));
}
