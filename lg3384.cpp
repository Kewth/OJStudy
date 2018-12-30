// include files {{{1
#include <bits/stdc++.h>

// function to speed up input {{{1
long long input() {
	int ch = getchar();
	long long res = 0;
	while(ch < '0' or ch > '9') ch = getchar();
	while(ch >= '0' and ch <= '9') res = res * 10 + ch - '0', ch = getchar();
	return res;
}

// Node {{{1
class node {
public:
	int newid;
	int val;
	int size;
	int deep;
	node *top;
	node *son;
	node *fa;
	std::vector<node*> link;
	node() : size(1), deep(0), top(this) {}
};

// Segment Tree {{{1
class Tree {
private:
	int L, R;
	Tree *lt, *rt;
	long long sum, mod, mark;
	void upd() {
		/* sum = lt->sum + lt->mark * (lt->R - lt->L + 1); */
		/* sum += rt->sum + rt->mark * (rt->R - rt->L + 1); */
		sum = lt->sum + rt->sum + mark * (R - L + 1);
		sum %= mod;
	}
public:
	void add(int l, int r, int v) {
		if(r < L or l > R) return ;
		/* std::cerr << "Add In " << L << "," << R << std::endl; */
		if(l <= L and R <= r) {
			(mark += v) %= mod;
			(sum += v * (R - L + 1)) %= mod;
		} else {
			lt->add(l, r, v);
			rt->add(l, r, v);
			upd();
		}
	}
	long long query(int l, int r) {
		if(r < L or l > R) return 0;
		if(l <= L and R <= r)
			return sum;
		long long res = mark * (std::min(R, r) - std::max(L, l) + 1) % mod;
		return (res + lt->query(l, r) + rt->query(l, r)) % mod;
	}
	Tree(int l, int r, int *v, int m) : L(l), R(r), mod(m), mark(0) {
		if(l == r) {
			sum = v[l];
			lt = rt = nullptr;
		} else {
			int mid = (l + r) >> 1;
			lt = new Tree(l, mid, v, m);
			rt = new Tree(mid+1, r, v, m);
			upd();
		}
	}
};

// Global defition {{{1
const int maxn = 100050;
node d[maxn];
int num[maxn];

// add edge {{{1
inline void add(int idx, int idy) {
	d[idx].link.push_back(d + idy);
	d[idy].link.push_back(d + idx);
}

// first dfs to init {{{1
void dfs1(node *u) {
	for(node *v : u->link)
		if(v != u->fa) {
			v->deep = u->deep + 1;
			v->fa = u;
			dfs1(v);
			u->size += v->size;
			if(not u->son or v->size > u->son->size)
				u->son = v;
		}
}

// second dfs to init {{{1
void dfs2(node *u) {
	static int ID = 0;
	u->newid = ++ ID;
	num[u->newid] = u->val;
	if(u->son) {
		u->son->top = u->top;
		dfs2(u->son);
	}
	for(node *v : u->link)
		if(v != u->fa and v != u->son) {
			dfs2(v);
		}
}

// clac for line {{{1
void line(node *a, node *b, std::function<void(int, int)> todo) {
	if(a->top == b->top) {
		if(a->deep > b->deep)
			std::swap(a, b);
		todo(a->newid, b->newid);
	} else if(a->top->deep > b->top->deep) {
		todo(a->top->newid, a->newid);
		line(a->top->fa, b, todo);
	} else {
		todo(b->top->newid, b->newid);
		line(a, b->top->fa, todo);
	}
}

// clac for tree {{{1
void tree(node *u, std::function<void(int, int)> todo) {
	todo(u->newid, u->newid + u->size - 1);
}

// Main function {{{1
int main() {
	/* std::ios::sync_with_stdio(false); */
	int n, q, rt, mod;
	std::cin >> n >> q >> rt >> mod;
	for(int i=1;i<=n;i++)
		std::cin >> d[i].val;
	for(int i=1;i<n;i++)
		add(input(), input());
	dfs1(&d[rt]);
	dfs2(&d[rt]);
	Tree T(1, n, num, mod);
	/* for(int i=1;i<=n;i++) */
		/* std::cerr << num[i] << ", "; */
	/* std::cerr << std::endl; */
	while(q --) {
		int typ = input(), x, y, z, RES;
		switch(typ) {
			case 1:
				std::cin >> x >> y >> z;
				line(&d[x], &d[y], [&](int l, int r) -> void {
						T.add(l, r, z);
					});
				break;
			case 2:
				std::cin >> x >> y;
				RES = 0;
				line(&d[x], &d[y], [&](int l, int r) -> void {
						(RES += T.query(l, r)) %= mod;
					});
				std::cout << RES << std::endl;
				break;
			case 3:
				std::cin >> x >> z;
				tree(&d[x], [&](int l, int r) -> void {
						/* std::cerr << l << ' ' << r << ' ' << z << std::endl; */
						T.add(l, r, z);
					});
				break;
			case 4:
				std::cin >> x;
				RES = 0;
				tree(&d[x], [&](int l, int r) -> void {
						/* std::cerr << l << ' ' << r << std::endl; */
						(RES += T.query(l, r)) %= mod;
					});
				std::cout << RES << std::endl;
				break;
		}
	}
}

// }}}1
