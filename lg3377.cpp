#if 0
2019.09.23

左偏树模板，但是总感觉左偏树并不很适合这种查询所属堆的操作，
需要将 fa 路径压缩，十分不自然。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005;
struct Heap {
	lolong val;
	int di;
	int ltid, rtid;
	int faid;
};
Heap pool[maxn];

#define self pool[now]
#define lt pool[self.ltid]
#define rt pool[self.rtid]

int find(int now) {
	if(!self.faid)
		return now;
	return self.faid = find(self.faid);
}

int merge(int now, int x) {
	if(!now) return x;
	if(!x) return now;
	if(self.val > pool[x].val)
		std::swap(now, x);
	self.rtid = merge(self.rtid, x);
	rt.faid = now;
	if(lt.di < rt.di)
		std::swap(self.ltid, self.rtid);
	self.di = rt.di + 1;
	return now;
}

void pop(int now) {
	self.val = -1;
	lt.faid = rt.faid = 0;
	self.faid = merge(self.ltid, self.rtid);
	self.ltid = self.rtid = 0;
}

int main() {
	int n = input(), q = input();
	for(int now = 1; now <= n; now ++) {
		self.val = 1ll * input() * maxn + now;
		self.di = 1;
	}

	while(q --) {
		if(input() == 1) {
			int now = input(), x = input();
			if(self.val != -1 and pool[x].val != -1) {
				now = find(now);
				x = find(x);
				if(now != x)
					merge(now, x);
			}
		}

		else {
			int now = input();
			if(self.val != -1) {
				now = find(now);
				printf("%lld\n", self.val / maxn);
				pop(now);
			} else
				puts("-1");
		}

		/* for(int now = 1; now <= n; now ++) */
		/* 	debug("%d: %d %d %d %d\n", now, self.ltid, self.rtid, self.faid, self.di); */
		/* debug("\n"); */
	}
}
