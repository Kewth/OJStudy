#if 0
2019.03.14

Dra 曰：线性基可以维护异或和为 x 的方案数！
于是推荐给了我这题

对任意 x ，集合 S 异或和为 x 方案数只能为 0 或 2 ^ (n - k) ，
其中 n 为 S 大小， k 为 S 线性基的大小。
口胡证明：
若 x 是 S 的一个子集的异或和，
那么 S 的线性基一定有唯一子集的异或和为 x ，
且 S 中其它未被加入线性基的元素（ n - k 个）任意子集的异或和异或上 x 都能被线性基异或出来。

有这个结论就用数位 DP 的思路求所有小与 Q 的数中能被异或出来的数量。
#endif
#include <bits/stdc++.h>

const int maxn = 1000060, maxk = 31, mod = 10086;
int num[maxn];
int xian[maxk];
int xsum[maxk];

void xian_add(int x) {
	for(unsigned k = maxk - 1; k < maxk; k --)
		if(x >> k & 1) {
			if(xian[k])
				x ^= xian[k];
			else {
				xian[k] = x;
				xsum[k] = 1;
				break;
			}
		}
}

int main() {
	int n, r;
	std::cin >> n;
	for(int i = 1; i <= n; i ++)
		std::cin >> num[i];
	std::cin >> r;
	for(int i = 1; i <= n; i ++)
		xian_add(num[i]);
	for(unsigned k = 1; k < maxk; k ++)
		xsum[k] += xsum[k - 1];
	int tot = 0;
	/* int used = 0; */
	for(unsigned k = maxk - 1; k < maxk; k --)
		if(r >> k & 1 and xian[k]) {
			int power = 1, tmp = k ? xsum[k - 1] : 0;
			while(tmp --)
				(power <<= 1) %= mod;
			tot += power;
		}
		/* if(r >> k & 1) { */
		/* 	assert(r >> (k + 1) == used >> (k + 1)); */
		/* 	int power = 1, tmp = k ? xsum[k - 1] : 0; */
		/* 	while(tmp --) */
		/* 		(power <<= 1) %= mod; */
		/* 	(tot += power) %= mod; */
		/* 	if(not xian[k]) */
		/* 		break; */
		/* 	if(not (used >> k & 1)) */
		/* 		used ^= xian[k]; */
		/* 	assert(used >> k & 1); */
		/* } else if(used >> k & 1) { */
		/* 	if(xian[k]) */
		/* 		used ^= xian[k]; */
		/* 	else */
		/* 		break; */
		/* 	assert(not (used >> k & 1)); */
		/* } */
	int power = 1, tmp = n - xsum[maxk - 1];
	while(tmp --)
		(power <<= 1) %= mod;
	std::clog << tot << ' ' << power << std::endl;
	std::cout << (power * tot + 1) % mod << std::endl;
}
