#if 0
2019.08.18

卧槽，第一次写李超树竟然一遍过。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

struct Tree;
Tree* null;

struct Tree {
	int L, R;
	Tree *lt, *rt;
	double K, B;

	void insert(double k, double b) {
		if(this == null)
			return;
		int mid = (L + R) >> 1;
		if(k * mid + b > K * mid + B) {
			(k > K ? lt : rt) -> insert(K, B);
			K = k;
			B = b;
		} else
			(k > K ? rt : lt) -> insert(k, b);
	}

	double query(int x) {
		if(this == null or x > R or x < L)
			return 0;
		/* if(K or B) */
		/* 	debug("%lf * %d + %lf = %lf\n", K, x, B, K * x + B); */
		return std::max(K * x + B,
				std::max(lt -> query(x), rt -> query(x)));
	}

	Tree(int l, int r): L(l), R(r), K(0), B(0) {
		if(l < r) {
			int mid = (l + r) >> 1;
			lt = new Tree(l, mid);
			rt = new Tree(mid + 1, r);
		} else
			lt = rt = null;
	}
};

int main() {
	null = new Tree(0, 0);
	Tree T(1, 50000);

	int q = input();
	while(q --) {
		char str[10];
		scanf("%s", str);

		if(*str == 'P') {
			double s, p;
			scanf("%lf %lf", &s, &p);
			T.insert(p, s - p);

		} else if(*str == 'Q') {
			double ans = T.query(input());
			printf("%d\n", int(ans / 100));
			/* debug("%lf\n", ans); */
		}
	}
}
