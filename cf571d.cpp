#if 0
2020.01.30

离线，对于大学和警卫分别建两个相互独立的森林，
建立规则类似于 kruskal 重构树，每次合并就建新点然后连左右儿子。
然后把修改操作挂在当时对应的根上，记录时间。
询问操作挂在两棵树的叶子上，同样记录时间。

离线处理，先处理警卫对应的森林，求出每个询问对应上一个清零的时间。
只需开一个 set 记录哪些时间点被清零了，在 dfs 前 insert ，dfs 后 erase 即可，
这样到每个叶子就可以知道在这个叶子上哪些时间点被清零了。

处理大学对应的森林也是类似的，把 set 换成树状数组，
这样就可以知道每个叶子上每个时间点被修改的值，
然后对于每个询问询问一个时间段的修改值的和即可。
#endif
#include <cstdio>
#include <vector>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 500005;

struct TreeSpace {
	int lt[maxn << 1], rt[maxn << 1];
	int top[maxn << 1];
	int size[maxn << 1];
	std::vector<int> modify[maxn << 1], query[maxn << 1];
	int np;

	int find(int x) {
		if(top[x] == x) return top[x];
		return top[x] = find(top[x]);
	}

	int merge(int a, int b) {
		++ np;
		a = find(a);
		b = find(b);
		lt[np] = a;
		rt[np] = b;
		top[a] = top[b] = top[np] = np;
		size[np] = size[a] + size[b];
		return np;
	}

	void init(int n) {
		np = n;
		for(int i = 1; i <= n; i ++) {
			top[i] = i;
			size[i] = 1;
		}
	}
} T1, T2;

int last[maxn];
std::set<int> set;
void dfs2(int x) {
	for(int t : T2.modify[x])
		set.insert(t);
	if(T2.lt[x] and T2.rt[x]) {
		dfs2(T2.lt[x]);
		dfs2(T2.rt[x]);
	} else
		for(int t : T2.query[x])
			last[t] = *(-- set.upper_bound(t));
	for(int t : T2.modify[x])
		set.erase(t);
}

ll bit[maxn];
void modify(int p, int x) {
	for(int k = p; k < maxn; k += k & -k)
		bit[k] += x;
}

ll query(int p) {
	ll res = 0;
	for(int k = p; k; k -= k & -k)
		res += bit[k];
	return res;
}

ll ans[maxn];
void dfs1(int x) {
	for(int t : T1.modify[x])
		modify(t, T1.size[x]);
	if(T1.lt[x] and T1.rt[x]) {
		dfs1(T1.lt[x]);
		dfs1(T1.rt[x]);
	} else
		for(int t : T1.query[x])
			ans[t] = query(t) - query(last[t]);
	for(int t : T1.modify[x])
		modify(t, - T1.size[x]);
}

int main() {
	int n = read, q = read;
	T1.init(n);
	T2.init(n);

	for(int i = 1; i <= q; i ++)
		ans[i] = -1;

	for(int i = 1; i <= q; i ++) {
		char o = read;
		if(o == 'U')
			T1.merge(read, read);
		if(o == 'M')
			T2.merge(read, read);
		if(o == 'A')
			T1.modify[T1.find(read)].push_back(i);
		if(o == 'Z')
			T2.modify[T2.find(read)].push_back(i);
		if(o == 'Q') {
			int x = read;
			T1.query[x].push_back(i);
			T2.query[x].push_back(i);
		}
	}

	set.insert(0);
	for(int i = 1; i <= T2.np; i ++)
		if(T2.top[i] == i)
			dfs2(i);

	for(int i = 1; i <= T1.np; i ++)
		if(T1.top[i] == i)
			dfs1(i);

	for(int i = 1; i <= q; i ++)
		if(~ans[i])
			printf("%lld\n", ans[i]);
}
