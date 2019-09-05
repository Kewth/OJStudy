#if 0
2019.08.02

考虑求中位数大于等于 x 的区间数，这样就可以套个二分求出 Kth 。
把数分两类：大于等于 x 的为 1 ，否则为 -1 ，
那么区间中位数大于等于 x 当且仅当区间和大于 0 。
分治求区间和大于 0 的数量，中间分奇偶用桶存权值即可。
#endif
#include <cstdio>
#include <set>
#include <algorithm>
#include <climits>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline lolong input() {
	int c = getchar();
	lolong x = 0;
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

const int maxn = 100005;
int a[maxn];
int b[maxn];
int tmp[2][maxn << 1];

lolong check(int l, int r) {
	if(l == r)
		return b[l] > 0;
	int mid = (l + r) >> 1;
	lolong res = check(l, mid) + check(mid + 1, r);
	int now[2] = {0, 0};
	for(int i = mid + 1, sum = 0; i <= r; i ++) {
		sum += b[i];
		tmp[i & 1][maxn + sum] ++;
		if(sum > 0)
			now[i & 1] ++;
	}
	for(int i = mid, L = maxn + 1; i >= l; i --) {
		if(b[i] == -1) {
			now[0] -= tmp[0][L];
			now[1] -= tmp[1][L];
		}
		L -= b[i];
		if(b[i] == 1) {
			now[0] += tmp[0][L];
			now[1] += tmp[1][L];
		}
		res += now[i & 1];
	}
	for(int i = mid + 1, sum = 0; i <= r; i ++) {
		sum += b[i];
		tmp[i & 1][maxn + sum] --;
	}
	// debug("check %d-%d = %lld\n", l, r, res);
	return res;
}

int main() {
	int n = input();
	lolong k = input();
	int l = INT_MAX, r = INT_MIN;
	for(int i = 1; i <= n; i ++) {
		a[i] = input();
		l = std::min(l, a[i]);
		r = std::max(r, a[i]);
	}
	while(l < r) {
		int mid = (0ll + l + r + 1) >> 1;
		// debug("get mid = %d\n", mid);
		for(int i = 1; i <= n; i ++)
			b[i] = a[i] >= mid ? 1 : -1;
		if(check(1, n) < k)
			r = mid - 1;
		else
			l = mid;
	}
	printf("%d\n", l);
}
