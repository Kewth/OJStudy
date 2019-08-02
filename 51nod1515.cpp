#if 0
2019.08.02

如果只有相等关系处理，并查集即可，考虑处理不等关系。
每个并查集用 set 存不能与哪些其他集合相等，合并时启发式合并即可。
#endif
#include <cstdio>
#include <set>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() {
	int c = getchar(), x = 0;
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

const int maxn = 100005;
int qux[maxn], quy[maxn], qup[maxn];
int t[maxn << 1];
int img_rel[maxn << 1];
int fa[maxn << 1];
std::set<int> cannot[maxn << 1];

int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void merge(int x, int y) {
	if(cannot[x].size() > cannot[y].size())
		std::swap(x, y);
	for(std::set<int>::iterator it = cannot[x].begin();
			it != cannot[x].end(); it ++) {
		cannot[*it].erase(x);
		cannot[*it].insert(y);
		cannot[y].insert(*it);
	}
	fa[x] = y;
}

int main() {
	int q = input();
	int p = 0;
	for(int i = 1; i <= q; i ++) {
		qux[i] = input();
		quy[i] = input();
		qup[i] = input();
		t[++ p] = qux[i];
		t[++ p] = quy[i];
	}
	std::sort(t + 1, t + p + 1);
	int n = 0;
	for(int i = 1; i <= p; i ++)
		if(t[i] != t[i - 1])
			img_rel[++ n] = t[i];
	for(int i = 1; i <= n; i ++)
		fa[i] = i;
	for(int i = 1; i <= q; i ++) {
		int x = std::lower_bound(img_rel + 1, img_rel + n + 1, qux[i]) - img_rel;
		int y = std::lower_bound(img_rel + 1, img_rel + n + 1, quy[i]) - img_rel;
		x = find(x);
		y = find(y);
		if(qup[i] == 1) {
			if(cannot[x].count(y))
				puts("NO");
			else {
				if(x != y)
					merge(x, y);
				puts("YES");
			}
		} else {
			if(x == y)
				puts("NO");
			else {
				cannot[x].insert(y);
				cannot[y].insert(x);
				puts("YES");
			}
		}
	}
}
