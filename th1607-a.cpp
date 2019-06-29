#if 0
2019.06.28

首先有一个结论：选 x + 1 一定有一个最优方案是下面两种情况之一：
(1) 从选 x 的最优方案中再选一个。
(2) 把选 x 的最优方案的某一段翻转（选变为不选，不选变为选）

那么用堆维护最大的点，每次选了一个点 i 后把 i-1, i, i+1 合并成一个，
因为在 i 翻转前 i-1 和 i+1 不能选，而翻转后 i-1 和 i+1 一定得选，
那么把新点的贡献设为翻转 i 后的变化，即 a[i-1] + a[i+1] - a[i] 。
换点的过程用链表维护即可。
#endif
#include <cstdio>
#include <queue>
#include <vector>

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 200005;
struct Candy {
	lolong val;
	Candy *left, *right;
	bool erased;
	bool fuck[7];
	inline void erase() {
		if(left) left -> right = right;
		if(right) right -> left = left;
		erased = true;
	}
};
typedef std::pair<lolong, Candy*> Element;

int main() {
	std::priority_queue<Element> q;
	int n = input();
	Candy *last = nullptr;
	while(n --) {
		Candy *c = new Candy;
		c -> left = last;
		if(last) last -> right = c;
		last = c;
		c -> val = input();
		c -> erased = false;
		q.push(Element(c -> val, c));
	}
	std::vector<lolong> ans;
	ans.push_back(0);
	while(not q.empty()) {
		Candy *c = q.top().second;
		q.pop();
		if(c -> erased) continue;
		ans.push_back(*(ans.end() - 1) + c -> val);
		if(c -> left and c -> right) {
			c -> val = c -> left -> val + c -> right -> val - c -> val;
			c -> left -> erase();
			c -> right -> erase();
			q.push(Element(c -> val, c));
		} else {
			if(c -> left) c -> left -> erase();
			if(c -> right) c -> right -> erase();
			c -> erase();
		}
	}
	n = input();
	while(n --)
		printf("%lld\n", ans[size_t(input())]);
}
