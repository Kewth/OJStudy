#if 0
2019.09.20

对于每个笑话开一个 set 记录所有听过该笑话的区间。
每次添加笑话在对应的 set 里弄出影响的区间，就可以确定哪些要赋 0 哪些赋 1 ，线段树维护。
弄完后把这些区间删掉添加当前的修改区间。
用什么势能分析可以证明这样是可以保证每次修改进行均摊常数次区间修改的复杂度的。
#endif
#include <cstdio>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef std::pair<int, int> Par;
typedef std::set<Par>::iterator iter;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005;
std::set<Par> set[maxn];
int val[maxn * 3], tag[maxn * 3];
int tmpl[maxn], tmpr[maxn];

void nodemodi(int now, int L, int R, int x) {
	val[now] = x * (R - L + 1);
	tag[now] = x;
}

void push_down(int now, int L, int R) {
	if(tag[now] == -1) return;
	int M = (L + R) >> 1;
	nodemodi(now << 1, L, M, tag[now]);
	nodemodi(now << 1 | 1, M + 1, R, tag[now]);
	tag[now] = -1;
}

void modify(int now, int L, int R, int l, int r, int x) {
	if(r < L or l > R or l > r)
		return;

	/* if(now == 1) */
	/* 	debug("%d %d %d\n", l, r, x); */

	if(l <= L and R <= r) {
		nodemodi(now, L, R, x);
		return;
	}

	int M = (L + R) >> 1;
	push_down(now, L, R);
	modify(now << 1, L, M, l, r, x);
	modify(now << 1 | 1, M + 1, R, l, r, x);
	val[now] = val[now << 1] + val[now << 1 | 1];
}

int query(int now, int L, int R, int l, int r) {
	if(r < L or l > R)
		return 0;

	if(l <= L and R <= r)
		return val[now];

	int M = (L + R) >> 1;
	push_down(now, L, R);
	return query(now << 1, L, M, l, r) + query(now << 1 | 1, M + 1, R, l, r);
}

int main() {
	for(int i = 0; i < maxn; i ++) {
		set[i].insert(Par(0, 0));
		set[i].insert(Par(maxn, maxn));
	}

	int n = input(), q = input();

	while(q --) {
		if(input() == 1) {
			int p = input(), x = input(), len = input();
			int l = std::max(p - len, 1), r = std::min(p + len, n);

			/* debug("shit %d-%d %d\n", l, r, x); */

			iter lt = set[x].upper_bound(Par(l, maxn));
			lt --;
			iter rt = set[x].lower_bound(Par(r, maxn));

			int tp = 0;
			for(iter it = lt; it != rt;)
				if(it -> second >= l and it -> first <= r) {
					tmpl[++ tp] = std::max(it -> first, l);
					tmpr[tp] = std::min(it -> second, r);
					if(it -> first < l)
						set[x].insert(Par(it -> first, l - 1));
					if(it -> second > r)
						set[x].insert(Par(r + 1, it -> second));
					set[x].erase(it ++);
				} else
					it ++;

			tmpr[0] = l - 1;
			for(int i = 1; i <= tp; i ++) {
				/* debug("tmp %d %d\n", tmpl[i], tmpr[i]); */
				modify(1, 1, n, tmpr[i - 1] + 1, tmpl[i] - 1, 1);
				modify(1, 1, n, tmpl[i], tmpr[i], 0);
			}
			modify(1, 1, n, tmpr[tp] + 1, r, 1);

			set[x].insert(Par(l, r));
		}

		else {
			int l = input(), r = input();
			printf("%d\n", query(1, 1, n, l, r));
		}
	}
}
