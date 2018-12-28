// include files {{{1
#include <bits/stdc++.h>
// 该死的兼容
#define nullptr NULL
#define private public

// statement of splay {{{1
class Splay_manage;
class Splay {
private:
	int val, size, times;
	Splay *son[2], *fa;
	void update();
	void rotate();
public:
	Splay *splay(Splay *);
	Splay *insert(int);
	Splay *find(int);
	Splay *kth(int);
	Splay(int, Splay*);
	Splay();
	/* friend Splay_manage; */
};
Splay *EMPTY = new Splay();

// statement of Splay's manage {{{1
class Splay_manage {
private:
	Splay *m_top;
public:
	void insert(int);
	void erase(int);
	int rank(int);
	int kth(int);
	int search_small(int);
	int search_big(int);
	Splay_manage();
};

// update a node {{{1
void Splay::update() {
	size = son[0]->size + times + son[1]->size;
	for(int i=0;i<2;i++)
		if(not son[i]->times and son[i] != EMPTY
				and son[i]->son[0] == EMPTY and son[i]->son[1] == EMPTY)
			son[i] = EMPTY;
}

// rotate a node {{{1
void Splay::rotate() {
	bool id = fa->son[0] == this;
	Splay *const f = fa, *const p = fa->fa, *const s = son[id];
	if(p) p->son[p->son[1]==f] = this;
	f->son[id^1] = s;
	son[id] = f;
	s->fa = f;
	f->fa = this;
	fa = p;
	f->update();
	update();
}

// splay a node {{{1
Splay* Splay::splay(Splay *top) {
	while(fa != top)
		if(fa->fa == top) rotate();
		else if((fa->fa->son[0]==fa) == (fa->son[0]==this)) {
			fa->rotate();
			rotate();
		} else {
			rotate();
			rotate();
		}
	return this;
}

// insert a node into splay {{{1
Splay *Splay::insert(int v) {
	Splay *res;
	if(v < val)
		res = son[0]==EMPTY ? son[0] = new Splay(v, this) : son[0]->insert(v);
	else if(v == val) {
		times ++;
		res = this;
	} else
		res = son[1]==EMPTY ? son[1] = new Splay(v, this) : son[1]->insert(v);
	update();
	return res;
}

void Splay_manage::insert(int v) {
	m_top = m_top->insert(v);
	m_top->splay(nullptr);
}

// find a node in a splay {{{1
Splay *Splay::find(int v) {
	if(v < val)
		return son[0]==EMPTY ? nullptr : son[0]->find(v);
	else if(v == val)
		return times ? this : nullptr;
	else
		return son[1]==EMPTY ? nullptr : son[1]->find(v);
}

// erase a node {{{1
void Splay_manage::erase(int v) {
	Splay *s = m_top->find(v);
	if(s) {
		m_top = s->splay(nullptr);
		s->times --;
		s->update();
	}
}

// get the rank of a node {{{1
int Splay_manage::rank(int v) {
	Splay *s = m_top->find(v);
	if(s) {
		m_top = s->splay(nullptr);
		return m_top->son[0]->size;
	} else
		return -1;
}

// find the kth node {{{1
Splay *Splay::kth(int k) {
	if(k <= son[0]->size)
		return son[0]->kth(k);
	else if(k <= son[0]->size + times)
		return this;
	else if(k <= size)
		return son[1]->kth(k - son[0]->size - times);
	else
		return nullptr;
}

int Splay_manage::kth(int k) {
	Splay *s = m_top->kth(k + 1);
	if(s) {
		m_top = s->splay(nullptr);
		return m_top->val;
	} else
		return -1;
}

// search the smaller node {{{1
int Splay_manage::search_small(int v) {
	insert(v);
	int res = -1;
	for(Splay *s=m_top->son[0];s!=EMPTY;) {
		if(s->son[1] == EMPTY) {
			if(not s->times) {
				s = s->son[0];
				continue;
			}
			else
				res = s->val;
		}
		s = s->son[1];
	}
	erase(v);
	return res;
}

// search the bigger node {{{1
int Splay_manage::search_big(int v) {
	insert(v);
	int res = -1;
	for(Splay *s=m_top->son[1];s!=EMPTY;) {
		if(s->son[0] == EMPTY) {
			if(not s->times) {
				s = s->son[1];
				continue;
			}
			else
				res = s->val;
		}
		s = s->son[0];
	}
	erase(v);
	return res;
}

// Make a node {{{1
Splay::Splay(int v, Splay *f): val(v), size(1), times(1), fa(f) {
	son[0] = son[1] = EMPTY;
}

Splay::Splay(): val(-2100000000), size(0), times(0), fa(nullptr) {
	son[0] = son[1] = nullptr;
}

// create a manage of splay {{{1
Splay_manage::Splay_manage(): m_top(new Splay(-2100000000, nullptr)) {
}

// Main function {{{1
int main(const int, const char **) {
	std::ios::sync_with_stdio(false);
	int q;
	std::cin >> q;
	Splay_manage S;
	while(q --) {
		int type, x;
		std::cin >> type >> x;
		switch(type) {
			case 1: S.insert(x); break;
			case 2: S.erase(x); break;
			case 3: std::cout << S.rank(x) << std::endl; break;
			case 4: std::cout << S.kth(x) << std::endl; break;
			case 5: std::cout << S.search_small(x) << std::endl; break;
			case 6: std::cout << S.search_big(x) << std::endl; break;
		}
	}
}
// {{{1
// END
// }}}1
