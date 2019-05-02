#if 0
2019.05.02

三维偏序，sort 做掉第一维，cdq 分治做掉第二维，权值树状数组做掉第三维。
由于比较是 <= 相等的要合并，相等的元素看作整体记个数量一起算贡献。
#endif
#include <bits/stdc++.h>

struct Fuck {
	int a, b, c, times, ans;
	Fuck(): times(1), ans(0) { }
	bool operator == (Fuck &an) {
		return a == an.a and b == an.b and c == an.c;
	}
};
const int maxn = 100050, maxm = 200050;
Fuck fuck[maxn];
Fuck cmp[maxn];
int bit[maxm];
int ans[maxm];

inline int lowbit(int x) { return x & (- x); }

void cdq(int l, int r) {
	if(l == r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid);
	cdq(mid + 1, r);
	int p = l, p1, p2;
	for(p1 = l, p2 = mid + 1; p1 <= mid and p2 <= r;)
		if(fuck[p1].b <= fuck[p2].b) {
			for(int k = fuck[p1].c; k < maxm; k += lowbit(k))
				bit[k] += fuck[p1].times;
			cmp[p ++] = fuck[p1 ++];
		} else {
			for(int k = fuck[p2].c; k; k -= lowbit(k))
				fuck[p2].ans += bit[k];
			cmp[p ++] = fuck[p2 ++];
		}
	while(p2 <= r) {
		for(int k = fuck[p2].c; k; k -= lowbit(k))
			fuck[p2].ans += bit[k];
		cmp[p ++] = fuck[p2 ++];
	}
	for(int i = l; i < p1; i ++)
		for(int k = fuck[i].c; k < maxm; k += lowbit(k))
			bit[k] -= fuck[i].times;
	while(p1 <= mid)
		cmp[p ++] = fuck[p1 ++];
	for(int i = l; i <= r; i ++)
		fuck[i] = cmp[i];
	/* std::cerr << l << '-' << r << std::endl; */
	/* for(int i = l; i <= r; i ++) */
	/* 	std::cerr << fuck[i].a << ' ' << fuck[i].b */
	/* 		<< ' ' << fuck[i].c << ' ' << fuck[i].ans << std::endl; */
}

int main() {
	int n, m;
	std::cin >> n >> m;
	for(int i = 1; i <= n; i ++)
		std::cin >> fuck[i].a >> fuck[i].b >> fuck[i].c;
	std::sort(fuck + 1, fuck + n + 1, [](Fuck a, Fuck b) -> bool {
				if(a.a == b.a) {
					if(a.b == b.b) return a.c < b.c;
					return a.b < b.b;
				}
				return a.a < b.a;
			});
	int same = 0;
	for(int i = 1; i < n; i ++)
		if(fuck[i] == fuck[i + 1]) {
			fuck[i + 1].times += fuck[i].times;
			fuck[i].times = 0;
			same ++;
		}
	std::sort(fuck + 1, fuck + n + 1, [](Fuck a, Fuck b) -> bool {
				if(a.times and b.times) {
					if(a.a == b.a) {
						if(a.b == b.b) return a.c < b.c;
						return a.b < b.b;
					}
					return a.a < b.a;
				}
				return a.times > b.times;
			});
	n -= same;
	/* for(int i = 1; i <= n; i ++) */
	/* 	std::cerr << fuck[i].a << ' ' << fuck[i].b */
	/* 		<< ' ' << fuck[i].c << ' ' << fuck[i].ans << std::endl; */
	cdq(1, n);
	for(int i = 1; i <= n; i ++)
		ans[fuck[i].ans + fuck[i].times - 1] += fuck[i].times;
	for(int i = 0; i < n + same; i ++)
		std::cout << ans[i] << std::endl;
	for(int i = 0; i < maxm; i ++)
		assert(bit[i] == 0);
}
