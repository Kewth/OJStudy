#include <bits/stdc++.h>

class Splay {
private:
	int val, sum;
	bool rev;
	Splay *son[2], *fa;
	void update();
	void rotate();
	void push_down();
public:
	Splay *find_top();
	void access();
	void set_root();
	Splay *splay(Splay *);
	int get_sum(int);
	void set_val(int);
	void link_to(Splay *);
	bool cut(bool);
	bool has_son(bool);
	Splay(int, Splay *);
	/* void debug(); */
	/* int debug_id; */
};

void Splay::update() { // {{{1
	sum = val;
	if(son[0]) sum ^= son[0]->sum;
	if(son[1]) sum ^= son[1]->sum;
}

void Splay::rotate() { // {{{1
	fa -> push_down();
	this -> push_down();
	bool id = fa->son[0] == this;
	Splay *const p = fa->fa, *const f = fa, *const s = son[id];
	// set son
	if(p and p -> son[1] == f)
		p -> son[1] = this;
	if(p and p -> son[0] == f)
		p -> son[0] = this;
	f -> son[id ^ 1] = s;
	this -> son[id] = f;
	// set fa
	f -> fa = this;
	this -> fa = p;
	if(s) s -> fa = f;
	// update
	f -> update();
	this -> update();
}

void Splay::push_down() { // {{{1
	if(rev) {
		std::swap(son[0], son[1]);
		if(son[0]) son[0] -> rev ^= 1;
		if(son[1]) son[1] -> rev ^= 1;
		rev = false;
	}
}

Splay *Splay::find_top() { // {{{1
	Splay *res = this;
	while(res -> fa and
			(res -> fa -> son[0] == res or res -> fa -> son[1] == res))
		res = res -> fa;
	return res;
}

void Splay::access() { // {{{1
	for(Splay *now=this, *last=nullptr;
			now; last=now, now=now->fa) {
		now -> splay(now -> find_top() -> fa);
		now -> push_down();
		now -> son[1] = last;
		now -> update();
	}
}

void Splay::set_root() { // {{{1
	access();
	splay(nullptr);
	rev ^= 1;
}

Splay *Splay::splay(Splay *top) { // {{{1
	while(fa != top)
		if(fa -> fa == top)
			rotate();
		else if((fa -> fa -> son[1] == fa)
				== (fa -> son[1] == this)) {
			fa -> rotate();
			rotate();
		} else {
			rotate();
			rotate();
		}
	return this;
}

int Splay::get_sum(int id) { // {{{1
	if(id == -1)
		return sum;
	else
		return son[id] ? son[id] -> sum : 0;
}

void Splay::set_val(int v) { // {{{1
	access();
	splay(nullptr);
	val = v;
	update();
}

void Splay::link_to(Splay *s) { // {{{1
	set_root();
	s -> access();
	splay(nullptr);
	if(s -> find_top() != this)
		fa = s;
}

bool Splay::cut(bool id) { // {{{1
	push_down();
	if(not son[id])
		return false;
	son[id] -> fa = nullptr;
	son[id] = nullptr;
	update();
	return true;
}

bool Splay::has_son(bool id) {
	push_down();
	return son[id];
}

Splay::Splay(int val, Splay *fa): // {{{1
	val(val), sum(val), rev(false), fa(fa) {
	son[0] = son[1] = nullptr;
}

/* void Splay::debug() { // {{{ */
/* 	if(son[0]) */
/* 		son[0] -> debug(); */
/* 	std::cerr << debug_id << ' '; */
/* 	if(son[1]) */
/* 		son[1] -> debug(); */
/* } */

int main() { // {{{1
	int n, q;
	std::cin >> n >> q;
	const int N = n;
	Splay *S[N + 1];
	for(int i=1; i<=n; i++) {
		int x;
		std::cin >> x;
		S[i] = new Splay(x, nullptr);
	}
	while(q --) {
		int type, x, y, ans = 0;
		std::cin >> type >> x >> y;
		/* std::cerr << type << x << y << std::endl; */
		switch(type) {
			case 0:
				if(x == y) {
					ans = S[x] -> get_sum(-1);
					ans ^= S[x] -> get_sum(0);
					ans ^= S[x] -> get_sum(1);
				} else {
					S[x] -> set_root();
					S[y] -> access();
					S[x] -> splay(nullptr);
					S[y] -> splay(S[x]);
					ans ^= S[x] -> get_sum(-1);
					ans ^= S[y] -> get_sum(1);
				}
				std::cout << ans << std::endl;
				break;
			case 1:
				S[x] -> link_to(S[y]);
				break;
			case 2:
				if(x == y)
					break;
				S[x] -> set_root();
				S[y] -> access();
				S[x] -> splay(nullptr);
				if(S[y] -> find_top() == S[x]) {
					S[y] -> splay(S[x]);
					if(not S[y] -> has_son(0))
						S[x] -> cut(1);
				}
				break;
			case 3:
				S[x] -> set_val(y);
				break;
		}
		/* for(int i=1; i<=n; i++) { */
		/* 	S[i] -> debug_id = i; */
		/* 	S[i] -> debug(); */
		/* 	std::cerr << std::endl; */
		/* } */
		/* system("sleep 100"); */
	}
}
