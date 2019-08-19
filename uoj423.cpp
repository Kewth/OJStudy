#if 0
2019.08.19

第二次写李超树又一遍过。

从下往上数层数。
考虑前 i 层稳定需要满足的条件，是对于每个 j < i 有 j + 1 ~ i 的积木都满足重心落在 j 上。
量化这个条件，即
sum((l[k] + r[k]) / 2 * (r[k] - l[k])) / sum(r[k] - l[k]) 在 l[j] 到 r[j] 之间。

上式是两个区间和的商，即 (va[i] - va[j]) / (vb[i] - vb[j]) 不大于 r[j] 不小于 l[j] 。
以不小于 l[j] 为例，把分母乘过去得 va[i] >= l[j] * vb[i] - vb[j] * l[j] + va[j] 。
即 va[i] >= k * vb[i] + b 的形式。
那么每个 j < i 都对应一条直线，要满足 vb[i] 在所有直线的取值都小于等于 va[i] ，
即所有直线在 x = vb[i] 的最大值小于等于 va[i] ，用李超树做即可。

那么求出了哪些 i 满足前 i 层稳定。
假设有 j < i 满足前 i 层和前 j 层均稳定，那么把 j + 1 ~ i 单独做一定是合法且最优的，证略。
那么答案就是相邻满足条件的 i 的差的最大值。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

struct Tree;
Tree *null;

const int maxn = 100005;
int vl[maxn], vr[maxn];
lolong va[maxn], vb[maxn];

struct Tree {
	int L, R;
	Tree *lt, *rt;
	lolong K, B;

	void insert(lolong k, lolong b) {
		if(this == null)
			return;

		int mid = (L + R) >> 1;

		if(k * vb[mid] + b > K * vb[mid] + B) {
			(K > k ? rt : lt) -> insert(K, B);
			K = k;
			B = b;
		} else
			(k > K ? rt : lt) -> insert(k, b);
	}

	lolong query(int x) {
		if(x < L or x > R)
			return - 1000000000000000000;

		return std::max(K * vb[x] + B,
				std::max(lt -> query(x), rt -> query(x)));
	}

	Tree(int l, int r): L(l), R(r), K(0), B(- 1000000000000000000) {
		if(l == r)
			lt = rt = null;

		else {
			int mid = (L + R) >> 1;
			lt = new Tree(l, mid);
			rt = new Tree(mid + 1, r);
		}
	}
};

int main() {
	null = new Tree(0, 0);

	int n = input();
	for(int i = n; i; i --) {
		vl[i] = input();
		vr[i] = input();
	}

	for(int i = 1; i <= n; i ++) {
		va[i] = va[i - 1] + (vr[i] - vl[i]) * (vr[i] + vl[i]);
		vb[i] = vb[i - 1] + (vr[i] - vl[i]) * 2;
	}

	Tree lt(1, n), rt(1, n);

	int last = 0, ans = 0;

	for(int i = 1; i <= n; i ++) {
		if(lt.query(i) <= va[i] and rt.query(i) <= - va[i]) {
			/* debug("%d\n", i); */
			ans = std::max(ans, i - last);
			last = i;
		}

		lt.insert(vl[i], va[i] - vl[i] * vb[i]);
		rt.insert(- vr[i], vr[i] * vb[i] - va[i]);
	}

	printf("%d\n", ans);
}
