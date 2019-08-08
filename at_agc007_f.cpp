#if 0
2019.08.08

之前学的是假的 Treap 。。
观察 s 的每个字符到 t 的路径，是一些不相交的折线。
考虑维护折线在每个位置的最大深度，最大的深度即最少的 copy 次数。
在 t 上从右到左依次考虑，每次贪心选 s 上最靠右的可以选的字符并连上折线，
考虑这条折线对区间内深度的影响，不难发现就是一段区间的 deep[i] = deep[i + 1] + 1 ，
直接暴力维护是 O(n^2) 的，用些高级的队列做法可以做到 O(n) ，
然而这个操作就是把一段区间 +1 后左移，平衡树爆艹上去，复杂度 O(nlogn) ，最慢的 1.5s ，勉强跑过。
#endif
#include <cstdio>
#include <queue>
#include <cassert>
#include <cstdlib>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

inline int lowbit(int x) { return x & - x; }

int TOT;
struct Treap {
	Treap *son[2];
	int val, weight, lazy, max, size;
	inline void update() {
		max = val;
		size = 1;
		if(son[0]) {
			assert(weight >= son[0] -> weight);
			max = std::max(max, son[0] -> max + lazy);
			size += son[0] -> size;
		}
		if(son[1]) {
			assert(weight >= son[1] -> weight);
			max = std::max(max, son[1] -> max + lazy);
			size += son[1] -> size;
		}
	}
	inline void push_down() {
		if(son[0]) {
			son[0] -> lazy += lazy;
			son[0] -> val += lazy;
		}
		if(son[1]) {
			son[1] -> lazy += lazy;
			son[1] -> val += lazy;
		}
		lazy = 0;
	}
	static Treap *merge(Treap *a, Treap *b) {
		if(not a) return b;
		if(not b) return a;
		if(a -> weight > b -> weight) {
			a -> push_down();
			a -> son[1] = merge(a -> son[1], b);
			a -> update();
			return a;
		} else {
			b -> push_down();
			b -> son[0] = merge(a, b -> son[0]);
			b -> update();
			return b;
		}
	}
	void split(int k, Treap *&x, Treap *&y) {
		TOT ++;
		int lsize = son[0] ? son[0] -> size : 0;
		push_down();
		if(k <= 0) {
			x = nullptr;
			y = this;
		} else if(k <= lsize) {
			assert(son[0]);
			y = this;
			son[0] -> split(k, x, son[0]);
		} else if(k <= lsize + 1) {
			x = this;
			y = son[1];
			son[1] = nullptr;
		} else if(k <= size) {
			assert(son[1]);
			x = this;
			son[1] -> split(k - lsize - 1, son[1], y);
		} else
			assert(false);
		update();
	}
	inline void add(int x) {
		val += x;
		lazy += x;
		max += x;
	}
	inline Treap(): son(), val(0), weight(rand()), lazy(0), max(0), size(1) { }
};

const int maxn = 1000005;
char s[maxn], t[maxn];
std::priority_queue<int> last[30];

int main() {
	int n = input();
	scanf("%s", s + 1);
	scanf("%s", t + 1);
	for(int i = 1; i <= n; i ++)
		last[s[i] - 'a'].push(i);
	Treap *T = nullptr;
	for(int i = 1; i <= n; i ++)
		T = Treap::merge(T, new Treap());
	int m = n;
	for(int i = n, find = 0; i; i -= find) {
		if(last[t[i] - 'a'].empty()) {
			puts("-1");
			return 0;
		}
		int p = last[t[i] - 'a'].top();
		while(m >= p) {
			last[s[m] - 'a'].pop();
			m --;
		}
		if(i != p) {
			Treap *t1, *t2, *t3, *t4, *t5;
			T -> split(p - 1, t1, t2);
			t2 -> split(1, t2, t3);
			t3 -> split(i - p - 1, t3, t4);
			t4 -> split(1, t4, t5);
			if(t2 and t4)
				t2 -> add(t4 -> val - t2 -> val + 1);
			if(t3)
				t3 -> add(1);
			if(t4)
				t4 -> add(1);
#if 0
			debug("%d - %d\n", p, i);
			debug("%d, %d, %d, %d, %d\n",
					t1 ? t1 -> max : 0,
					t2 ? t2 -> max : 0,
					t3 ? t3 -> max : 0,
					t4 ? t4 -> max : 0,
					t5 ? t5 -> max : 0);
			debug("%d\n", TOT);
			fflush(stderr);
#endif
			T = Treap::merge(
					t1, Treap::merge(
						t3, Treap::merge(
							t4, Treap::merge(
								t2, t5))));
			// for(int j = p; j < i; j ++)
				// deep[j] = deep[j + 1] + 1;
			// deep[i] ++;
		}
		find = 0;
		for(int j = i; j >= p and t[j] == t[i]; j --)
			find ++;
	}
	printf("%d\n", T -> max);
}

