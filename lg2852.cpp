#if 0
2019.02.27

二分最长的长度再判断是否有 k 个长度为 mid 的子串。
子串的统计可以用后缀数组，但是我懒。
计算所有长为 mid 的子串的哈希值放在 std::map 统计即可。

#endif
#include <bits/stdc++.h>

int input() { int res; scanf("%d", &res); return res; }

typedef unsigned long long Hash;
const int maxn = 20050, base = 29;
int num[maxn];
Hash sum[maxn];

int check(int n, int len) {
	std::map<Hash, int> mp;
	Hash now = 0, power = 1;
	for(int i=0; i<len; i++) {
		(now *= base) += uint(num[i]);
		/* fprintf(stderr, ".-%d: %llu\n", i, now); */
		power *= base;
	}
	/* fprintf(stderr, "pow: %llu\n", power); */
	for(int i=len; i<=n; i++) {
		(now *= base) += uint(num[i]);
		now -= power * uint(num[i - len]);
		/* fprintf(stderr, "%d-%d: %llu\n", i - len + 1, i, now); */
		mp[now] ++;
	}
	int res = 0;
	for(auto pr: mp)
		res = std::max(pr.second, res);
	/* fprintf(stderr, "(%d) -> %d\n", len, res); */
	return res;
}

int main() {
	int n = input(), m = input();
	int l = 1, r = n;
	for(int i=1; i<=n; i++)
		num[i] = input();
	while(l < r) {
		int mid = (l + r + 1) >> 1;
		if(check(n, mid) >= m) l = mid;
		else r = mid - 1;
	}
	printf("%d\n", l);
}
