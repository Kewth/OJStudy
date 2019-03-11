#if 0
2019.03.10

搜线性基跳到了这题，看完题目 WTF 线性基怎么支持删除？
于是学了一波线段树分治。

有了线段树分治的话，这题就比较可做了，
维护思路类似于最大 xor 路径那题。

细节方面注意 q = 0 的情况，以及为了因对洛谷的垃圾数据要开 2 倍数组
#endif
#ifdef debugging
# define clog(x) std::clog << x << std::endl
# define clo(c) std::clog << x
#else
# define clog(x)
# define clo(c)
/* # define NDEBUG */
#endif
#include <bits/stdc++.h>

// TODO: LOJ AC, Luogu RE...

// 洛谷的垃圾数据不符合要求，数组按题目开会 RE ，故全开大一倍
const int maxn = 2005, maxk = 1005, maxlog = 20, maxq = 2005;
typedef std::bitset<2048> bignum;
bignum ans[maxq];
bignum to_root[maxn];
int head[maxn], to[maxn << 1], nxt[maxn << 1], wp;
bignum edge_val[maxn << 1];
bool vis[maxn];
int last[maxq]; // 第 k 条边被加入的时间
/* bignum new_edge_val[maxq]; */
bignum mon[maxq]; // 第 k 条边的权值
int nodex[maxq], nodey[maxq]; // 第 k 条边的端点

// (xian) (xing) (ji) {{{
class JI {
private:
	bignum Ji[maxk];
public:
	void add(bignum &x) {
		for(unsigned k=maxk-1; k<maxk; k--)
			if(x[k]) {
				if(Ji[k] == 0) {
					Ji[k] = x;
					break;
				} else
					x ^= Ji[k];
			}
	}
	void max(bignum &now) {
		assert(now == 0);
		clog("Geting max");
		/* for(unsigned k=maxk-1; k<maxk; k--) */
		/* 	if(Ji[k] != 0) */
		/* 		std::clog << Ji[k].to_ulong() << std::endl; */
		for(unsigned k=maxk-1; k<maxk; k--)
			if(not now[k])
				now ^= Ji[k];
		clog("Got " << now.to_ulong());
	}
	void operator = (JI &an) {
		for(unsigned k=maxk-1; k<maxk; k--)
			Ji[k] = an.Ji[k];
	}
};
JI ji_list[maxlog];
// }}}

// Line Segment Tree {{{
class Tree {
private:
	std::vector<bignum> tags;
	int L, R;
	Tree *lt, *rt;
public:
	void add(int, int, bignum &);
	void fuckit(int);
	Tree(int, int);
};

void Tree::add(int l, int r, bignum &x) {
	if(r < L or l > R)
		return;
	if(l <= L and R <= r)
		tags.push_back(x);
	else {
		assert(lt and rt);
		lt -> add(l, r, x);
		rt -> add(l, r, x);
	}
}

void Tree::fuckit(int p) {
	for(auto &x : tags) {
		/* std::clog << "Add " << x.to_ulong() */
		/* 	<< " into ji " << p << std::endl; */
		ji_list[p].add(x);
	}
	tags.clear();
	{ std::vector<bignum>().swap(tags); } // 释放内存
	if(L == R)
		ji_list[p].max(ans[L]);
	else {
		assert(lt and rt);
		ji_list[p + 1] = ji_list[p];
		lt -> fuckit(p + 1);
		ji_list[p + 1] = ji_list[p];
		rt -> fuckit(p + 1);
	}
}

Tree::Tree(int l, int r): tags(), L(l), R(r) {
	if(l == r) {
		lt = rt = nullptr;
	} else {
		int mid = (l + r) >> 1;
		lt = new Tree(l, mid);
		rt = new Tree(mid + 1, r);
	}
}
// }}}

void dfs(int u) {
	assert(not vis[u]);
	vis[u] = true;
	for(int i=head[u]; i; i=nxt[i]) {
		int v = to[i];
		/* std::clog << "dfs " << u << "->" << v << std::endl; */
		bignum to_add = to_root[u] ^ edge_val[i];
		if(vis[v]) {
			to_add ^= to_root[v];
			/* std::clog << "Add " << to_add.to_ulong() */
			/* 	<< " into ji 0" << std::endl; */
			ji_list[0].add(to_add);
		} else {
			to_root[v] = to_add;
			dfs(v);
		}
	}
}

int main() {
	int n, m, q;
	std::cin >> n >> m >> q;
	for(int i=1; i<=m; i++) {
		int x, y;
		bignum v;
		std::cin >> x >> y >> v;
		assert(1 <= x and x <= n);
		assert(1 <= y and y <= n);
		nxt[++ wp] = head[x];
		head[x] = wp;
		to[wp] = y;
		edge_val[wp] = v;
		nxt[++ wp] = head[y];
		head[y] = wp;
		to[wp] = x;
		edge_val[wp] = v;
	}
	dfs(1);
	ji_list[0].max(ans[0]);
	if(q) { // 日，这个要特判一下。。
		Tree T(1, q);
		int addp = 0;
		for(int i=1; i<=q; i++) {
			std::string type;
			std::cin >> type;
			if(type == "Add") {
				++ addp;
				int &x = nodex[addp], &y = nodey[addp];
				bignum &v = mon[addp];
				std::cin >> x >> y >> v;
				v ^= to_root[x];
				v ^= to_root[y];
				last[addp] = i;
			} else if(type == "Cancel") {
				int k;
				std::cin >> k;
				clog(last[k] << " to " << i - 1
					<< " : " << mon[k].to_ulong());
				T.add(last[k], i - 1, mon[k]);
				mon[k] = 0;
			} else if(type == "Change") {
				int k;
				bignum v;
				std::cin >> k >> v;
				clog(last[k] << " to " << i - 1
					<< " : " << mon[k].to_ulong());
				T.add(last[k], i - 1, mon[k]);
				int &x = nodex[k], y = nodey[k];
				mon[k] = v ^ to_root[x] ^ to_root[y];
				last[k] = i;
			} else
				assert(type == "WTF?");
		}
		for(int i=1; i<=addp; i++)
			if(mon[i] != 0) {
				clog(last[i] << " to " << q
					<< " : " << mon[i].to_ulong());
				T.add(last[i], q, mon[i]);
			}
		T.fuckit(0);
	}
	for(int i=0; i<=q; i++) {
		unsigned begin = 0;
		for(unsigned k=maxk-1; k<maxk; k--)
			if(ans[i][k]) {
				begin = k;
				break;
			}
		for(unsigned k=begin; k<maxk; k--)
			std::cout << ans[i][k];
		std::cout << std::endl;
	}
}
