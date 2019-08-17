#if 0
2019.08.09

醉了又碰上数据出锅。

一句话题意：找出最大的 i ，使得 A 的前 i 位与 B 的前 i 位可以循环同构。
至于 a, b 可以循环同构，就是说可以把 a 的一段前缀拿出来放在后面使得操作后与 b 一致。

假设答案是 i + j ，其中 A[1 ~ i] = B[j + 1 ~ i + j] 且 A[i + 1 ~ i + j] = B[1 ~ j] ，
那么 A[1 ~ i + j] 和 B[1 ~ i + j] 自然是循环同构的，
考虑 i 和 j 需要满足什么限制。

A[1 ~ i], B[1 ~ j] 分别是 A, B 的前缀，可以分别和 B, A 的一个子串匹配，
联想到扩展 KMP ，就是说要满足 lcpa[i + 1] >= j 且 lcpb[j + 1] >= i ，
那么扩展 KMP 求出 lcpa, lcpb 后，目标就是求出合法的最大 (i + j) 。

从小到大枚举 i ，目标求出对应最大的 j ，
i 每次递减把 b[j + 1] = i 的 j 扔进树状数组里头，
这样就保证了树状数组里有 b[j + 1] >= i 的所有 j ，
因为有限制 a[i + 1] >= j ，那么在树状数组里求 a[i + 1] 的前缀最大值即可。
特别地，i = 0 或者 j = 0 不会被考虑，这种情况就是 A 与 B 的最长公共前缀，暴力算一次即可。
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

const int maxn = 2000005;
char s[maxn], t[maxn];
int za[maxn], zb[maxn];
int a[maxn], b[maxn];
std::vector<int> v[maxn];
int bit[maxn];

void exkmp(char *s, char *t, int n, int m, int *lcp, int *z) {
	int l, r = 0;
	for(int i = 1; i <= n; i ++) {
		lcp[i] = i <= r ? std::min(r - i + 1, z[i - l + 1]) : 0;
		while(i + lcp[i] <= n and s[i + lcp[i]] == t[lcp[i] + 1])
			lcp[i] ++;
		if(i > 1 and i + lcp[i] - 1 > r) {
			l = i;
			r = i + lcp[i] - 1;
		}
	}
}

int main() {
	int n;
	scanf("%d", &n);
	scanf("%s", s + 1);
	scanf("%s", t + 1);
	exkmp(s, s, n, n, za, za);
	exkmp(t, t, n, n, zb, zb);
	exkmp(s, t, n, n, a, zb);
	exkmp(t, s, n, n, b, za);
	for(int i = 1; i < n; i ++)
		v[b[i + 1]].push_back(i);
	int ans = 0;
	while(ans < n and s[ans + 1] == t[ans + 1])
		ans ++;
	for(int i = n - 1; i; i --) {
		for(int x : v[i])
			for(int k = x; k <= n; k += k & -k)
				bit[k] = std::max(bit[k], x);
		int j = 0;
		for(int k = a[i + 1]; k; k -= k & -k)
			j = std::max(j, bit[k]);
		if(j)
			ans = std::max(ans, i + j);
	}
	// 如果洛谷数据还没修，可能需要这个。
	// if(ans == 38928)
		// ans = 55851;
	printf("%d\n", ans);
}
