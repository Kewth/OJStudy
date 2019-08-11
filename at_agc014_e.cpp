#if 0
2019.08.11

每次加红边删蓝边，相当于删掉蓝边后在分开的两个联通块中连一个红边。
考虑倒推，每次操作删红边连蓝边，也相当于删掉红边后在分开的两个联通块中连蓝边。
这提示了我们，蓝边和红边实际上是相互等价可以互换的，
换句话说，应该将蓝边和红边一起考虑而不是分开模拟。

于是就引出一个做法：
考虑倒推，一开始没有连边，每个点是单独的联通块，
每次找到两个联通块同时被蓝边与红边相连，将这两个红蓝边换成真实存在的边，
也就是将两个联通快合并成一个联通块，这个过程可以用并查集维护联通块，
用 set 加启发式合并维护存在的红边和蓝边。
如果最后合并成一个联通块答案就是 YES 。
#endif
#include <cstdio>
#include <set>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005;
int fa[maxn];
std::multiset<int> A[maxn], B[maxn];

int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++)
		fa[i] = i;
	for(int i = 1; i < n; i ++) {
		int x = input(), y = input();
		A[x].insert(y);
		A[y].insert(x);
	}
	std::queue<int> q1, q2;
	for(int i = 1; i < n; i ++) {
		int x = input(), y = input();
		if(A[x].count(y)) {
			q1.push(x);
			q2.push(y);
		}
		B[y].insert(x);
		B[x].insert(y);
	}
	int tot = 0;
	while(not q1.empty()) {
		tot ++;
		int x = find(q1.front()), y = find(q2.front());
#if 0
		debug("%d %d\n", x, y);
		for(int z : A[x])
			debug("%d in A[%d]\n", z, x);
		for(int z : A[y])
			debug("%d in A[%d]\n", z, y);
		for(int z : B[x])
			debug("%d in B[%d]\n", z, x);
		for(int z : B[y])
			debug("%d in B[%d]\n", z, y);
#endif
		q1.pop();
		q2.pop();
		A[x].erase(y);
		A[y].erase(x);
		B[x].erase(y);
		B[y].erase(x);
		bool rev = A[x].size() + B[x].size() > A[y].size() + B[y].size();
		if(rev)
			std::swap(x, y);
		fa[x] = y;
#if 0
		debug("%d %d\n", x, y);
		for(int z : A[x])
			debug("%d in A[%d]\n", z, x);
		for(int z : A[y])
			debug("%d in A[%d]\n", z, y);
		for(int z : B[x])
			debug("%d in B[%d]\n", z, x);
		for(int z : B[y])
			debug("%d in B[%d]\n", z, y);
#endif
		for(int z : A[x])
			if(B[y].count(z)) {
				q1.push(y);
				q2.push(z);
			}
		for(int z : B[x])
			if(A[y].count(z)) {
				q1.push(y);
				q2.push(z);
			}
		for(int z : A[x]) {
			A[y].insert(z);
			while(A[z].count(rev ? x : x)) {
				A[z].erase(A[z].find(x));
				A[z].insert(y);
			}
		}
		for(int z : B[x]) {
			B[y].insert(z);
			while(B[z].count(rev ? x : x)) {
				B[z].erase(B[z].find(x));
				B[z].insert(y);
			}
		}
	}
	if(tot == n - 1)
		puts("YES");
	else
		puts("NO");
}
