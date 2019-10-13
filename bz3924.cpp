#if 0
2019.10.13

动态树分治，建出点分树，对于点分树上每个点维护三个值。
s1 表示该点代表的联通块到该点的带权距离和。
s2 表示该点代表的联通块到该点在点分树上的父亲的带权距离和。
s3 表示该点代表的联通块的权值和。
每次修改直接在点分树上跳 father 维护 s1, s2, s3 。
查询时从点分树的根开始，每次在原图连边中找到代价比当前点小的点，
然后向该点方向跳到对应点分树上的边，最终可以找到代价最小的点。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005;

int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], hp = 1;
inline void add(int u, int v, int w) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	val[hp] = w;
}

inline bool chkmin(lolong &x, lolong y) {
	if(y < x) return x = y, 1;
	return 0;
}

inline bool chkmax(int &x, int y) {
	if(y > x) return x = y, 1;
	return 0;
}

int size[maxn], msize[maxn];
bool vis[maxn];
int rt;
void getsize(int u, int tot) {
	size[u] = 1;
	msize[u] = 0;
	for(int i = head[u]; i; i = nxt[i])
		if(!vis[to[i]]) {
			vis[u] = 1;
			getsize(to[i], tot);
			vis[u] = 0;
			size[u] += size[to[i]];
			chkmax(msize[u], size[to[i]]);
		}
	chkmax(msize[u], tot - size[u]);
	if(msize[u] < msize[rt])
		rt = u;
}

int fa[maxn];
int nto[maxn << 1];
int maketree(int u, int n) {
	rt = 0;
	getsize(u, n);
	u = rt;
	vis[u] = 1;
	for(int i = head[u]; i; i = nxt[i])
		if(!vis[to[i]]) {
			int v = maketree(to[i], size[to[i]]);
			fa[v] = u;
			nto[i] = v;
		}
	return u;
}

const int maxk = 20;
lolong st[maxn << 1][maxk];
int highbit[maxn << 1];
int first[maxn], sp;
lolong dist[maxn];
void dfs(int u, int f) {
	st[first[u] = ++ sp][0] = dist[u];
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != f) {
			dist[to[i]] = dist[u] + val[i];
			dfs(to[i], u);
			st[++ sp][0] = dist[u];
		}
}

void stinit() {
	for(int i = 2; i <= sp; i ++)
		highbit[i] = highbit[i >> 1] + 1;
	for(int i = sp; i; i --)
		for(int k = 1; k < maxk and i + (1 << k) - 1 <= sp; k ++)
			st[i][k] = std::min(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
}

lolong dis(int x, int y) {
	lolong res = dist[x] + dist[y];
	x = first[x];
	y = first[y];
	if(x > y) std::swap(x, y);
	int k = highbit[y - x + 1];
	res -= std::min(st[x][k], st[y - (1 << k) + 1][k]) << 1;
	return res;
}

lolong s1[maxn], s2[maxn], s3[maxn];
lolong calc(int u) {
	lolong res = s1[u];
	for(int x = u; fa[x]; x = fa[x])
		res += (s1[fa[x]] - s2[x]) + (s3[fa[x]] - s3[x]) * dis(u, fa[x]);
	return res;
}

lolong query(int x) {
	while(1) {
		/* debug("q%d\n", x); */
		lolong v = calc(x);
		for(int i = head[x]; i; i = nxt[i])
			if(nto[i]) {
				lolong nv = calc(to[i]);
				/* debug("%d -> %d : %lld\n", x, to[i], nv); */
				if(chkmin(v, nv)) {
					x = nto[i];
					goto GET;
				}
			}
		return v;
		break;
GET:;
	}
}

int main() {
	int n = input();
	int q = input();

	for(int i = 1; i < n; i ++) {
		int u = input(), v = input(), w = input();
		add(u, v, w);
		add(v, u, w);
	}

	dfs(1, 0);
	stinit();

	msize[0] = 1000000000;
	int root = maketree(1, n);

	while(q --) {
		int u = input(), e = input();

		for(int x = u; x; x = fa[x]) {
			s1[x] += e * dis(x, u);
			s3[x] += e;
		}

		for(int x = u; fa[x]; x = fa[x])
			s2[x] += e * dis(fa[x], u);

		/* for(int i = 1; i <= n; i ++) */
		/* 	debug("%d: %lld %lld %lld\n", i, s1[i], s2[i], s3[i]); */

		printf("%lld\n", query(root));
	}
}
