#if 0
2019.03.11

重温树状数组套主席树

之前对这个的空间复杂度有误解，因为要开 n 颗线段树，以为空间会炸。
而树状数组套主席树又不能像前缀和套主席树一样每次再上一个区间的基础上开一条链。
事实上由于线段树维护的并不是整体，
套了树状数组可能只表示一段很小的区间有，因此许多点的权值为零，
因此在修改操作上动态加点。
而且因为动态加点，权值线段树不需要离散化（但是可能常数会大，洛谷上 TLE ）。
（线段树用多了现在都不会树状数组了）

细节方面注意权值有 0 。
#endif
#include <bits/stdc++.h>

class HJT {
private:
	int sum;
	int L, R;
	int fuck;
	HJT *lt, *rt;
	void update() {
		sum = 0;
		if(lt) sum += lt -> sum;
		if(rt) sum += rt -> sum;
		if(lt and lt -> sum == 0) {
			delete lt; // 沃日，卡空间
			lt = NULL;
		}
		if(rt and rt -> sum == 0) {
			delete rt; // 沃日，卡空间
			rt = NULL;
		}
	}
	void check_son() {
		if(lt and rt)
			return;
		/* assert(not lt and not rt); */
		assert(L < R);
		int mid = (L + R) >> 1;
		if(not lt)
			lt = new HJT(L, mid);
		if(not rt)
			rt = new HJT(mid + 1, R);
	}
public:
	void modify(int id, int cg) {
		if(id < L or id > R) return;
		if(L == R) {
			sum += cg;
			return;
		}
		check_son();
		lt -> modify(id, cg);
		rt -> modify(id, cg);
		update();
	}
	HJT(int l, int r): sum(0), L(l), R(r), lt(NULL), rt(NULL) { }
	friend int query_all(int, int, int);
};

const int maxn = 200050, maxk = 30, maxv = 2000000005;
HJT *t[maxn];
int a[maxn];

inline int lowbit(int x) { return x & (- x); }

int query_all(int l, int r, int k) {
	l --;
	HJT *lts[maxk], *rts[maxk];
	int lp = 0, rp = 0;
	for(int x = l; x; x -= lowbit(x))
		lts[lp ++] = t[x];
	for(int x = r; x; x -= lowbit(x))
		rts[rp ++] = t[x];
	int L = (*rts) -> L, R = (*rts) -> R;
	while(L < R) {
		int lsize = 0;
		for(int i = 0; i < rp; i ++)
			if(rts[i] and rts[i] -> lt)
				lsize += rts[i] -> lt -> sum;
		for(int i = 0; i < lp; i ++)
			if(lts[i] and lts[i] -> lt)
				lsize -= lts[i] -> lt -> sum;
		for(int i = 0; i < lp; i ++)
			if(lts[i])
				lts[i] = (k <= lsize) ? lts[i] -> lt : lts[i] -> rt;
		for(int i = 0; i < rp; i ++)
			if(rts[i])
				rts[i] = (k <= lsize) ? rts[i] -> lt : rts[i] -> rt;
		int mid = (L + R) >> 1;
		if(k <= lsize)
			R = mid;
		else {
			L = mid + 1;
			k -= lsize;
		}
	}
	assert(L == R);
	return L;
}

int main() {
	int n, q;
	std::cin >> n >> q;
	for(int i = 1; i <= n; i ++)
		std::cin >> a[i];
	for(int i = n; i; i --) {
		t[i] = new HJT(0, maxv);
		for(int x = i; x <= n; x += lowbit(x))
			t[x] -> modify(a[i], 1);
	}
	while(q --) {
		char type;
		std::cin >> type;
		if(type == 'Q') {
			int l, r, k;
			std::cin >> l >> r >> k;
			std::cout << query_all(l, r, k) << std::endl;
		} else if(type == 'C') {
			int id, v;
			std::cin >> id >> v;
			for(int x = id; x <= n; x += lowbit(x)) {
				t[x] -> modify(a[id], -1);
				t[x] -> modify(v, 1);
			}
			a[id] = v;
		}
	}
}
