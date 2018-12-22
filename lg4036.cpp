// include files {{{1
#include <bits/stdc++.h>
#define nullptr NULL

// statement of splay {{{1
class Splay {
private:
	static const unsigned long long K = 27;
	class INFO {
	public:
		unsigned hash, mi, size;
		INFO operator + (INFO an) {
			INFO res(hash * an.mi + an.hash, mi * an.mi, size + an.size);
			return res;
		}
		void operator = (INFO an) {
			hash = an.hash;
			mi = an.mi;
			size = an.size;
		}
		INFO(unsigned long long hash, unsigned long long mi, unsigned long long size)
			: hash(hash), mi(mi), size(size) {
			}
	};
	Splay *fa, *son[2];
	void update();
	void rotate();
public:
	INFO self, info;
	Splay *splay(Splay *);
	Splay *insert(int, int);
	Splay *Kth(int);
	Splay *range(int, int);
	void debug();
	void changeto(int);
	Splay(int, Splay*);
	Splay();
};

// an empty node {{{1
Splay *const EMPTY = new Splay();

// update a node {{{1
void Splay::update() {
	info = son[0]->info + self + son[1]->info;
}

// rotate a node {{{1
void Splay::rotate() {
	if(not fa) return;
	bool id = fa->son[0] == this;
	Splay *const f = fa, *const p = fa->fa, *const s = son[id];
	if(p) p->son[p->son[1]==f] = this;
	f->son[id^1] = s;
	son[id] = f;
	s->fa = f;
	fa = p;
	f->fa = this;
	f->update();
	update();
}

// rotate a node to the top {{{1
Splay *Splay::splay(Splay *top) {
	while(fa != top)
		if(fa->fa == top)
			rotate();
		else if((fa->fa->son[0] == fa) == (fa->son[0] == this)) {
			fa->rotate();
			rotate();
		} else {
			rotate();
			rotate();
		}
	return this;
}

// insert a node into splay {{{1
Splay *Splay::insert(int k, int v) {
	Splay *res;
	if(k <= (int)son[0]->info.size)
		res = son[0]!=EMPTY ? son[0]->insert(k, v) : son[0] = new Splay(v, this);
	else
		res = son[1]!=EMPTY
			? son[1]->insert(k-son[0]->info.size-self.size, v)
			: son[1] = new Splay(v, this);
	update();
	return res;
}

// find the kth node {{{1
Splay *Splay::Kth(int k) {
	if(k == int(son[0]->info.size + self.size))
		return this;
	else if(k <= (int)son[0]->info.size)
		return son[0] -> Kth(k);
	else
		return son[1] -> Kth(k - son[0]->info.size - self.size);
}

// split a range in a splay {{{1
Splay *Splay::range(int l, int r) {
	Splay *top = Kth(l)->splay(nullptr);
	return top->Kth(r+2)->splay(top)->son[0];
}

// change the value of the node {{{1
void Splay::changeto(int v) {
	self.hash = v;
	update();
}

// debug function {{{1
void Splay::debug() {
	return;
	if(son[0] != EMPTY)
		son[0]->debug();
	std::cerr << char(self.hash + 'a')
		<< " size=" << info.size
		<< std::endl;
	if(son[1] != EMPTY)
		son[1]->debug();
}

// make a new node {{{1
Splay::Splay(int val, Splay *fa): fa(fa), self(val, K, 1), info(val, K, 1) {
	son[0] = son[1] = EMPTY;
}

// make a empty node {{{1
Splay::Splay(): self(0, 1, 0), info(0, 1, 0) {
	/* son[0] = son[1] = EMPTY; */
}

// Main Function {{{1
int main(const int, const char **) {
	/* freopen("data/a0.in", "r", stdin); */
	std::ios::sync_with_stdio(false);
	std::string s;
	int q;
	std::cin >> s >> q;
	Splay *S = new Splay(0, nullptr);
	for(unsigned int i=0;i<s.size();i++)
		S = S->insert(i+1, s[i] - 'a')->splay(nullptr);
	S = S->insert(s.size()+1, 0)->splay(nullptr);
	/* ; */
	/* S = S->range(9, 49); */
	/* ; */
	/* S = S->splay(nullptr); */
	/* ; */
	/* S = S->range(12, 52); */
	/* ; */
	/* S = S->splay(nullptr); */
	/* ; */
	while(q --) {
		char type;
		int x;
		std::cin >> type >> x;
		switch(type) {
			case 'Q': {
				int y;
				std::cin >> y;
				if(x > y) std::swap(x, y);
				int l = 0, r = S->info.size - y - 1;
				while(l < r) {
					int mid = (l + r + 1) >> 1;
					unsigned long long ll, rr;
					S = S->range(x, x+mid-1);
					ll = S->info.hash;
					S = S->splay(nullptr);
					S = S->range(y, y+mid-1);
					rr = S->info.hash;
					S = S->splay(nullptr);
					if(ll == rr)
						l = mid;
					else
						r = mid - 1;
				}
				std::cout << l << std::endl;
			} break;
			case 'R': {
				char c;
				std::cin >> c;
				S = S->Kth(x+1)->splay(nullptr);
				S->changeto(c-'a');
			} break;
			case 'I': {
				char c;
				std::cin >> c;
				S = S->insert(x+1, c-'a')->splay(nullptr);
			} break;
			case '\n': {
				std::cerr << "FUCK YOU!" << std::endl;
			} break;
		}
		S->debug();
	}
}

// {{{1

// }}}1
