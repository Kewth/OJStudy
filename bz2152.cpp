#if 0
2019.07.24

点分治板子（我竟然只花了 30min 就调完了）。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) // fprintf(stderr, __VA_ARGS__)

inline int input() {
	int c = getchar(), x = 0;
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

const int maxn = 20005;
int head[maxn], to[maxn << 1], nxt[maxn << 1], val[maxn << 1], hp;
int size[maxn];
bool vis[maxn];
int town[3], Town[3];

inline void add(int u, int v, int w) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	val[hp] = w;
}

int center, totsize, minsize;
void get_center(int u) {
	vis[u] = true;
	int now = 0;
	size[u] = 1;
	for(int i = head[u]; i; i = nxt[i])
		if(not vis[to[i]]) {
			get_center(to[i]);
			size[u] += size[to[i]];
			now = std::max(now, size[to[i]]);
		}
	now = std::max(now, totsize - size[u]);
	if(now < minsize) {
		center = u;
		minsize = now;
	}
	vis[u] = false;
}

void dfs(int u, int deep) {
	town[deep % 3] ++;
	vis[u] = true;
	for(int i = head[u]; i; i = nxt[i])
		if(not vis[to[i]])
			dfs(to[i], deep + val[i]);
	vis[u] = false;
}

int calc(int u) {
	vis[u] = true;
	int res = 0;
	Town[0] = 1;
	Town[1] = Town[2] = 0;
	for(int i = head[u]; i; i = nxt[i])
		if(not vis[to[i]]) {
			town[0] = town[1] = town[2] = 0;
			dfs(to[i], val[i]);
			debug("%d -> %d: %d %d %d\n", u, to[i], town[0], town[1], town[2]);
			for(int j = 0; j < 3; j ++) {
				res += Town[j] * town[(3 - j) % 3] * 2;
				Town[j] += town[j];
			}
		}
	debug("calc %d: %d\n", u, res);
	return res;
}

int divi(int u, int n) {
	debug("divi %d\n", u);
	center = u;
	totsize = n;
	minsize = 100000000;
	get_center(u);
	int res = calc(center);
	for(int i = head[center]; i; i = nxt[i])
		if(not vis[to[i]])
			res += divi(to[i], size[to[i]]);
	return res;
}

int gcd(int a, int b) {
	if(not b) return a;
	return gcd(b, a % b);
}

int main() {
	int n = input();
	for(int i = 1; i < n; i ++) {
		int u = input(), v = input(), w = input();
		add(u, v, w);
		add(v, u, w);
	}
	int a = divi(1, n) + n, b = n * n;
	int g = gcd(a, b);
	a /= g;
	b /= g;
	printf("%d/%d\n", a, b);
}
