#if 0
By kewth.
Splay.
#else
#include <bits/stdc++.h>

char str[10000000]; // Make C happy.
class Splay {
private:
	char ch;
	bool rev, fuck[2];
	int size;
	Splay *son[2], *fa;
	void update();
	void push_down();
	void rotate();
public:
	Splay *Kth(int);
	Splay *splay(Splay *);
	Splay *insert(int, Splay *);
	Splay *erase(int, int);
	Splay *flip(int, int);
	Splay *range(int, int);
	int get_str(int);
	int get_ch();
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
	push_down();
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
	push_down();
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

Splay *Splay::flip(int l, int r) {
	splay(nullptr);
	Splay *L = Kth(l - 1) -> splay(nullptr);
	Splay *R = L -> Kth(r + 1) -> splay(L);
	R -> son[0] -> rev ^= 1;
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

int Splay::get_ch() { return ch; }

Splay::Splay(int l, int r): rev(false) {
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
#if 1
				getchar();
				for (int i = 0; i < n; ++i)
				{
					int ch = getchar();
					while (ch < 32 || ch > 126)
					{
						if (ch == 10 || ch == 13)
						{
							for (i = i; i < n; ++i)
								str[i] = 0;
							ch = 0;
							break;
						}
						ch = getchar();
					}
					str[i] = char(ch);
				}
				str[n] = '\0';
#else
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
#endif
				s = s -> insert(pos + 1, new Splay(0, n)) -> splay(nullptr);
					  } break;
			case 'D': {
				int n = input();
				s = s -> erase(pos + 2, pos + n + 1) -> splay(nullptr);
					  } break;
			case 'G': {
				s = s -> Kth(pos + 2) -> splay(nullptr);
				putchar(s -> get_ch());
				puts("");
					  } break;
			case 'P': pos --; break;
			case 'N': pos ++; break;
			case 'R': {
				int n = input();
				s = s -> flip(pos + 2, pos + n + 1) -> splay(nullptr);
					  } break;
			/* default: exit(13); */
		}
		/* s -> debug(); */
	}
}
#endif
