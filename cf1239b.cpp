#if 0
2020.04.01

把括号序列拿来建树。
可以发现如果要交换，交换一对匹配括号一定比交换非匹配括号更优。
而且如果交换的一对括号在括号树上深度超过 2 就一定不会影响答案。
枚举深度为 1 和 2 的所有括号树节点即可。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 300005;
char s[maxn];
int nxt[maxn];
int match[maxn];
std::vector<int> son[maxn];
int fa[maxn];

int build (int x) {
	if (match[x]) return match[x];
	int &y = match[x];
	for (y = nxt[x]; s[y] == '('; y = nxt[build(y)]) {
		fa[y] = x;
		son[x].push_back(y);
	}
	return y;
}

int main () {
	int n = read;
	scanf("%s", s + 1);

	int tot = 0;
	for (int i = 1; i <= n; i ++) tot += s[i] == '(';
	if (tot != n - tot) return printf("0\n1 1\n"), 0;

	for (int i = 1; i < n; i ++) nxt[i] = i + 1;
	nxt[n] = 1;

	for (int i = 1; i <= n; i ++)
		if (s[i] == '(')
			build(i);

	int out = 0;
	for (int i = 1; i <= n; i ++)
		if (s[i] == '(' and !fa[i])
			++ out;

	int ans = out, a1 = 1, a2 = 1;
	for (int i = 1; i <= n; i ++)
		if (s[i] == '(' and !fa[i]) {
			if (int(son[i].size()) + 1 > ans) {
				ans = int(son[i].size()) + 1;
				a1 = i;
				a2 = match[i];
			}
			for (int j : son[i])
				if (out + 1 + int(son[j].size()) > ans) {
					ans = out + 1 + int(son[j].size());
					a1 = j;
					a2 = match[j];
				}
		}

	printf("%d\n%d %d\n", ans, a1, a2);
}
