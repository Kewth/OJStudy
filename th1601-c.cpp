#if 0
2019.06.21

数据结构题，树状数组套平衡树。
#endif
#define NDEBUG
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <map>
#include <algorithm>
#ifdef NDEBUG
# define debug(...)
#else
# define debug(...) fprintf(stderr, __VA_ARGS__)
#endif

typedef long long lolong;
class Treap {
public:
	class Par {
		Treap *val[2];
	public:
		inline Treap *&operator [] (bool id) { return val[id]; }
		inline void swap() { std::swap(val[0], val[1]); }
		Par(Treap *a, Treap *b)
		{ val[0] = a; val[1] = b; }
	};
	int size, fuck;
private:
	int val, weight;
	Par son;
	inline void update() {
		size = 1;
		if(son[0]) size += son[0] -> size;
		if(son[1]) size += son[1] -> size;
		if(son[0]) assert(weight >= son[0] -> weight);
		if(son[1]) assert(weight >= son[1] -> weight);
		if(son[0]) assert(val >= son[0] -> val);
		if(son[1]) assert(val <= son[1] -> val);
	}
public:
	static Treap *merge(Treap *a, Treap *b) {
		if(not a) return b;
		if(not b) return a;
		if(a -> val > b -> val) std::swap(a, b); // It shouldn't be run
		assert(a -> lessthan(b -> val + 1) == a -> size);
		if(a -> weight < b -> weight) {
			b -> son[0] = merge(a, b -> son[0]);
			b -> update();
			return b;
		} else {
			a -> son[1] = merge(a -> son[1], b);
			a -> update();
			return a;
		}
	}
	Par split(int k) {
		if(not k) return Par(nullptr, this);
		int lsize = son[0] ? son[0] -> size : 0;
		if(k <= lsize) {
			assert(son[0]);
			Par p = son[0] -> split(k);
			son[0] = nullptr;
			update();
			return Par(p[0], merge(p[1], this));
		} else if(k <= lsize + 1) {
			Treap *s = son[1];
			son[1] = nullptr;
			update();
			return Par(this, s);
		} else if(k <= size) {
			assert(son[1]);
			Par p = son[1] -> split(k - lsize - 1);
			son[1] = nullptr;
			update();
			return Par(merge(this, p[0]), p[1]);
		}
		assert(false);
		return Par(nullptr, nullptr);
	}
	int lessthan(int v) { // rank
		if(v <= val) return son[0] ? son[0] -> lessthan(v) : 0;
		else return son[1] ?
			size - son[1] -> size + son[1] -> lessthan(v) : size;
	}
	Treap(int v):
		size(1), val(v), weight(rand()), son(nullptr, nullptr) { }
	void print(int d=0) {
#ifdef NDEBUG
		return;
#endif
		if(son[0]) son[0] -> print(d + 1);
		for(int i = 0; i < d; i ++) debug(" ");
		debug("v%d(s%d, w%d)\n", val, size, weight);
		if(son[1]) son[1] -> print(d + 1);
	}
};

inline int input() { int x; scanf("%d", &x); return x; }
inline int lowbit(int x) { return x & (- x); }

const int maxn = 100005, maxk = 20;
int head[maxn], to[maxn << 1], nxt[maxn << 1];
int rank[maxn << 1], greed[maxn << 1], hp;
lolong ans[maxn];
Treap *t[maxn];
std::map<int, int> rel_img;
int img_rel[maxn], ip;

void dfs(int u, int fa) {
	debug("%d: %lld\n", u, ans[u]);
	for(int i = head[u]; i; i = nxt[i]) {
		if(to[i] == fa) continue;
		int tot = 0, cost;
		int img_rk = rel_img[rank[i]];
		for(int k = img_rk - 1; k > 0; k -= lowbit(k))
			if(t[k])
				tot += t[k] -> size;
		if(tot) {
			int l = 0, r = 1000000000;
			while(l < r) {
				int mid = (l + r) >> 1, les = 0;
				for(int k = img_rk - 1; k > 0; k -= lowbit(k))
					if(t[k])
						les += t[k] -> lessthan(mid);
				if(les * 2 >= tot) r = mid;
				else l = mid + 1;
			}
			assert(l == r);
			cost = l;
		} else
			cost = greed[i];
		ans[to[i]] = ans[u] + cost;
		for(int k = img_rk; k < maxn; k += lowbit(k)) {
			if(t[k]) {
				int les = t[k] -> lessthan(cost);
				Treap::Par p = t[k] -> split(les);
				t[k] = Treap::merge(p[0],
						Treap::merge(new Treap(cost), p[1]));
			} else {
				t[k] = new Treap(cost);
			}
		}
		dfs(to[i], u);
		for(int k = img_rk; k < maxn; k += lowbit(k)) {
			assert(t[k]);
			int les = t[k] -> lessthan(cost);
			Treap::Par p = t[k] -> split(les);
			assert(p[1]);
			t[k] = Treap::merge(p[0], p[1] -> split(1)[1]);
		}
	}
}

int main() {
	int n = input();
	for(int i = 0; i < n; i ++) {
		int u = input(), v = input(), b = input(), c = input();
		nxt[++ hp] = head[u];
		head[u] = hp;
		to[hp] = v;
		rank[hp] = b;
		greed[hp] = c;
		nxt[++ hp] = head[v];
		head[v] = hp;
		to[hp] = u;
		rank[hp] = b;
		greed[hp] = c;
		img_rel[++ ip] = b;
	}
	std::sort(img_rel + 1, img_rel + ip + 1);
	ip = int(std::unique(img_rel + 1, img_rel + ip + 1) - img_rel - 1);
	for(int i = 1; i <= ip; i ++)
		rel_img[img_rel[i]] = i;
	dfs(0, -1);
	for(int i = 1; i <= n; i ++)
		printf("%lld ", ans[i]);
	puts("");
}
