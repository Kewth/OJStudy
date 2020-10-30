/*
 * Author: Kewth

 * Date:
  2020.10.26

 * Solution:
  首先 p = 3 的情况是不存在的，容易想到整张图其实是基环树森林，随便并查集做做就行了。

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <vector>
#include "supertrees.h"
#define debug(...) fprintf(stderr, __VA_ARGS__)
#pragma GCC diagnostic ignored "-Wsign-conversion"

typedef long long ll;
using std::vector;

int find (vector<int> &fa, int x) {
	return x == fa[x] ? x : fa[x] = find(fa, fa[x]);
}

void merge (vector<int> &fa, int x, int y) {
	x = fa[x], y = fa[y];
	fa[x] = y;
}

bool same (vector<int> &fa, int x, int y) {
	return find(fa, x) == find(fa, y);
}

int construct (vector<vector<int>> p) {
	int n = int(p.size());
	vector<int> fa1(n), fa2(n);
	for (int i = 0; i < n; i ++)
		fa1[i] = fa2[i] = i;

	for (int i = 0; i < n; i ++)
		for (int j = 0; j < n; j ++) {
			if (p[i][j])
				merge(fa2, i, j);
			if (p[i][j] == 1)
				merge(fa1, i, j);
			if (p[i][j] == 3)
				return 0;
		}

	bool ok = 1;
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < n; j ++)
			if (p[i][j] == 0)
				ok &= !same(fa2, i, j) and !same(fa1, i, j);
			else if (p[i][j] == 1)
				ok &= same(fa2, i, j) and same(fa1, i, j);
			else if (p[i][j] == 2)
				ok &= same(fa2, i, j) and !same(fa1, i, j);
	if (!ok) return 0;

	vector<vector<int>> b(n, vector<int>(n));
	vector<bool> vis(n);
	for (int i = 0; i < n; i ++)
		if (fa1[i] == i) {
			if (!vis[i]) {
				vis[i] = 1;
				vector<int> cycle;
				for (int j = i + 1; j < n; j ++)
					if (same(fa2, i, j) and fa1[j] == j)
						cycle.push_back(j), vis[j] = 1;
				if (cycle.size() == 1)
					return 0;
				if (cycle.size() > 1) {
					int k = i;
					for (int j : cycle)
						b[j][k] = b[k][j] = 1, k = j;
					int j = i;
					b[j][k] = b[k][j] = 1;
				}
			}
			int k = i;
			for (int j = 0; j < n; j ++)
				if (find(fa1, j) == i and j != i)
					b[j][k] = b[k][j] = 1, k = j;
		}

	return build(b), 1;
}
