#if 0
By kewth.
BZOJ 1507.
Splay.
#else
#include <bits/stdc++.h>

char str[10000000]; // Make C happy.
class Splay {
private:
	char ch;
	bool fuck[3];
	int size;
	Splay *son[2], *fa;
	void update();
	void rotate();
	Splay *Kth(int);
public:
	Splay *splay(Splay *);
	Splay *insert(int, Splay *);
	Splay *erase(int, int);
	Splay *range(int, int);
	int get_str(int);
	void debug(int deep = 0) {
		if(not deep) {
			int len = get_str(0);
			str[len] = '\n';
			str[len + 1] = '\0';
			fputs(str, stderr);
		}
		if(son[0]) son[0] -> debug(deep + 1);
		for(int i=0; i<deep; i++)
			fputs(" ", stderr);
		fprintf(stderr, "ch(%c) size(%d)\n", ch, size);
		if(son[1]) son[1] -> debug(deep + 1);
	}
	Splay(int, int);
};

void Splay::update() {
	size = 1;
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

Splay *Splay::Kth(int k) {
	int lsize = son[0] ? son[0] -> size : 0;
	if(k <= lsize)
		return son[0] -> Kth(k);
	else if(k <= lsize + 1)
		return this;
	else if(k <= size)
		return son[1] -> Kth(k - lsize - 1);
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

Splay *Splay::insert(int p, Splay *s) {
	int lsize = son[0] ? son[0] -> size : 0;
	bool id = p > lsize;
	if(p > size) exit(14);
	if(son[id])
		son[id] -> insert(p - id * (lsize + 1), s);
	else {
		son[id] = s;
		s -> fa = this;
	}
	update();
	return s;
}

Splay *Splay::erase(int l, int r) {
	splay(nullptr);
	Splay *L = Kth(l - 1) -> splay(nullptr);
	Splay *R = L -> Kth(r + 1) -> splay(L);
	delete R -> son[0];
	R -> son[0] = nullptr;
	R -> update();
	L -> update();
	return L;
}

Splay *Splay::range(int l, int r) {
	splay(nullptr);
	Splay *L = Kth(l - 1) -> splay(nullptr);
	Splay *R = L -> Kth(r + 1) -> splay(L);
	return R -> son[0];
}

int Splay::get_str(int p) {
	int now = p + (son[0] ? son[0] -> get_str(p) : 0);
	str[now ++] = ch;
	now += son[1] ? son[1] -> get_str(now) : 0;
	return now - p;
}

Splay::Splay(int l, int r) {
	/* fprintf(stderr, "build %d-%d\n", l, r); */
	int mid = (l + r) >> 1;
	if(l < mid) {
		son[0] = new Splay(l, mid);
		son[0] -> fa = this;
	} else
		son[0] = nullptr;
	ch = str[mid];
	if(mid + 1 < r) {
		son[1] = new Splay(mid + 1, r);
		son[1] -> fa = this;
	} else
		son[1] = nullptr;
	update();
}

int input() {
	int res;
	scanf("%d", &res);
	return res;
}

int main() {
	int q = input(), pos = 0;
	str[0] = '!';
	str[1] = '!';
	Splay *s = new Splay(0, 2);
	/* s -> debug(); */
	while(q --) {
		scanf("%s", str);
		switch(str[0]) {
			case 'M': {
				pos = input();
					  } break;
			case 'I': {
				int n = input();
				for(int i=0; i<n; i++)
					do
						str[i] = char(getchar());
					while(str[i] < 32 or str[i] > 126);
				str[n] = '\0';
				/* fputs(str, stderr); */
				/* fputs("  < insert\n", stderr); */
				/* Splay *in = new Splay(0, n); */
				/* in -> debug(); */
				/* delete in; */
				s = s -> insert(pos + 1, new Splay(0, n)) -> splay(nullptr);
					  } break;
			case 'D': {
				int n = input();
				s = s -> erase(pos + 2, pos + n + 1) -> splay(nullptr);
					  } break;
			case 'G': {
				int n = input();
				Splay *now = s -> range(pos + 2, pos + n + 1);
				int len = now -> get_str(0);
				str[len] = '\0';
				puts(str);
				fflush(stdout);
				s = now -> splay(nullptr);
					  } break;
			case 'P': pos --; break;
			case 'N': pos ++; break;
			default: exit(13);
		}
		/* s -> debug(); */
	}
}
#endif
