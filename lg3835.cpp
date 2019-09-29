#if 0
2019.09.29

可持久化平衡树模板。
数组开 log 倍是不够的，每次 split/merge 都会产生 log 个节点，
而像插入删除这种操作可能一共用到 4 次 split/merge 。

一个简单的空间优化是去掉 merge 的复制操作，
事实上由于 merge 操作的总是 split 新建的节点，merge 是可以不用可持久化的。
#endif
#include <cstdio>
#include <cstdlib>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

struct Treap {
    int val, times, size, weight;
	int ltid, rtid;
};
#define self pool[now]
#define lt pool[self.ltid]
#define rt pool[self.rtid]

const int maxn = 500005;
Treap pool[maxn * 40];
int pp;

inline void update(int now) {
	self.size = self.times + lt.size + rt.size;
}

void split(int now, int v, int &a, int &b) {
	if(!now)
		a = b = 0;
	else {
		pool[++ pp] = self;
		now = pp;
		if(v < self.val) {
			split(self.ltid, v, a, self.ltid);
			b = now;
		} else {
			split(self.rtid, v, self.rtid, b);
			a = now;
		}
		update(now);
	}
}

int kth(int now, int k) {
	if(k <= lt.size)
		return kth(self.ltid, k);
	if(k <= lt.size + self.times)
		return self.val;
	return kth(self.rtid, k - lt.size - self.times);
}


int merge(int a, int b) {
	if(!a) return b;
	if(!b) return a;

	/* int now = ++ pp; */
	if(pool[a].weight > pool[b].weight) {
		pool[a].rtid = merge(pool[a].rtid, b);
		update(a);
		return a;
	} else {
		pool[b].ltid = merge(a, pool[b].ltid);
		update(b);
		return b;
    }
}

void print(int now, int d = 0) {
	/* if(self.ltid) print(self.ltid, d + 1); */
	/* for(int i = 0; i < d; i ++) debug(" "); */
	/* debug("%d: %d %d| %d %d| %d\n", */
	/* 		now, self.ltid, self.rtid, self.times, self.size, self.val); */
	/* if(self.rtid) print(self.rtid, d + 1); */
	/* if(!d) debug("\n"); */
}

int history[maxn];

int main() {
	srand(19491001);

	int now = ++ pp;
	self.times = self.size = 1;
	self.weight = rand();

	now = ++ pp;
	self.times = self.size = 1;
	self.weight = rand();
	self.val = - 2147483647;
	now = ++ pp;
	self.times = 1;
	self.size = 1;
	self.weight = rand();
	self.val = 2147483647;
	self.ltid = now - 1;

	print(now);
	history[0] = now;

    int q = input();
	for(int i = 1; i <= q; i ++) {
		now = history[input()];
        int t = input(), x = input();

        if(t == 1 or t == 2) {
			int a, b, c;
			split(now, x - 1, a, b);
			split(b, x, b, c);

            if(t == 1) {
				if(!b) {
					b = ++ pp;
					pool[b] = pool[1];
					pool[b].val = x;
					pool[b].weight = rand();
				} else {
					pool[b].times ++;
					pool[b].size ++;
				}
            } else {
				print(b);
				if(pool[b].times == 1)
					b = 0;
                else if(b) {
					pool[b].times --;
					pool[b].size --;
				}
            }

            now = merge(a, merge(b, c));
        }

        else if(t == 3) {
			int a, b;
			split(now, x - 1, a, b);
			printf("%d\n", pool[a].size);
            now = merge(a, b);
        }

        else if(t == 4)
			printf("%d\n", kth(now, x + 1));

        else if(t == 5) {
			int a, b;
			split(now, x - 1, a, b);
			printf("%d\n", kth(a, pool[a].size));
            now = merge(a, b);
        }

        else if(t == 6) {
			int a, b;
			split(now, x, a, b);
			printf("%d\n", kth(b, 1));
            now = merge(a, b);
        }

		print(now);
		history[i] = now;
    }
}
