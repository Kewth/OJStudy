#if 0
2019.09.24

先令 a[i] = a[i] - i ，这样 b 就可以是单调不减的了。
考虑一段单调不增的 a ，最优的 b 一定都是这段 a 的中位数。
如果是两段单调不增的 a 拼在一起呢？设左右两段的中位数分别为 x, y ，
如果 x <= y ，那么两段最优的 b 直接拼起来即可，
否则 x > y ，不难发现此时最优的 b 一定都是两段 a 一起的中位数。

推广到更一般的结论，将 a 拆分成若干段单调不增的区间，考虑一个一个合并。
由于要维护中位数，可以使用对顶堆，一个小根堆一个大根堆，为了两个区间的合并需要使用左偏树。
实现上也可以一个一个加 a ，将每个 a 看做一个单独的长度为 1 的区间。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

struct Heap {
	int val;
	int ltid, rtid;
	int di;
	int size;
};

#define self pool[now]
#define lt pool[self.ltid]
#define rt pool[self.rtid]

const int maxn = 1000005;
Heap pool[maxn << 1];

int merge(int now, int x) {
	if(!now) return x;
	if(!x) return now;
	if(self.val < pool[x].val)
		std::swap(now, x);
	self.size += pool[x].size;
	self.rtid = merge(self.rtid, x);
	if(rt.di > lt.di)
		std::swap(self.ltid, self.rtid);
	self.di = rt.di + 1;
	return now;
}

int pop(int now) {
	int res = merge(self.ltid, self.rtid);
	self.ltid = self.rtid = 0;
	self.di = self.size = 1;
	self.val *= -1;
	return res;
}

int st_l[maxn], st_r[maxn], st_v[maxn], st_lh[maxn], st_rh[maxn], sp;

int main() {
	int n = input();

	for(int i = 1; i <= n; i ++) {
		pool[i].di = pool[i].size = 1;
		int x = pool[i].val = input() + n - i;
		int lh = i, rh = 0;

		while(sp and x < st_v[sp]) {
			lh = merge(st_lh[sp], lh);
			rh = merge(st_rh[sp], rh);

			while(pool[lh].size > pool[rh].size + 1) {
				int tmp = lh;
				lh = pop(tmp);
				rh = merge(rh, tmp);
			}

			while(pool[rh].size > pool[lh].size + 1) {
				int tmp = rh;
				rh = pop(tmp);
				lh = merge(lh, tmp);
			}

			if(pool[lh].size > pool[rh].size)
				x = pool[lh].val;
			else
				x = - pool[rh].val;

			sp --;

			/* for(int j = 1; j <= sp; j ++) */
			/* 	for(int now = st_l[j]; now <= st_r[j]; now ++) */
			/* 		debug("%d: %d %d | %d %d | %d in %d(%d)\n", */
			/* 				now, self.ltid, self.rtid, self.di, self.size, self.val, */
			/* 				j, st_v[j]); */
			/* for(int now = st_r[sp] + 1; now <= i; now ++) */
			/* 	debug("%d: %d %d | %d %d | %d in now(%d)\n", */
			/* 			now, self.ltid, self.rtid, self.di, self.size, self.val, x); */
			/* debug("\n"); */
		}

		++ sp;
		st_l[sp] = st_r[sp - 1] + 1;
		st_r[sp] = i;
		st_v[sp] = x;
		st_lh[sp] = lh;
		st_rh[sp] = rh;
	}

	lolong ans = 0;

	for(int i = 1; i <= sp; i ++)
		for(int j = st_l[i]; j <= st_r[i]; j ++)
			ans += std::abs(std::abs(pool[j].val) - st_v[i]);

	printf("%lld\n", ans);
	for(int i = 1; i <= sp; i ++)
		for(int j = st_l[i]; j <= st_r[i]; j ++)
			printf("%d ", st_v[i] + j - n);
	puts("");
}
