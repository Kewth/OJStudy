#if 0
2019.03.04

一开始以为是二分，
后来发现不满足单调性，又以为是线段树，
又发现线段树维护不了，才发觉是 Splay 。

先按分数排一遍序，从大到小枚举中间的奶牛，
对于该奶牛，为了保证它是中位数，要在它左边选一半，在右边选一半，
然后希望代价最小（序列中最小的 n / 2 个数的和），
用 2 颗 Splay 维护其左边和右边的所有奶牛的最小代价即可。

#endif
#define NDEBUG
#include <bits/stdc++.h>

int input() { int x; scanf("%d", &x); return x; }

class Splay {
private:
	int val, sum;
	int times, size;
	Splay *son[2], *fa;
	void update();
	void rotate();
	Splay *Kth(int);
public:
	Splay *splay(Splay *);
	Splay *insert(int);
	Splay *range(int, int);
	Splay *find(int);
	Splay *erase();
	int get_sum();
	Splay(int, Splay*);
};

void Splay::update() {
	size = times;
	sum = val * times;
	if(son[0]) {
		size += son[0] -> size;
		sum += son[0] -> sum;
	}
	if(son[1]) {
		size += son[1] -> size;
		sum += son[1] -> sum;
	}
}

void Splay::rotate() {
	assert(fa);
	bool id = fa -> son[0] == this;
	Splay *const p = fa -> fa, *const f = fa, *const s = son[id];
	if(p) p -> son[p -> son[1] == f] = this;
	f -> son[! id] = s;
	this -> son[id] = f;
	if(s) s -> fa = f;
	this -> fa = p;
	f -> fa = this;
	f -> update();
	this -> update();
}

Splay *Splay::Kth(int k) {
	int lsize = son[0] ? son[0] -> size : 0;
	assert(k > 0);
	if(k <= lsize) return son[0] -> Kth(k);
	if(k <= lsize + times) return this;
	if(k <= size) return son[1] -> Kth(k - lsize - times);
	exit(13);
}

Splay *Splay::splay(Splay *top) {
	while(fa != top) {
		assert(fa);
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
	Splay *res;
	bool id = v > val;
	res = son[id] ? son[id] -> insert(v) : son[id] = new Splay(v, this);
	update();
	assert(res);
	return res;
}

Splay *Splay::range(int l, int r) {
	splay(nullptr);
	Splay *L = Kth(l - 1) -> splay(nullptr);
	assert(L);
	Splay *R = L -> Kth(r + 1) -> splay(L);
	assert(R);
	return R -> son[0];
}

Splay *Splay::find(int v) {
	if(v == val) return this;
	bool id = v > val;
	assert(son[id]);
	return son[id] -> find(v);
}

Splay *Splay::erase() {
	assert(times); // 这里可能会失败，暂时没找出原因
	times --;
	update();
	return this;
}

int Splay::get_sum() {
	return sum;
}

Splay::Splay(int val, Splay *fa):
	val(val), sum(val), times(1), size(1), fa(fa) {
		son[0] = son[1] = nullptr;
	}

const int maxn = 100050;
typedef std::pair<int, int> par;
par cow[maxn], tmp[maxn];

int main() {
	using std::clog;
	using std::endl;
	int n = input() >> 1, m = input(), mon = input();
	for(int i=0; i<m; i++) {
		cow[i].first = input();
		cow[i].second = input();
	}
	std::sort(cow, cow + m);
	Splay *left = (new Splay(INT_MIN >> 2, nullptr)) ->
		insert(INT_MAX >> 2) -> splay(nullptr);
	Splay *right = (new Splay(INT_MIN >> 2, nullptr)) ->
		insert(INT_MAX >> 2) -> splay(nullptr);
	for(int i=0; i<m-n; i++)
		left = left -> insert(cow[i].second) -> splay(nullptr);
	for(int i=m-n+1; i<m; i++)
		right = right -> insert(cow[i].second) -> splay(nullptr);
	for(int i=m-n-1; i>=n; i--) {
		assert(left);
		assert(right);
		right = right -> insert(cow[i + 1].second) -> splay(nullptr);
		left = left -> find(cow[i].second) -> splay(nullptr) -> erase();
		assert(left);
		assert(right);
		left = left -> range(2, n + 1);
		right = right -> range(2, n + 1);
		assert(left);
		assert(right);
		int now = left -> get_sum() + right -> get_sum() + cow[i].second;
		/* clog << left -> get_sum() << ' ' */
		/* 	<< cow[i].second << ' ' */
		/* 	<< right -> get_sum() << endl; */
		if(now <= mon) {
			printf("%d\n", cow[i].first);
			return 0;
		}
		left = left -> splay(nullptr);
		right = right -> splay(nullptr);
	}
	puts("-1");
}
