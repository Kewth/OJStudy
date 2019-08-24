#if 0
2019.08.24

其实答案的式子中分母分子的 d 可以消掉的，答案就是 xi += d 后 d 在 f1 的系数。
而且这个 f 完完全全就是一个线段树一样的结构，用线段树维护即可。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1 << 22, mod = 998244353;
int a[maxn];
char op_s[maxn];
int val[maxn];
int lp;

void update(int now) {
	if(op_s[now] == '1')
		val[now] = 1ll * val[now << 1] * val[(now << 1) | 1] % mod;
	else
		val[now] = (val[now << 1] + val[(now << 1) | 1]) % mod;
}

void modify(int now, int p, int l, int r, int x) {
	int mid = (l + r) >> 1;
	if(l == r)
		val[now] = x;
	else {
		if(p <= mid)
			modify(now << 1, p, l, mid, x);
		else
			modify((now << 1) | 1, p, mid + 1, r, x);
		update(now);
	}
	/* debug("%d - %d : %d\n", l, r, val[now]); */
}

int query(int now, int p, int l, int r) {
	int mid = (l + r) >> 1;
	if(l == r)
		return 1;
	if(p <= mid)
		return (1ll * query(now << 1, p, l, mid) *
				(op_s[now] == '1' ? val[now << 1 | 1] : 1)) % mod;
	else
		return (1ll * query(now << 1 | 1, p, mid + 1, r) *
				(op_s[now] == '1' ? val[now << 1] : 1)) % mod;
}

int main() {
	int l = input(), q = input();
	int n = 1 << (l - 1);

	scanf("%s", op_s + 1);

	for(int i = 1; i <= n; i ++)
		modify(1, i, 1, n, i);

	while(q --) {
		if(input() == 1) {
			int p = input(), x = input();
			modify(1, p, 1, n, x);
		}

		else {
			int p = input();
			printf("%d\n", query(1, p, 1, n));
		}
	}
}
