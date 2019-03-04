#if 0
2019.03.03

链表神仙题。。。
相同高度且相邻的向日葵可以看做一个整体（合并）。
一天一天模拟，但是不能处理每个向日葵的生长（肯定会 T 啊），
而是只处理可能的发生的向日葵合并。
一个向日葵在与其他向日葵合并前的所有时候的高度都是可以确定的。
向日葵合并后由于左右节点发生变化需要更新信息并计算下次合并的时间。
说起来容易，有许多需要注意的细节，难打。

好 难 啊

好 。 难 。 啊

卧槽终于 A 了啊啊啊啊啊啊

#endif
#include <bits/stdc++.h>

int input() { int x; scanf("%d", &x); return x; }

struct list;
const int maxn = 300050;
int T;
int suma[maxn], sumb[maxn];
std::vector<list*> va[maxn], vb[maxn], vab[maxn];

struct list {
	int high, last, max, size;
	bool left, right;
	bool fuck[6];
	list *l, *r;
	int until() {
		return high + left * (suma[T] - suma[last])
				+ right * (sumb[T] - sumb[last]);
	}
	void update_side() {
		left = l and l -> until() > until();
		right = r and r -> until() > until();
	}
	void check() {
		/* update_side(); */
		/* r -> update_side(); */
		if(not r) return;
		if(r -> until() == until()) {
			merge();
			return;
		}
		if(not r) return;
		/* std::clog << "check " << until() << std::endl; */
		int cha = until() - r -> until();
		bool fa = (cha > 0) ^ left; // 玄学技巧
		bool fb = (cha < 0) ^ r -> right; // 玄学技巧
		cha = std::abs(cha);
		if(fa and fb) {
			int k = T + cha;
			if(k < maxn)
				vab[k].push_back(this);
			/* std::clog << high << " pushab " << k << std::endl; */
		} else if(fa) {
			int k = suma[T] + cha;
			if(k < maxn)
				va[k].push_back(this);
			/* std::clog << high << " pusha " << k << std::endl; */
		} else if(fb) {
			int k = sumb[T] + cha;
			if(k < maxn)
				vb[k].push_back(this);
			/* std::clog << high << " pushb " << k << std::endl; */
		}
	}
	void merge() {
		/* std::clog << "merge " << until() << std::endl; */
		// size == 0 的情况一定注意，可能一个节点在 merge 之前被另一节点 merge
		if(not size or not r or until() != r -> until()) return;
		size += r -> size;
		r -> size = 0;
		if(r -> r) r -> r -> l = this;
		r = r -> r;
		high = until();
		last = T;
		update_side();
		if(l) l -> check();
		check();
		/* std::clog << "merged " << until() << std::endl; */
	}
	list(int high):
		high(high), last(0), size(1), left(false), right(false),
		l(nullptr), r(nullptr) {}
};

int main() {
	int n = input(), time = input();
	list *start = new list(input()), *now = start;
	for(int i=1; i<n; i++) {
		now -> r = new list(input());
		now -> r -> l = now;
		now = now -> r;
	}
	for(now=start; now; now=now->r)
		now -> update_side();
	for(now=start; now; now=now->r)
		now -> check();
	std::string s;
	std::cin >> s;
	for(T=1; T<=time; T++) {
		suma[T] = suma[T - 1];
		sumb[T] = sumb[T - 1];
		if(s[ulong(T - 1)] == 'A') suma[T] ++;
		else sumb[T] ++;
		for(ulong i=0; i<va[suma[T]].size(); i++)
			va[suma[T]][i] -> merge();
		for(ulong i=0; i<vb[sumb[T]].size(); i++)
			vb[sumb[T]][i] -> merge();
		for(ulong i=0; i<vab[T].size(); i++)
			vab[T][i] -> merge();
		/* for(now=start; now; now=now->r) { */
		/* 	fprintf(stderr, "("); */
		/* 	for(int i=0; i<now->size; i++) */
		/* 		fprintf(stderr, "%d ", now -> until()); */
		/* 	fprintf(stderr, ")"); */
		/* } */
		/* fputs("\n", stderr); */
	}
	T --;
	for(now=start; now; now=now->r)
		for(int i=0; i<now->size; i++)
			printf("%d ", now -> until());
	puts("");
	/* for(now=start; now; now=now->r) */
	/* 	for(int i=0; i<now->size; i++) */
	/* 		fprintf(stderr, "%d ", now -> high); */
	/* puts(""); */
}
