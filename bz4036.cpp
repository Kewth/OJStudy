#if 0
2019.04.04

神仙题。
首先 min-max 容斥，设随机变量 x_i 表示第 i 位为 1 的操作次数。
集合 S 为一些 x_i 的集合，那么 E(maxS) = \sum (-1)^{|T| - 1} E(minT) 。
当 S 为所有 x 的集合 (2^n - 1) 时，E(maxS) 就是答案。
考虑计算 E(minT) ，易得：
E(minT) = \sum_{k=1}^{INF} p(S - T)^{k-1} (1 - p(S - T)) k ，
其中 p(S) 表示选中 S 的子集的概率。
化简得 E(minT) = 1 / (1 - p(S - T)) 。
考虑求 p(S) ，易得 p(S) = \sum_{T|S=S} P(T) ，
其中 P(T) 表示输入的概率。
那么可以将 P 做快速莫比乌斯变换或者 FWT 得到 p 。
#endif
#include <bits/stdc++.h>

const int maxn = 20;
double p[1 << maxn];

template <class T>
inline void FMT(T *a, int n) {
	for(int m = 2; m <= n; m <<= 1) {
		for(int i = 0; i < n; i += m)
			for(int k = i; k < i + (m >> 1); k ++) {
				T a0 = a[k], a1 = a[k + (m >> 1)];
				a[k] = a0;
				a[k + (m >> 1)] = a0 + a1;
			}
	}
}

inline int bitcount(int x) {
	int res = 0;
	for(int k = 31; k >= 0; k --)
		res += x >> k & 1;
	return res;
}

int main() {
	std::ios::sync_with_stdio(false);
	int n;
	std::cin >> n;
	const int N = 1 << n;
	for(int i = 0; i < N; i ++)
		std::cin >> p[i];
	FMT(p, N);
	double ans = 0;
	for(int T = 1; T < N; T ++) {
		if(1 - p[N - 1 - T] < 1e-7) {
			std::cout << "INF" << std::endl;
			return 0;
		}
		if(bitcount(T) & 1)
			ans += double(1) / (1 - p[N - 1 - T]);
		else
			ans -= double(1) / (1 - p[N - 1 - T]);
	}
	std::cout << std::fixed << std::setprecision(7) << ans << std::endl;
}
