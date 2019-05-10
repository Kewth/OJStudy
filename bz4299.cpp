#if 0
2019.04.04

若一些数的 Forbitsum 为 x ，当且仅当 [1, x] 的数的和一定小于 x 。
那么可以用主席树查询权值区间的和，但是要枚举 x ，复杂度 O(n^2 log) 。
若 [1, x] 的数的和为 y, 那么 y >= x 时下一个 x 直接考虑 y + 1 ，
据说这样枚举 x 最多枚举 log 次，复杂度 O(n log^2) 。

emm 写主席树必卡空间，离散化不方便直接动态开点即可，
值域开到 1e9 会 MLE ，开到 1e7 即可。
#endif
#include <bits/stdc++.h>

class Tree {
private:
	int L, R, sum;
	int fuck_memory;
	Tree *lt, *rt;
	void update() {
		sum = 0;
		if(lt) sum += lt -> sum;
		if(rt) sum += rt -> sum;
	}
	void getson() {
		int mid = (L + R) >> 1;
		if(not lt)
			lt = new Tree(L, mid);
		if(not rt)
			rt = new Tree(mid + 1, R);
	}
	void checkson() {
		if(lt and not lt -> sum) {
			delete lt;
			lt = nullptr;
		}
		if(rt and not rt -> sum) {
			delete rt;
			rt = nullptr;
		}
	}
public:
	/* static Tree *const null; */
	Tree *lain(int p) {
		Tree *node = new Tree(*this);
		if(L == R) {
			node -> sum += p;
			return node;
		}
		int mid = (L + R) >> 1;
		getson();
		if(p <= mid)
			node -> lt = lt -> lain(p);
		else
			node -> rt = rt -> lain(p);
		node -> update();
		node -> checkson();
		checkson();
		return node;
	}
	static int query(Tree *lt, Tree *rt, int l, int r) {
		if(not (rt -> sum - lt -> sum)) return 0;
		if(r < lt -> L or l > rt -> R) return 0;
		if(l <= lt -> L and rt -> R <= r) return rt -> sum - lt -> sum;
		lt -> getson();
		rt -> getson();
		int res = query(lt -> lt, rt -> lt, l, r) +
			query(lt -> rt, rt -> rt, l, r);
		lt -> checkson();
		rt -> checkson();
		return res;
	}
	Tree(int l, int r): L(l), R(r), sum(0), lt(nullptr), rt(nullptr) { }
	/* Tree(): L(-1), R(-1), sum(0), lt(nullptr), rt(nullptr) { } */
};
/* Tree *const Tree::null = new Tree(); */

const int maxn = 100050;
Tree *T[maxn];

int main() {
	std::ios::sync_with_stdio(false);
	int n;
	std::cin >> n;
	T[0] = new Tree(1, 10000000);
	for(int i = 1; i <= n; i ++) {
		int x;
		std::cin >> x;
		T[i] = T[i - 1] -> lain(x);
	}
	int q;
	std::cin >> q;
	while(q --) {
		int l, r;
		std::cin >> l >> r;
		/* std::clog << "Q " << l << ' ' << r << std::endl; */
		for(int now = 1, sum; ; now = sum + 1) {
			sum = Tree::query(T[l - 1], T[r], 1, now);
			/* std::clog << "s " << sum << std::endl; */
			if(sum < now) {
				std::cout << now << std::endl;
				break;
			}
		}
	}
}
