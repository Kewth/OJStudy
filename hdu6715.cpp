#if 0
2019.08.24

首先 mu[lca(a, b)] = mu[a] mu[b] mu[gca(a, b)] 。
那么枚举约数 d ，把 d 提前，把互质条件拆成 mu[x] ，
把 x 提前，把 T = dx 提前，一系列套路后得到一个式子，
中间有个 mu * mu 的卷积，是积性函数，可以筛，
还有个 mu[k] + mu[2k] + ... 的玩意，需要 O(nlogn) 预处理，
具体的方法可以离线询问再排序从小到大处理出来。
#endif
#include <cstdio>
#include <algorithm>
#include <numeric>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1000005, maxq = 13;
int nop[maxn];
int mu[maxn];
int mumu[maxn];
int s[maxq << 1][maxn];
int tmp[maxq << 1];
int qn[maxq], qm[maxq];

int main() {
	mu[1] = 1;
	mumu[1] = 1;
	for(int i = 2; i < maxn; i ++)
		if(not nop[i]) {
			mu[i] = -1;
			mumu[i] = -2;
			for(int j = 2; i * j < maxn; j ++) {
				nop[i * j] = true;
				if(j % i) {
					mu[i * j] = mu[i] * mu[j];
					mumu[i * j] = mumu[i] * mumu[j];
				} else {
					mu[i * j] = 0;
					int k = 1, y = j;
					while(not (y % i)) {
						k ++;
						y /= i;
					}
					mumu[i * j] = (k + 1) * ((k & 1) ? -1 : 1) * mumu[y];
				}
			}
		}

	/* for(int i = 1; i <= 10; i ++) */
	/* 	debug("%d %d\n", mu[i], mumu[i]); */

	int q = input();

	int p = 0;
	for(int i = 1; i <= q; i ++) {
		tmp[++ p] = qn[i] = input();
		tmp[++ p] = qm[i] = input();
	}

	std::sort(tmp + 1, tmp + p + 1);

	for(int k = 1; k <= p; k ++) {
		for(int i = 1; i <= tmp[k - 1]; i ++) {
			s[k][i] = s[k - 1][i];
			if(tmp[k - 1] / i + 1 <= tmp[k] / i)
				for(int j = tmp[k - 1] / i + 1; j <= tmp[k] / i; j ++)
					s[k][i] += mu[i * j];
		}
		for(int i = tmp[k - 1] + 1; i <= tmp[k]; i ++) {
			s[k][i] = s[k - 1][i];
			for(int j = 1; j <= tmp[k] / i; j ++)
				s[k][i] += mu[i * j];
		}
	}

	for(int i = 1; i <= q; i ++) {
		if(qn[i] < qm[i])
			std::swap(qn[i], qm[i]);
		int idn, idm;
		for(int k = 1; k <= p; k ++) {
			if(tmp[k] == qn[i])
				idn = k;
			if(tmp[k] == qm[i])
				idm = k;
		}

		int ans = 0;

		for(int t = 1; t <= qn[i]; t ++)
			ans += s[idn][t] * s[idm][t] * mumu[t];

		printf("%d\n", ans);
	}
}
