#include <bits/stdc++.h>

class Splay {
private:
	int val, size;
	int times, fuck;
	Splay *son[2], *fa;
	void update();
	void rotate();
public:
	Splay *splay(Splay *);
	Splay *insert(int);
	Splay *Kth(int);
	Splay *cut_left_son();
	int get_val();
	int get_size();
	Splay(int, Splay *);
};

void Splay::update() {
	size = times;
	if(son[0]) size += son[0] -> size;
	if(son[1]) size += son[1] -> size;
}

void Splay::rotate() {
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
	if(v == val) {
		times ++;
		update();
		return this;
	}
	Splay *res;
	bool id = v > val;
	if(son[id])
		res = son[id] -> insert(v);
	else
		res = son[id] = new Splay(v, this);
	update();
	return res;
}

Splay *Splay::Kth(int k) {
	int lsize = son[0] ? son[0] -> size : 0;
	if(k <= lsize)
		return son[0] -> Kth(k);
	else if(k <= lsize + times)
		return this;
	else if(k <= size)
		return son[1] -> Kth(k - lsize - times);
	return nullptr;
}

Splay *Splay::cut_left_son() {
	delete son[0];
	son[0] = nullptr;
	update();
	return this;
}

int Splay::get_val() { return val; }
int Splay::get_size() { return size; }

Splay::Splay(int val, Splay *fa): val(val), size(1), times(1), fa(fa)  {
	son[0] = son[1] = nullptr;
}

int input() {
	int res = 0, ch = getchar();
	while(ch < '0' or ch > '9') ch = getchar();
	while(ch >= '0' and ch <= '9')
		res = res * 10 + ch - '0', ch = getchar();
	return res;
}

int main() {
	int q = input(), m = input(), add = 0, inserted = 1;
	Splay *s = new Splay(INT_MAX >> 1, nullptr);
	while(q --) {
		char typ;
		int x;
		std::cin >> typ >> x;
		int l = 1, r = s -> get_size();
		switch(typ) {
			case 'I':
				if(x >= m) {
					s = s -> insert(x - add) -> splay(nullptr);
					inserted ++;
				}
				break;
			case 'A':
				add += x;
				break;
			case 'S':
				add -= x;
				while(l < r) {
					int mid = (l + r) >> 1;
					s = s -> Kth(mid) -> splay(nullptr);
					if(s -> get_val() + add >= m)
						r = mid;
					else
						l = mid + 1;
				}
				s = s -> Kth(l) -> splay(nullptr) -> cut_left_son();
				break;
			case 'F':
				if(x < s -> get_size()) {
					s = s -> Kth(s -> get_size() - x) -> splay(nullptr);
					printf("%d\n", s -> get_val() + add);
				} else
					puts("-1");
				break;
		}
	}
	printf("%d\n", inserted - s -> get_size());
}
