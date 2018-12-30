// include files {{{1
#include <bits/stdc++.h>

// function to speed up input {{{1
long long input() {
	int ch = getchar();
	long long res = 0;
	while(ch < '0' or ch > '9') ch = getchar();
	while(ch >= '0' and ch <= '9') res = res * 10 + ch - '0', ch = getchar();
	return res;
}

// global variables {{{1
const int maxn = 50050;
int f[maxn], g[maxn];
int head[maxn], to[maxn<<1], lon[maxn<<1], nxt[maxn<<1];
int num[maxn];
int tol[maxn], tor[maxn];

// add edge {{{1
void add(int x, int y, int w) {
	static int p = 0;
	nxt[++p] = head[x];
	head[x] = p;
	to[p] = y;
	lon[p] = w;
	nxt[++p] = head[y];
	head[y] = p;
	to[p] = x;
	lon[p] = w;
}

// delete a node {{{1
int remove(int x) {
	tol[tor[x]] = tol[x];
	tor[tol[x]] = tor[x];
	return tor[x];
}

// DP again {{{1
int dp2(int n, int K) {
	std::sort(num+1, num+n+1);
	int res = 0;
	for(int i=1;i<=n+1;i++) {
		tol[i] = i-1;
		tor[i] = i+1;
	}
	for(int i=1,p=n+1;i<=n;p=remove(p),i=remove(i)) {
		if(i == p)
			p = tor[p];
		if(p == n+1) {
			p = tol[p];
			while(i < p and num[i] + num[p] < K)
				i = tor[i];
			if(i >= p) break;
		}
		while(num[i] + num[tol[p]] >= K and tol[p] > i)
			p = tol[p];
		res ++;
	}
	return res;
}

// dfs to DP {{{1
void dp(int u, int fa, int K) {
	f[u] = 0;
	g[u] = 0;
	int p = 0;
	// fprintf(stderr, "%d->\n", u);
	for(int i=head[u];i;i=nxt[i]) {
		int v = to[i];
		if(v == fa) continue;
		dp(v, u, K);
		f[u] += f[v];
	}
	for(int i=head[u];i;i=nxt[i]) {
		int v = to[i];
		if(v == fa) continue;
		int w = lon[i] + g[v];
		if(w >= K)
			f[u] ++;
		else
			num[++p] = w;
	}
	f[u] += dp2(p, K);
	g[u] = num[tol[p+1]];
	// fprintf(stderr, "%d:%d,%d\n", u, f[u], g[u]);
}

// Main function {{{1
int main() {
	/* freopen("track.in", "r", stdin); */
	/* freopen("track.out", "w", stdout); */
	int n = input(), m = input();
	for(int i=1;i<n;i++) {
		int x = input(), y = input(), w = input();
		add(x, y, w);
	}
	int l = 1, r = 1000000000;
	while(l < r) {
		int mid = (l + r + 1) >> 1;
		dp(1, 0, mid);
		if(f[1] >= m) l = mid;
		else r = mid - 1;
	}
	printf("%d\n", l);
	// debug:
	// fprintf(stderr, "---\n");
	// dp(1, 0, 15);
}

// }}}1
