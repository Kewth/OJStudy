#if 0
2020.01.13

前面的 len 部分很好求，只考虑求 sum(lcp(i, j) [i < j]) 。
对应在 height 数组上就是求所有区间最小值的和。
枚举右端点，用单调栈维护所有使得区间最小值不同的的左端点，然后维护当前右端点的所有区间最小值的和。
单调栈更新的同时是可以很好维护当前的区间最小值的和的。
#endif
#include <cstdio>
#include <algorithm>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

const int maxn = 500005;
char s[maxn];
int sa[maxn], rank[maxn], hi[maxn];
int tmp[maxn], sa2[maxn], t[maxn];
int stack[maxn], sp;

int main() {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1)), tot;

	for(int i = 1; i <= n; i ++) {
		rank[i] = s[i] - 'a' + 1;
		sa2[i] = i;
	}

	for(int i = 1; i <= n; i ++) ++ t[rank[i]];
	for(int i = 1; i <= 26; i ++) t[i] += t[i - 1];
	for(int i = n; i; i --) sa[t[rank[sa2[i]]] --] = sa2[i];
	std::fill(t + 1, t + 257, 0);
	rank[sa[1]] = tot = 1;
	for(int i = 2; i <= n; i ++)
		rank[sa[i]] = s[sa[i]] == s[sa[i - 1]] ? tot : ++ tot;

	for(int m = 1; tot < n; m <<= 1) {
		int p = 0;
		for(int i = 1; i <= m; i ++) sa2[++ p] = n - m + i;
		for(int i = 1; i <= n; i ++) if(sa[i] > m) sa2[++ p] = sa[i] - m;
		for(int i = 1; i <= n; i ++) ++ t[rank[i]];
		for(int i = 1; i <= tot; i ++) t[i] += t[i - 1];
		for(int i = n; i; i --) sa[t[rank[sa2[i]]] --] = sa2[i];
		std::fill(t + 1, t + tot + 1, 0);
		std::copy(rank, rank + n + 1, tmp);
		rank[sa[1]] = tot = 1;
		for(int i = 2; i <= n; i ++)
			rank[sa[i]] = (tmp[sa[i]] == tmp[sa[i - 1]] and
					tmp[sa[i] + m] == tmp[sa[i - 1] + m]) ? tot : ++ tot;
	}

	for(int i = 1; i <= n; i ++) {
		int &k = hi[rank[i]] = std::max(0, hi[rank[i - 1]] - 1);
		while(s[i + k] == s[sa[rank[i] - 1] + k]) ++ k;
	}

	ll ans = 0;
	for(int i = 1; i <= n; i ++)
		ans += 3ll * i * (i - 1) >> 1;

	ll sum = 0;
	for(int i = 1; i <= n; i ++) {
		while(sp and hi[stack[sp]] >= hi[i]) {
			sum -= 1ll * hi[stack[sp]] * (stack[sp] - stack[sp - 1]);
			-- sp;
		}
		stack[++ sp] = i;
		sum += 1ll * hi[stack[sp]] * (stack[sp] - stack[sp - 1]);
		ans -= sum << 1;
	}

	printf("%lld\n", ans);
}
