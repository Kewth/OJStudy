#include <climits>
#include <algorithm>
#include <iostream>
/* #include <bits/stdc++.h> */

int input() {{{
	int res;
	scanf("%d", &res);
	return res;
}}}

class Splay { // {{{
private:
	int val, real;
	int lazy_chage, lazy_rev;
	Splay *son[2], *fa;
	void rotate();
	void update();
	void push_down();
public:
	int sum, size, max_sum[3];
	int fuck;
	Splay *splay(Splay *);
	Splay *insert(int, Splay *);
	Splay *range(int, int);
	Splay *Kth(int);
	Splay *change_to(int, int, int);
	Splay *flip(int, int);
	Splay *erase(int, int);
	Splay(int, Splay *);
	~Splay();
	friend Splay *build(int, int*, Splay*);
	void debug(int deep=0) {
		if(son[0])
			son[0] -> debug(deep + 1);
		for(int i=0; i<deep; i++)
			fputs(" ", stderr);
		fprintf(stderr, "val%d sum%d size%d {%d, %d, %d}",
				val, sum, size, max_sum[0], max_sum[1], max_sum[2]);
		if(lazy_chage != INT_MAX)
			fprintf(stderr, " change%d", lazy_chage);
		if(lazy_rev)
			fprintf(stderr, " (REV)");
		if(not real)
			fprintf(stderr, " !!!!!!");
		fputs("\n", stderr);
		if(son[1])
			son[1] -> debug(deep + 1);
		if(not deep)
			fputs("\n", stderr);
	}
}; // }}}

void Splay::rotate() {{{
	fa -> push_down();
	this -> push_down();
	bool id = fa -> son[0] == this;
	Splay *const p = fa -> fa, *const f = fa,
		*const s = son[id];
	if(s) s -> push_down();
	if(s) s -> fa = f;
	this -> fa = p;
	f -> fa = this;
	if(p) p -> son[p -> son[1] == f] = this;
	f -> son[id ^ 1] = s;
	this -> son[id] = f;
	f -> update();
	this -> update();
}}}

void Splay::update() {{{
	push_down();
	if(son[0]) son[0] -> push_down();
	if(son[1]) son[1] -> push_down();
	sum = val;
	size = real;
	for(int i=0; i<3; i++)
		max_sum[i] = INT_MIN;
	int side = val;
	for(int i=0; i<2; i++) {
		int another = val;
		if(son[i]) {
			sum += son[i] -> sum;
			size += son[i] -> size;
			if(son[i] -> max_sum[i ^ 1] > 0)
				side += son[i] -> max_sum[i ^ 1];
			max_sum[2] = std::max(son[i] -> max_sum[2], max_sum[2]);
			max_sum[i] = son[i] -> max_sum[i];
			another += son[i] -> sum;
		}
		if(son[i ^ 1] and son[i ^ 1] -> max_sum[i] > 0)
			another += son[i ^ 1] -> max_sum[i];
		if(another > max_sum[i])
			max_sum[i] = another;
	}
	max_sum[2] = std::max(side, max_sum[2]);
}}}

void Splay::push_down() {{{
	if(lazy_chage != INT_MAX) {
		val = lazy_chage;
		if(son[0]) son[0] -> lazy_chage = lazy_chage;
		if(son[1]) son[1] -> lazy_chage = lazy_chage;
		lazy_chage = INT_MAX;
		sum = size * val;
		if(val > 0)
			for(int i=0; i<3; i++)
				max_sum[i] = sum;
		else
			for(int i=0; i<3; i++)
				max_sum[i] = val;
	}
	if(lazy_rev) {
		std::swap(son[0], son[1]);
		if(son[0]) son[0] -> lazy_rev ^= 1;
		if(son[1]) son[1] -> lazy_rev ^= 1;
		lazy_rev = 0;
		std::swap(max_sum[0], max_sum[1]);
	}
}}}

Splay *Splay::splay(Splay *top) {{{
	while(fa != top) {
		if(fa -> fa == top)
			rotate();
		else if((fa -> fa -> son[0] == fa) ==
				(fa -> son[0] == this)) {
			fa -> rotate();
			rotate();
		} else {
			rotate();
			rotate();
		}
	}
	return this;
}}}

Splay *Splay::insert(int k, Splay *s) {{{
	push_down();
	int lsize = son[0] ? son[0] -> size : 0;
	bool id = k > lsize;
	Splay *res;
	if(son[id])
		res = son[id] -> insert(k - id * (lsize + real), s);
	else {
		res = son[id] = s;
		s -> fa = this;
	}
	update();
	return res;
}}}

Splay *Splay::range(int l, int r) {{{
	splay(nullptr);
	Splay *L = Kth(l - 1) -> splay(nullptr);
	Splay *R = L -> Kth(r + 1) -> splay(L);
	R -> push_down();
	return R -> son[0];
}}}

Splay *Splay::Kth(int k) {{{
	push_down();
	int lsize = son[0] ? son[0] -> size : 0;
	if(k <= lsize)
		return son[0] -> Kth(k);
	if(k == lsize + real)
		return this;
	if(k <= size)
		return son[1] -> Kth(k - lsize - real);
	exit(2);
}}}

Splay *Splay::change_to(int l, int r, int v) {{{
	splay(nullptr);
	Splay *L = Kth(l - 1) -> splay(nullptr);
	Splay *R = L -> Kth(r + 1) -> splay(L);
	R -> push_down();
	R -> son[0] -> lazy_chage = v;
	R -> son[0] -> push_down();
	R -> update();
	L -> update();
	return L;
}}}

Splay *Splay::flip(int l, int r) {{{
	splay(nullptr);
	Splay *L = Kth(l - 1) -> splay(nullptr);
	Splay *R = L -> Kth(r + 1) -> splay(L);
	R -> push_down();
	R -> son[0] -> lazy_rev ^= 1;
	R -> son[0] -> push_down();
	R -> update();
	L -> update();
	return L;
}}}

Splay *Splay::erase(int l, int r) {{{
	splay(nullptr);
	Splay *L = Kth(l - 1) -> splay(nullptr);
	Splay *R = L -> Kth(r + 1) -> splay(L);
	R -> push_down();
	delete R -> son[0];
	R -> son[0] = nullptr;
	R -> update();
	L -> update();
	return L;
}}}

Splay::Splay(int val, Splay *fa): // {{{
	val(val), real(1), lazy_chage(INT_MAX), lazy_rev(0), fa(fa) {
	son[0] = son[1] = nullptr;
	update();
}

Splay::~Splay() {
	if(son[0]) delete son[0];
	if(son[1]) delete son[1];
} // }}}

Splay *build(int n, int *a, Splay *fa) {{{
	if(not n) return nullptr;
	int mid = n >> 1;
	Splay *m = new Splay(a[mid], fa);
	m -> son[0] = build(mid, a, m);
	m -> son[1] = build(n - mid - 1, a + mid + 1, m);
	m -> update();
	return m;
}}}

// {{{
Splay *s;
void INSERT() {
	int pos = input() + 1, m = input();
	if(m == 0)
		return;
	 int *a = new int [uint(m)];
	 for(int i=0; i<m; i++)
		 a[i] = input();
	 s = s -> insert(pos, build(m, a, nullptr)) -> splay(nullptr);
	/* s -> debug(); */
}
void DELETE() {
	int pos = input() + 1, m = input();
	if(m == 0)
		return;
	s = s -> erase(pos, pos + m - 1);
	/* s -> debug(); */
}
void MAKE_SAME() {
	int pos = input() + 1, m = input(), x = input();
	if(m == 0)
		return;
	s = s -> change_to(pos, pos + m - 1, x);
	/* s -> debug(); */
}
void REVERSE() {
	int pos = input() + 1, m = input();
	if(m == 0)
		return;
	s = s -> flip(pos, pos + m - 1);
	/* s -> debug(); */
}
void GET_SUM() {
	int pos = input() + 1, m = input();
	if(m == 0) {
		puts("0");
		return;
	}
	Splay *r = s -> range(pos, pos + m - 1);
	std::cout << r -> sum << std::endl;
	s = r -> splay(nullptr);
	/* s -> debug(); */
}
void MAX_SUM() {
	printf("%d\n", s -> max_sum[2]);
}
// }}}

int main() {{{
	int n = input(), q = input();
	int *a = new int[uint(n + 2)];
	a[n + 1] = a[0] = INT_MIN >> 1;
	for(int i=1; i<=n; i++)
		a[i] = input();
	s = build(n + 2, a, nullptr);
	delete[] a;
	while(q --) {
		char typ[10];
		scanf("%s", typ);
		if(typ[0] == 'I')
			INSERT();
		else if(typ[0] == 'D')
			DELETE();
		else if(typ[2] == 'K')
			MAKE_SAME();
		else if(typ[0] == 'R')
			REVERSE();
		else if(typ[0] == 'G')
			GET_SUM();
		else if(typ[2] == 'X')
			MAX_SUM();
		else
			exit(3);
	}
	delete s;
}}}
