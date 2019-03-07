#if 0
2019.03.07

一开始看错题目了，好难，看题解研究代码才搞懂。。。

这题不要用线性基，却要用到线性基的思想，
与非可以转换为与和非和或。
将 n 个数用 log(maxvalue) 个数表示，
且用这 log 个数部分按位或可以得到原数列部分与非的所有结果。
其中第 k 个数满足二进制第 k 位为 1 ，二进制大于 k 位都为 0 。
很像线性基。

构造方式是通过按位与和非，
x 对线性基第 k 位的贡献是 &= x (x 第 k 位为 1) 或者 &= ~x （反之），

举例：

	00101
	01011
	01111

压缩成（按位与线性基？）：

	10000
	01010
	00100
	00000
	00001

然后求 1 ~ r 内的方案数，用数位 DP 的思路去扫一遍线性基。
若 r 当前这位为 1 ，考虑结果的这一位，
若为 0 ，则后面不再有限制，随便选，方案是 2^(...) ；
若为 1 ，则必须选当前线性基这一位，后面继续限制，继续扫即可。

不得不说这题的代码太精练了，而且有许多需要注意的细节。

#endif
#include <bits/stdc++.h>

typedef long long lolong;
const int maxn = 10050, maxm = 62;
lolong a[maxn];
lolong Ji[maxm];
int suf_sum[maxm];

void num2(lolong x, int m) {
	/* assert((x >> m) == 0); */
	for(int k=m-1; k>=0; k--)
		std::clog << (x >> k & 1);
	std::clog << std::endl;
}

lolong query(lolong x, int m) {
	if(x < 0) return -1; // 额外去除 0 的贡献
	/* num2(x, m); */
	if(x > (1ll << m) - 1)
		return (1ll << suf_sum[m - 1]) - 1;
	lolong res = 0, used = 0;
	for(int k=m-1; k>=0; k--)
		if(x >> k & 1) {
			// 当前为 0 ，后面随意
			if(k and not (used >> k & 1))
				res += (1ll << suf_sum[k - 1]) - 1; // 不包括 0
			// 当前为 1 ，必须用 Ji[k]
			if(Ji[k]) {
				used |= Ji[k];
				if(used > x) break;
				res ++; // 只用 Ji[k] 和 used
			} else if(not(used >> k & 1))
				break; // 当前只能为 0 ，接下来不用考虑
			/* std::clog << res << std::endl; */
		}
	return res;
}

int main() {
	int n, m;
	lolong l, r;
	std::cin >> n >> m >> l >> r;
	for(int i=0; i<n; i++)
		std::cin >> a[i];
	lolong orsum = 0;
	for(int k=m-1; k>=0; k--)
		if(not (orsum >> k & 1)) {
			lolong &now = Ji[k];
			now = (1ll << m) - 1;
			for(int i=0; i<n; i++)
				if(a[i] >> k & 1)
					now &= a[i];
				else
					now &= ~ a[i];
			orsum |= now;
			assert(now >> k & 1);
			suf_sum[k] = 1;
		}
	for(int k=1; k<m; k++)
		suf_sum[k] += suf_sum[k - 1];
	/* for(int k=m-1; k>=0; k--) */
	/* 	num2(Ji[k], m); */
	/* std::clog << std::endl; */
	std::cout << query(r, m) - query(l - 1, m) << std::endl;
}
