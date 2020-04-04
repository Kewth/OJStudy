#if 0
2020.02.01

对于每一行，将点随意匹配然后连边，如果剩下点不管，列同理。
两点连边相当于限制两点颜色不同，那么对于建出来的图黑白染色即可。
黑白染色一定是可以成功的，因为图不存在奇环。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 200005;
int las_x[maxn], las_y[maxn];
std::vector<int> G[maxn];
char s[maxn];

void dfs(int u) {
	for(int v : G[u])
		if(!s[v]) {
			s[v] = 'r' + 'b' - s[u];
			dfs(v);
		}
}

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++) {
		int x = read, y = read;
		if(las_x[x]) {
			G[las_x[x]].push_back(i);
			G[i].push_back(las_x[x]);
			las_x[x] = 0;
		} else
			las_x[x] = i;
		if(las_y[y]) {
			G[las_y[y]].push_back(i);
			G[i].push_back(las_y[y]);
			las_y[y] = 0;
		} else
			las_y[y] = i;
	}

	for(int i = 1; i <= n; i ++)
		if(!s[i]) {
			s[i] = 'r';
			dfs(i);
		}

	puts(s + 1);
}
