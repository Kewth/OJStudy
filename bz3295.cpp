#if 0
2019.09.03

逆序对是个二维偏序，把存在时间看做第三维，那就是求三维偏序了。
直接蒯的陌上花开代码。
我擦，删的是值不是下标，搞反了还能过样例。
#endif
#include <bits/stdc++.h>

struct Fuck {
	int a, b, c, times, ans;
	Fuck(): times(1), ans(0) { }
	bool operator == (Fuck &an) {
		return a == an.a and b == an.b and c == an.c;
	}
};
const int maxn = 100050;
Fuck fuck[maxn];
Fuck cmp[maxn];
int pos[maxn];
int bit[maxn];
long long ans[maxn];

inline int lowbit(int x) { return x & (- x); }

void cdq(int l, int r) {
	if(l == r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid);
	cdq(mid + 1, r);
	int p = l, p1, p2;
	for(p1 = l, p2 = mid + 1; p1 <= mid and p2 <= r;)
		if(fuck[p1].b <= fuck[p2].b) {
			for(int k = fuck[p1].c; k < maxn; k += lowbit(k))
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
		for(int k = fuck[i].c; k < maxn; k += lowbit(k))
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
	for(int i = 1; i <= n; i ++) {
		fuck[i].a = i;
		std::cin >> fuck[i].b;
		pos[fuck[i].b] = i;
		fuck[i].b *= -1;
		fuck[i].c = -1;
	}
	for(int i = 1; i <= m; i ++) {
		int x;
		std::cin >> x;
		fuck[pos[x]].c = n + 1 - i;
	}
	int p = 0;
	for(int i = 1; i <= n; i ++)
		if(fuck[i].c == -1)
			fuck[i].c = ++ p;
	/* for(int i = 1; i <= n; i ++) */
	/* 	std::cerr << fuck[i].a << ' ' << fuck[i].b */
	/* 		<< ' ' << fuck[i].c << ' ' << fuck[i].ans << std::endl; */
	/* std::cerr << std::endl; */
	cdq(1, n);
	/* for(int i = 1; i <= n; i ++) */
	/* 	std::cerr << fuck[i].a << ' ' << fuck[i].b */
	/* 		<< ' ' << fuck[i].c << ' ' << fuck[i].ans << std::endl; */
	/* std::cerr << std::endl; */
	for(int i = 1; i <= n; i ++) {
		ans[n + 1 - fuck[i].c] += fuck[i].ans;
		fuck[i].ans = 0;
		fuck[i].a *= -1;
		fuck[i].b *= -1;
	}
	std::sort(fuck + 1, fuck + n + 1, [](Fuck a, Fuck b) -> bool {
				if(a.a == b.a) {
					if(a.b == b.b) return a.c < b.c;
					return a.b < b.b;
				}
				return a.a < b.a;
			});
	cdq(1, n);
	/* for(int i = 1; i <= n; i ++) */
	/* 	std::cerr << fuck[i].a << ' ' << fuck[i].b */
	/* 		<< ' ' << fuck[i].c << ' ' << fuck[i].ans << std::endl; */
	/* std::cerr << std::endl; */
	for(int i = 1; i <= n; i ++)
		ans[n + 1 - fuck[i].c] += fuck[i].ans;
	/* for(int i = 1; i <= n; i ++) */
	/* 	std::cerr << ans[i] << std::endl; */
	for(int i = n - 1; i; i --)
		ans[i] += ans[i + 1];
	for(int i = 1; i <= m; i ++)
		printf("%lld\n", ans[i]);
	/* for(int i = 0; i < maxn; i ++) */
	/* 	assert(bit[i] == 0); */
}

