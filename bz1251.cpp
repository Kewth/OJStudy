// include files {{{1
#include <bits/stdc++.h>

// statement of splay {{{1
class Splay {
private:
	Splay *son[2], *fa;
	void rotate();
	void update();
	void push_down();
public:
	long long val, size;
	long long max, flip, add;
	Splay *splay(Splay *);
	Splay *kth(int);
	Splay *range(int, int);
	Splay(int, Splay*);
	Splay();
};
Splay *EMPTY = new Splay();

// rotate a node {{{1
void Splay::rotate() {
	if(fa->fa) fa->fa->push_down();
	fa->push_down();
	push_down();
	bool id = fa->son[0] == this;
	Splay *const f = fa, *const p = fa->fa, *const s = son[id];
	if(p) p->son[p->son[1]==f] = this;
	f->son[!id] = s;
	son[id] = f;
	s->fa = f;
	fa = p;
	f->fa = this;
	f->update();
	update();
}

// update a node {{{1
void Splay::update() {
	max = std::max(son[0]->max, son[1]->max);
	max = std::max(max, val);
	/* max = val; */
	/* for(int i=0;i<2;i++) */
	/* 	max = std::max(max, son[i]->max + son[i]->add); */
	size = son[0]->size + son[1]->size + 1;
}

// push the lazy mark down {{{1
void Splay::push_down() {
	if(flip) {
		std::swap(son[0], son[1]);
		son[0]->flip ^= 1;
		son[1]->flip ^= 1;
		flip = 0;
	}
	son[0]->val += add;
	son[1]->val += add;
	son[0]->max += add;
	son[1]->max += add;
	son[0]->add += add;
	son[1]->add += add;
	add = 0;
}

// spaly a node {{{1
Splay *Splay::splay(Splay *top) {
	while(fa != top) {
		if(fa->fa == top)
			rotate();
		else if((fa->fa->son[0]==fa) == (fa->son[0]==this)) {
			fa->rotate();
			rotate();
		} else {
			rotate();
			rotate();
		}
	}
	return this;
}

// search the kth biggest node {{{1
Splay *Splay::kth(int k) {
	push_down();
	if(k <= son[0]->size)
		return son[0]->kth(k);
	else if(k <= son[0]->size + 1)
		return this;
	else
		return son[1]->kth(k - son[0]->size - 1);
}

// get a range {{{1
Splay *Splay::range(int l, int r) {
	Splay *L = kth(l-1)->splay(nullptr);
	Splay *R = L->kth(r+1)->splay(L);
	R->son[0]->push_down();
	return R->son[0];
}

// make a splay {{{1
Splay::Splay(int size, Splay * fa): fa(fa), val(0), size(0), max(0), flip(0), add(0) {
	son[0] = size > 1 ? new Splay(size>>1, this) : EMPTY;
	son[1] = size > 2 ? new Splay(size - (size>>1) - 1, this) : EMPTY;
	update();
}
Splay::Splay(): fa(nullptr), val(-1000000000000000000ll), size(0), max(-1000000000000000000ll), flip(0), add(0) {
	son[0] = son[1] = nullptr;
}

// Main function {{{1
int main(const int, const char **) {
	std::ios::sync_with_stdio(false);
	int n, q;
	std::cin >> n >> q;
	Splay *S = new Splay(n+2, nullptr);
	while(q --) {
		int type, l, r, v;
		std::cin >> type >> l >> r;
		S = S->range(l+1, r+1);
		switch(type) {
			case 1:
				std::cin >> v;
				S->val += v;
				S->max += v;
				S->add += v;
				break;
			case 2:
				S->flip ^= 1;
				break;
			case 3:
				std::cout << S->max << std::endl;
				break;
		}
		S = S->splay(nullptr);
	}
}

// }}}1
