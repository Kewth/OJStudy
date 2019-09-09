#if 0
2019.09.09

突然发现 Treap 做以权值为键的平衡树时候巨好写写起来巨舒服。
获得成就：平衡树一遍过
虽然还是写了 40min+ 。
#endif
#include <cstdio>
#include <cstdlib>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

struct Treap;
Treap *null;

struct Treap {
	int val, times, size, weight;
	Treap *lt, *rt;

	inline void update() {
		size = times + lt -> size + rt -> size;
	}

	void split(int v, Treap *&a, Treap *&b) {
		if(this == null)
			a = b = null;

		else {
			if(v < val) {
				lt -> split(v, a, lt);
				b = this;
			} else {
				rt -> split(v, rt, b);
				a = this;
			}
			update();
		}
	}

	int kth(int k) {
		if(k <= lt -> size)
			return lt -> kth(k);
		if(k <= lt -> size + times)
			return val;
		return rt -> kth(k - lt -> size - times);
	}

	Treap(int val, int times):
		val(val), times(times), size(times), weight(rand()), lt(null), rt(null) {}
};

Treap *merge(Treap *a, Treap *b) {
	if(a == null) return b;
	if(b == null) return a;

	if(a -> weight > b -> weight) {
		a -> rt = merge(a -> rt, b);
		a -> update();
		return a;
	} else {
		b -> lt = merge(a, b -> lt);
		b -> update();
		return b;
	}
}

int main() {
	null = new Treap(0, 0);

	int q = input();
	Treap *T = new Treap(0, 0);

	while(q --) {
		int t = input(), x = input();

		if(t == 1 or t == 2) {
			Treap *a, *b, *c;
			T -> split(x - 1, a, b);
			b -> split(x, b, c);

			if(t == 1) {
				if(b == null)
					b = new Treap(x, 1);
				else
					b -> times ++;
			} else {
				if(b == null)
					debug("出来挨打\n");
				else if(b -> times == 1)
					b = null;
				else
					b -> times --;
			}

			T = merge(a, merge(b, c));
		}

		else if(t == 3) {
			Treap *a, *b;
			T -> split(x - 1, a, b);
			printf("%d\n", a -> size + 1);
			T = merge(a, b);
		}

		else if(t == 4)
			printf("%d\n", T -> kth(x));

		else if(t == 5) {
			Treap *a, *b;
			T -> split(x - 1, a, b);
			printf("%d\n", a -> kth(a -> size));
			T = merge(a, b);
		}

		else if(t == 6) {
			Treap *a, *b;
			T -> split(x, a, b);
			printf("%d\n", b -> kth(1));
			T = merge(a, b);
		}
	}
}
