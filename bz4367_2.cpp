#if 0
2019.04.03

设起点两边分别有 g[i] 表示花 i 天的最大收益。
若已知 g, 枚举两边所用的天数即可得到答案。

n^2 DP
在起点两边设 f[i][j] 表示最远走到 i 点共 j 天的最大收益。
考虑是否停留在 i 即可得到转移，g[i] 就是一段 f[j][i] 的最大值。

n^2 log 主席树
枚举达到的最远点，查询区间内前 k 大的数的和，用主席树搞。

n log^2 主席树优化
设 g[i] 在最远点为 d[i] 处取到最大值，d[i] 是单调的。
那么可以分治求 g ，
若当前求出 g[x] 和 d[x] ，那么 i < x 的 g[x] 的最远点一定在 d[x] 的一边。
i > x 在另一边。
每次 x 取中点并分治求 x 左边的和 x 右边的即可。

妈的傻逼东西卡我空间 64MB 开大一倍会死啊会死啊
重写了一遍数组版的还是没屁用
#endif
#include <bits/stdc++.h>

typedef long long lolong;
const int maxn = 100050, maxlog = 22, maxd = 250050;
lolong to_real[maxn];
std::map<lolong, int> to_img;
int Tp;
class Tree {
private:
	int L, R, size;
	int fuck_memory[1];
	lolong sum;
	int lt, rt;
	void update();
public:
	int lain(int);
	static int build(int, int);
	int copy_build();
	static lolong query(int, int, int);
	Tree() {}
	friend int main();
};
Tree T[maxn * 20];
lolong a[maxn], tmp[maxn];
lolong l1[maxd], l2[maxd], r1[maxd], r2[maxd];
int t[maxn];

void Tree::update() {
	size = T[lt].size + T[rt].size;
	sum = T[lt].sum + T[rt].sum;
}

int Tree::lain(int p) {
	int node = copy_build();
	if(L == R) {
		T[node].size ++;
		T[node].sum += to_real[p];
		return node;
	}
	int mid = (L + R) >> 1;
	if(p <= mid)
		T[node].lt = T[lt].lain(p);
	else
		T[node].rt = T[rt].lain(p);
	T[node].update();
	return node;
}

lolong Tree::query(int l, int r, int k) {
	if(k <= 0) return 0;
	/* std::cerr << "Ql " << T[l].L << ' ' << T[l].R << std::endl; */
	/* std::cerr << "Ql " << T[r].L << ' ' << T[r].R << std::endl; */
	/* std::cerr << "Qs " << T[l].sum << ' ' << T[r].sum << std::endl; */
	if(T[l].L == T[l].R)
		return to_real[T[l].L] * std::min(k, T[r].size - T[l].size);
	int rsize = T[T[r].rt].size - T[T[l].rt].size;
	if(k <= rsize)
		return query(T[l].rt, T[r].rt, k);
	else
		return query(T[l].lt, T[r].lt, k - rsize)
			+ T[T[r].rt].sum - T[T[l].rt].sum;
}

int Tree::build(int l, int r) {
	int now = ++ Tp;
	T[Tp].L = l;
	T[Tp].R = r;
	T[Tp].size = T[Tp].sum = 0;
	if(l == r) {
		T[Tp].lt = T[Tp].rt = 0;
		return Tp;
	}
	int mid = (l + r) >> 1;
	T[now].lt = build(l, mid);
	T[now].rt = build(mid + 1, r);
	return now;
}

int Tree::copy_build() {
	T[++ Tp] = *this;
	return Tp;
}

void fuck(int s, int l, int r, int L, int R,
		lolong *todo, std::function<lolong(int, int, int)> fun) {
	if(l > r) return;
	if(L > R) return;
	int mid = (l + r) >> 1;
	int midpos = -1;
	todo[mid] = -1;
	/* if(todo == l1) std::cerr << l << ' ' << r << std::endl; */
	for(int i = L; i <= R; i ++) {
		lolong sum = fun(s, i, mid);
		/* if(todo == l1) std::cerr << sum << std::endl; */
		if(sum > todo[mid]) {
			todo[mid] = sum;
			midpos = i;
		}
	}
	if(todo == l1 or todo == l2) {
		fuck(s, l, mid - 1, midpos, R, todo, fun);
		fuck(s, mid + 1, r, L, midpos, todo, fun);
	} else {
		fuck(s, l, mid - 1, L, midpos, todo, fun);
		fuck(s, mid + 1, r, midpos, R, todo, fun);
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	int n, s, d;
	std::cin >> n >> s >> d;
	s ++;
	for(int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		tmp[i] = a[i];
	}
	std::sort(tmp + 1, tmp + n + 1);
	int sizep = 0;
	tmp[0] = -1;
	for(int i = 1; i <= n; i ++)
		if(tmp[i] != tmp[i - 1]) {
			to_img[tmp[i]] = ++ sizep;
			to_real[sizep] = tmp[i];
		}
	t[0] = Tree::build(1, sizep);
	for(int i = 1; i <= n; i ++)
		t[i] = T[t[i - 1]].lain(to_img[a[i]]);
	/* for(int i = 0; i <= n; i ++) */
	/* 	std::cerr << "R " << t[i] << ' ' << T[t[i]].sum << ' ' */
	/* 		<< T[t[i]].L << ' ' << T[t[i]].R << std::endl; */
	/* for(int i = 1; i <= Tp; i ++) */
	/* 	std::cerr << "T " << ' ' << T[i].sum << ' ' */
	/* 		<< T[i].L << ' ' << T[i].R << std::endl; */
	fuck(s, 1, d, 1, s - 1, l1, [&](int _s, int _i, int _d) {
			return Tree::query(t[_i - 1], t[_s - 1], _d - (_s - _i));
		});
	fuck(s, 1, d, 1, s - 1, l2, [&](int _s, int _i, int _d) {
			return Tree::query(t[_i - 1], t[_s - 1], _d - ((_s - _i) << 1));
		});
	fuck(s, 1, d, s + 1, n, r1, [&](int _s, int _i, int _d) {
			return Tree::query(t[_s], t[_i], _d - (_i - _s));
		});
	fuck(s, 1, d, s + 1, n, r2, [&](int _s, int _i, int _d) {
			return Tree::query(t[_s], t[_i], _d - ((_i - _s) << 1));
		});
	lolong ans = 0;
	/* for(int i = 1; i <= d; i ++) */
	/* 	std::cerr << l1[i] << ' ' << l2[i] << ' ' */
	/* 		<< r1[i] << ' ' << r2[i] << std::endl; */
	for(int l = 0; l <= d; l ++) {
		ans = std::max(ans, l1[l] + r2[d - l]);
		ans = std::max(ans, l2[l] + r1[d - l]);
	}
	for(int l = 0; l < d; l ++) {
		ans = std::max(ans, l1[l] + r2[d - l - 1] + a[s]);
		ans = std::max(ans, l2[l] + r1[d - l - 1] + a[s]);
	}
	std::cout << ans << std::endl;
}
