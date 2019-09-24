#if 0
date +%Y.%m.%d

题解先咕着。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x = -1; scanf("%d", &x); return x; }

struct Heap {
	int val;
	int ltid, rtid;
	int faid;
	int di;
};

#define self pool[now]
#define lt pool[self.ltid]
#define rt pool[self.rtid]

const int maxn = 100005;
Heap pool[maxn];

int merge(int now, int x) {
	if(!now) return x;
	if(!x) return now;
	if(self.val < pool[x].val)
		std::swap(now, x);
	self.rtid = merge(self.rtid, x);
	rt.faid = now;
	if(lt.di < rt.di)
		std::swap(self.ltid, self.rtid);
	self.di = rt.di + 1;
	self.faid = 0;
	return now;
}

void pop(int now) {
	lt.faid = rt.faid = 0;
	self.faid = merge(self.ltid, self.rtid);
	self.ltid = self.rtid = 0;
	self.di = 1;
}

int find(int now) {
	if(!self.faid)
		return now;
	return self.faid = find(self.faid);
}

int main() {
	while(1) {
		int n = input();
		if(n == -1)
			return 0;

		for(int now = 1; now <= n; now ++) {
			self.val = input();
			self.di = 1;
			self.ltid = self.rtid = self.faid = 0;
		}

		int q = input();
		while(q --) {
			int now = find(input()), x = find(input());
			if(now == x) {
				puts("-1");
				continue;
			}

			pop(now);
			self.val >>= 1;
			now = merge(now, self.faid);
			std::swap(now, x);
			pop(now);
			self.val >>= 1;
			now = merge(now, self.faid);

			now = merge(now, x);

			printf("%d\n", self.val);

			/* for(now = 1; now <= n; now ++) */
			/* 	debug("%d: %d %d %d|%d %d\n", */
			/* 			now, self.ltid, self.rtid, self.faid, self.di, self.val); */
			/* debug("\n"); */
		}
	}
}
