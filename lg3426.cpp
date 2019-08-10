#if 0
2019.08.09

首先模板一定同时是原串的前缀和后缀，
那么说明模板在 fail 树上对应末节点的祖先。
要求长度最小，考虑从根向末节点方向搜，搜到第一个合法的节点即是答案。
如何判定当前节点合法？
当且仅当该节点在原串的所有出现位置的右端点最大间距不超过当且节点长度。
而考虑该节点在原串对应的每个右端点，就是 fail 树上子树的所有节点，
这也是 fail 树的一个性质，那么从上向下搜的过程中删掉不在子树的点，
用链表维护最大间距即可。
#endif
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

const int maxn = 1000005;
char s[maxn];
int fail[maxn];
int l[maxn], r[maxn];
bool flag[maxn];
std::vector<int> G[maxn];

int maxdis = 1;
int erase(int u) {
	maxdis = std::max(maxdis, r[u] - l[u]);
	r[l[u]] = r[u];
	l[r[u]] = l[u];
	for(int v : G[u])
		erase(v);
}

int dfs(int u) {
	if(maxdis <= u)
		return u;
	int to;
	for(int v : G[u])
		if(not flag[v])
			erase(v);
		else
			to = v;
	return dfs(to);
}

int main() {
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	fail[0] = -1;
	for(int i = 0; i < n; i ++) {
		int j = fail[i];
		while(~ j and s[j + 1] != s[i + 1])
			j = fail[j];
		fail[i + 1] = j + 1;
		G[j + 1].push_back(i + 1);
	}
	for(int i = n; i; i = fail[i])
		flag[i] = true;
	for(int i = 1; i <= n; i ++) {
		l[i] = i - 1;
		r[i] = i + 1;
	}
	printf("%d\n", dfs(0));
}

