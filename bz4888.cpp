#if 0
2019.06.01

把区间和转换为前缀和 s ，那么题目所求为所有 s[i] - s[j] 的异或和。
一位一位单独计算，考虑计算第 k 位。
枚举 i ，考虑统计小于 i 的 j 中 s[i] - s[j] 第 k 位为 1 的个数。
若 s[i] 与 s[j] 第 k 位不同，那么 k 位后的数 s[j] <= s[i] 才有贡献。
否则第 k 位后 s[j] > s[i] 才有贡献。
分 0 1 讨论，开两个权值树状数组维护即可。
#endif
#include <cstdio>
#include <cstring>

const int maxn = 100005, maxv = 1000005;
int a[maxn], s[maxn];
bool bit0[maxv], bit1[maxv];

inline int lowbit(int x) { return x & -x; }

inline bool bit_query(bool *bit, int n) {
	bool res = false;
	for(int k = n; k; k -= lowbit(k))
		res ^= bit[k];
	return res ^ bit[0];
}

inline void bit_modify(bool *bit, int x) {
	if(x)
		for(int k = x; k < maxv; k += lowbit(k))
			bit[k] ^= 1;
	else
		bit[0] ^= 1;
}

void debug(int n) {
	printf("%d", bit_query(bit0, 0));
	for(int i = 1; i <= n; i ++)
		printf("%d", bit_query(bit0, i) ^ bit_query(bit0, i - 1));
	puts("");
	printf("%d", bit_query(bit1, 0));
	for(int i = 1; i <= n; i ++)
		printf("%d", bit_query(bit1, i) ^ bit_query(bit1, i - 1));
	puts("");
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d", a + i);
	for(int i = 1; i <= n; i ++)
		s[i] = s[i - 1] + a[i];
	int ans = 0;
	for(int k = 0; (1 << k) < maxv; k ++) {
		bool now = false;
		memset(bit0, 0, sizeof bit0);
		memset(bit1, 0, sizeof bit1);
		int suffix = (1 << k) - 1;
		bit_modify(bit0, s[0] & suffix);
		for(int i = 1; i <= n; i ++) {
			if(s[i] >> k & 1) {
				now ^= bit_query(bit1, suffix);
				now ^= bit_query(bit1, s[i] & suffix);
				now ^= bit_query(bit0, s[i] & suffix);
				bit_modify(bit1, s[i] & suffix);
			} else {
				now ^= bit_query(bit0, suffix);
				now ^= bit_query(bit0, s[i] & suffix);
				now ^= bit_query(bit1, s[i] & suffix);
				bit_modify(bit0, s[i] & suffix);
			}
		}
		if(now) ans += 1 << k;
	}
	printf("%d\n", ans);
}
