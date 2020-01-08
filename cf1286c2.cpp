#if 0
2020.01.08

询问 [1, n] 和 [1, n - 1] ，前者比后者多出来了 n 个后缀。
通过这 n 个后缀可以很容易还原整个串。
但这样询问总串长太大，但可以通过这个方法先询问出前半段。

还剩下一次询问，自然是询问 [1, n] ，对于长度 l 不超过一半的串，
考虑每个位置被长为 l 的区间覆盖的次数，
不难发现是 1, 2, 3 ... l ... l ... 3, 2, 1 的形式。
将 l 和 l - 1 比较，就是 [l, n - l + 1] 这一部分多被覆盖一次。
这样一来就得到了 [l, n - l + 1] 这个区间的乱序，由于前半段 [1, mid] 已知，
那么就可以得到 [mid + 1, n - l + 1] 这个区间的乱序，也就是后半段的一个前缀。
通过这些前缀自然也能还原出整个后半段。
#endif
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

const int maxn = 105, maxk = 26;
char s_cache[maxn];
struct str {
	int tot[maxk];
	int len() {
		int res = 0;
		for(int i = 0; i < maxk; i ++)
			res += tot[i];
		return res;
	}
	str() {
		for(int i = 0; i < maxk; i ++)
			tot[i] = 0;
	}
};
bool operator < (str a, str b) {
	for(int i = 0; i < maxk; i ++)
		if(a.tot[i] != b.tot[i])
			return a.tot[i] < b.tot[i];
	return 0;
}
str operator - (str a, str b) {
	for(int i = 0; i < maxk; i ++)
		a.tot[i] -= b.tot[i];
	return a;
}
str operator + (str a, str b) {
	for(int i = 0; i < maxk; i ++)
		a.tot[i] += b.tot[i];
	return a;
}

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator str () {
		scanf("%s", s_cache);
		int len = int(strlen(s_cache));
		str x;
		for(int i = 0; i < len; i ++)
			++ x.tot[s_cache[i] - 'a'];
		return x;
	}
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

std::multiset<str> v[maxn];
str A[maxn], B[maxn];
char ans[maxn];

int main() {
	int n = read;
	int mid = (n + 1) >> 1;
	printf("? %d %d\n", 1, mid);
	fflush(stdout);

	for(int l = 1; l <= mid; l ++) {
		for(int r = l; r <= mid; r ++) {
			str now = read;
			v[now.len()].insert(now);
		}
	}

	if(mid > 1) {
		printf("? %d %d\n", 1, mid - 1);
		fflush(stdout);
		for(int l = 1; l < mid; l ++) {
			for(int r = l; r < mid; r ++) {
				str now = read;
				int le = now.len();
				v[le].erase(v[le].find(now));
			}
		}
	}

	for(int i = 1; i <= mid; i ++)
		A[i] = *v[i].begin();

	for(int i = 1; i <= mid; i ++) {
		for(int k = 0; k < maxk; k ++)
			if(A[i].tot[k] > A[i - 1].tot[k])
				ans[mid - i + 1] = char('a' + k);
	}

	if(n > 1) {
		printf("? %d %d\n", 1, n);
		fflush(stdout);

		for(int l = 1; l <= n; l ++)
			for(int r = l; r <= n; r ++) {
				str now = read;
				int le = now.len();
				B[le] = B[le] + now;
			}

		for(int i = n - mid; i; i --)
			B[i] = B[i] - B[i - 1];

		for(int i = 1; i <= n - mid; i ++)
			B[i] = B[i] - A[mid - i + 1];

/* 		for(int i = 1; i <= n - mid; i ++) { */
/* 			debug("B[%d]:", i); */
/* 			for(int k = 0; k < maxk; k ++) */
/* 				for(int j = 0; j < B[i].tot[k]; j ++) */
/* 					debug("%c", 'a' + k); */
/* 			debug("\n"); */
/* 		} */

		B[n - mid + 1] = B[0];

		for(int i = 1; i <= n - mid; i ++) {
			for(int k = 0; k < maxk; k ++)
				if(B[n - mid - i + 1].tot[k] > B[n - mid - i + 2].tot[k])
					ans[mid + i] = char('a' + k);
		}
	}

	printf("! %s\n", ans + 1);
	fflush(stdout);
}
