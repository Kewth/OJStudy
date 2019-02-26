#include <bits/stdc++.h>

class Splay {
private:
	int val;
	int size;
	bool rev;
	bool fuck[7];
	Splay *son[2], *fa;
	void update();
	void push_down();
	void rotate();
	Splay *Kth(int);
public:
	Splay *splay(Splay *);
	Splay *insert(int);
	int lsize();
	int get_val();
	Splay *flip(int, int);
	Splay(int, Splay *);
};

void Splay::update() {
	size = 1;
	if(son[0]) size += son[0] -> size;
	if(son[1]) size += son[1] -> size;
}

void Splay::push_down() {
	if(rev) {
		std::swap(son[0], son[1]);
		if(son[0]) son[0] -> rev ^= 1;
		if(son[1]) son[1] -> rev ^= 1;
		rev = false;
	}
}

void Splay::rotate() {
	fa -> push_down();
	this -> push_down();
	bool id = fa -> son[0] == this;
	Splay *const f = fa, *const p = fa -> fa, *const s = son[id];
	if(p) p -> son[p -> son[1] == f] = this;
	f -> son[id ^ 1] = s;
	this -> son[id] = f;
	if(s) s -> fa = f;
	this -> fa = p;
	f -> fa = this;
	f -> update();
	this -> update();
}

Splay *Splay::Kth(int k) {
	push_down();
	if(k <= lsize())
		return son[0] -> Kth(k);
	else if(k <= lsize() + 1)
		return this;
	else if(k <= size)
		return son[1] -> Kth(k - lsize() - 1);
	else
		exit(13);
}

Splay *Splay::splay(Splay *top) {
	while(fa != top) {
		if(fa -> fa == top)
			rotate();
		else if((fa -> fa -> son[0] == fa) == (fa -> son[0] == this)) {
			fa -> rotate();
			rotate();
		} else {
			rotate();
			rotate();
		}
	}
	return this;
}

Splay *Splay::insert(int v) {
	push_down();
	Splay *res;
	if(son[1]) res = son[1] -> insert(v);
	else res = son[1] = new Splay(v, this);
	update();
	return res;
}

int Splay::lsize() { push_down(); return son[0] ? son[0] -> size : 0; }
int Splay::get_val() { return val; }

Splay *Splay::flip(int l, int r) {
	splay(nullptr);
	Splay *L = Kth(l - 1) -> splay(nullptr);
	Splay *R = L -> Kth(r + 1) -> splay(L);
	R -> son[0] -> rev ^= 1;
	return L;
}

Splay::Splay(int val, Splay *fa): val(val), size(1), rev(false), fa(fa) {
	son[0] = son[1] = nullptr;
}

int input() { int res; scanf("%d", &res); return res; }

const int maxn = 100050;
typedef std::pair<Splay *, int> par;
par todo[maxn];

bool cmp(par x, par y) {
	if(x.first -> get_val() == y.first -> get_val())
		return x.second < y.second;
	return x.first -> get_val() < y.first -> get_val();
}

int main() {
	int n = input();
	Splay *s = new Splay(0, nullptr);
	for(int i=1; i<=n; i++) {
		int x = input();
		s = s -> insert(x) -> splay(nullptr);
		todo[i] = par(s, i);
	}
	s = s -> insert(0);
	std::sort(todo + 1, todo + n + 1, cmp);
	for(int i=1; i<=n; i++) {
		s = todo[i].first -> splay(nullptr);
		printf("%d ", s -> lsize());
		s = s -> flip(i + 1, s -> lsize() + 1);
	}
}
