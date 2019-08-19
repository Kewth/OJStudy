#if 0
2019.08.19

每次询问相当于只考虑一个子图，而这个子图一定是森林，要求的就是树的个数。
而森林中树的个数等于点数减去边数，那么现在要求子图内的边数。
由于子图是编号在一个区间的点，那么子图内的边一定是两端都在区间内的边。
把边和询问都抽象成区间，问题转换为求询问区间包含了多少边区间，扫描线 + 树状数组即可。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() {
	int x = 0, c = getchar();
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

const int maxn = 200005;
int count[maxn];
std::vector<int> edge[maxn], query[maxn];
int ans[maxn];
int qr[maxn];
int bit[maxn];

int main() {
	int n = input(), q = input();
	for(int i = 1; i < n; i ++) {
		int u = input(), v = input();
		if(u > v)
			std::swap(u, v);
		edge[u].push_back(v);
	}
	for(int i = 1; i <= q; i ++) {
		int l =input(), r = input();
		query[l].push_back(i);
		qr[i] = r;
		ans[i] = r - l + 1;
	}
	for(int i = n; i; i --) {
		for(int k : edge[i])
			while(k < maxn) {
				bit[k] ++;
				k += k & -k;
			}
		for(int p : query[i])
			for(int k = qr[p]; k; k -= k & -k)
				ans[p] -= bit[k];
	}
	for(int i = 1; i <= q; i ++)
		printf("%d\n", ans[i]);
}
