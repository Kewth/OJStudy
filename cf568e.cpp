#if 0
2020.02.09

先计算 lis 长度，考虑维护一个序列，依次在末尾添加一个数 a[i] 。
期间维护 f[len] 表示长为 len 的 lis 的末尾最小值。
如果 a[i] 是个确定的数，二分最大的 len 满足 f[len] < a[i] ，
用 a[i] 更新 f[len + 1] 即可。
如果 a[i] = -1 ，枚举所有可能的值更新。
注意到如果两个位置填了同一个值，那么这两个值不会同时出现在一个 lis 中，
因此计算长度的时候无需考虑重复选的情况。

由于要还原子序列，记录转移方向是必须的。
维护 f 的同时维护 g[len] 表示 f[len] 所代表的末尾的下标。
然后如果 a[i] 是个确定的数，
就可以计算 l[i] 表示以 i 结尾的 lis 最大长度，
p[i] 表示这个 lis 除去 i 后结尾的位置。

只需要还原一个最长的 lis ，剩下的随便填就行。
从最长 lis 的末尾开始，如果这个位置是个确定的数，
就可以由 p 跳转到上一个位置。
否则二分一个最大的满足条件的数填进去，
然后暴力枚举所有位置是否能作为上一个位置。
#endif
#include <cstdio>
#include <algorithm>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 100005;
int a[maxn], b[maxn];
int f[maxn], g[maxn];
int len[maxn], pre[maxn];
int tmp[maxn];
bool vis[maxn];

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		a[i] = read;

	int m = read;
	for(int i = 1; i <= m; i ++)
		b[i] = read;
	std::sort(b + 1, b + m + 1);

	for(int i = 1; i <= n + 1; i ++)
		f[i] = 1000000005;

	int max = 0, now = 1;
	for(int i = 1; i <= n; i ++) {
		int nlen = 1;
		if(a[i] == -1) {
			for(int j = 1; j <= m; j ++) {
				while(f[nlen] < b[j])
					++ nlen;
				tmp[j] = nlen;
			}
			for(int j = 1; j <= m; j ++)
				if(tmp[j] > tmp[j - 1]) {
					f[tmp[j]] = b[j];
					g[tmp[j]] = i;
				}
		}
		else {
			nlen = int(std::lower_bound(f, f + n + 1, a[i]) - f);
			f[nlen] = a[i];
			g[nlen] = i;
			pre[i] = g[nlen - 1];
			len[i] = nlen;
		}
		if(nlen > max) {
			max = nlen;
			now = i;
		}
	}

	int nxt = 1000000005, pos = max;
	while(now) {
		// debug("%d\n", now);
		if(a[now] == -1) {
			int p = int(std::lower_bound(b + 1, b + m + 1, nxt) - b - 1);
			// debug(" p = %d\n", p);
			a[now] = b[p];
			vis[p] = 1;
			for(int i = 1; i < now; i ++)
				if(~a[i] and a[i] < a[now] and len[i] == pos - 1) {
					pre[now] = i;
					break;
				}
			if(!pre[now])
				for(int i = 1; i < now; i ++)
					if(a[i] == -1)
						pre[now] = i;
		}
		nxt = a[now];
		now = pre[now];
		-- pos;
	}

	for(int i = 1, j = 1; i <= n; i ++) {
		if(a[i] == -1) {
			while(vis[j]) ++ j;
			a[i] = b[j ++];
		}
		printf("%d ", a[i]);
	}
	puts("");
}
