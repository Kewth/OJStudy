#if 0
2019.07.29

考虑分治，那么对于当前分治区间只需要求跨过中点的区间最大贡献。
从中点向两边暴力求出后缀 gcd 和前缀 gcd ，
那么求最大贡献需要两两枚举统计，复杂度仍是 O(N^2 logN) 。
但是不难发现前缀 gcd 中 gcd 每次减小会减小成前面的数的因子，那么至少缩小一般。
所以前缀 gcd 中只有 O(logV) 个不同的值，后缀同理，只对这 O(logV) 个值两两枚举即可。
复杂度 O(Nlog^3V) ，实际上这个 logV 根本跑不满，飞快。
#endif
#include <cstdio>
#include <algorithm>

typedef long long lolong;
inline lolong input() {
	int c = getchar();
	lolong x = 0;
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

const int maxn = 100005;
lolong val[maxn];
lolong a[maxn], b[maxn];
lolong A[maxn], Alen[maxn], B[maxn], Blen[maxn];

lolong gcd(lolong x, lolong y) {
	if(not y) return x;
	return gcd(y, x % y);
}

lolong solve(int l, int r) {
	if(l == r) return val[l];
	int mid = (l + r) >> 1;
	lolong res = std::max(solve(l, mid), solve(mid + 1, r));
	a[0] = b[0] = 0;
	int ap = 0, bp = 0;
	for(int i = 1; i <= mid - l + 1; i ++) {
		a[i] = gcd(a[i - 1], val[mid - i + 1]);
		if(a[i] != a[i - 1]) {
			A[++ ap] = a[i];
			Alen[ap] = i;
		} else
			Alen[ap] ++;
	}
	for(int i = 1; i <= r - mid; i ++) {
		b[i] = gcd(b[i - 1], val[mid + i]);
		if(b[i] != b[i - 1]) {
			B[++ bp] = b[i];
			Blen[bp] = i;
		} else
			Blen[bp] ++;
	}
	for(int i = 1; i <= ap; i ++) {
		lolong g = A[i];
		for(int j = 1; j <= bp; j ++) {
			g = gcd(g, B[j]);
			res = std::max(res, g * (Alen[i] + Blen[j]));
		}
	}
	return res;
}

int main() {
	int T = input();
	while(T --) {
		int n = input();
		for(int i = 1; i <= n; i ++)
			val[i] = input();
		printf("%lld\n", solve(1, n));
	}
}
