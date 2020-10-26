/*
 * Author: Kewth

 * Date:
  2020.10.18

 * Solution:
  容易发现行和列的置换数都是 1296 而非 9! 。对于两个待检查的数独 a 和 b ，朴素的
想法是在 a 上枚举所有行的置换和所有列的置换然后比对，但是由于行列之间不影响，不难
想到折半，在 a 上枚举所有行的置换，然后在 b 上枚举所有列的置换，在两边检查有没有
相同的数独即可。
  对角线翻折操作最多只进行一次，并且如果需要进行的话可以在任意时刻进行，因此如果
需要这个操作不妨假定它在最后，额外检查一次即可。

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef std::pair<int, int> par;
typedef long long ll;
typedef unsigned long long ull;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxt = 1296;
char tmp[10];
int perm[maxt][9];

ull hash (int x[9][9]) {
	int trans[10], p = 0;
	for (int i = 0; i < 10; i ++) trans[i] = 0;
	for (int i = 0; i < 9; i ++)
		for (int j = 0; j < 9; j ++)
			if (x[i][j] != -1 and !trans[x[i][j] + 1])
				trans[x[i][j] + 1] = ++ p;
	ull res = 0;
	for (int i = 0; i < 9; i ++)
		for (int j = 0; j < 9; j ++)
			res = res * 29 + ull(trans[x[i][j] + 1] + 1);
	return res;
}

struct sudoku {
	int x[9][9];
	int place_holder;
	ull a[maxt];
	std::map<ull, int> b;
	void init () {
		int y[9][9];
		for (int t = 0; t < maxt; t ++) {
			for (int i = 0; i < 9; i ++)
				for (int j = 0; j < 9; j ++)
					y[i][j] = x[perm[t][i]][j];
			a[t] = hash(y);
		}
		for (int t = 0; t < maxt; t ++) {
			for (int i = 0; i < 9; i ++)
				for (int j = 0; j < 9; j ++)
					y[i][j] = x[i][perm[t][j]];
			b[hash(y)] = t;
		}
	}
} s[45];

void get (sudoku &s1, sudoku &s2) {
	for (int i = 0; i < 9; i ++) {
		scanf("%s", tmp);
		for (int j = 0; j < 9; j ++)
			s1.x[i][j] = s2.x[j][i] = tmp[j] == '.' ? -1 : tmp[j] - '1';
	}
}

void check (int i, int j, int n, int &x, int &y, int &sp) {
	for (int t = 0; t < maxt; t ++) {
		ull h = s[i].a[t];
		if (s[j].b.count(h))
			return x = t, y = s[j].b[h], sp = 0, void();
		if (s[n + j].b.count(h))
			return x = t, y = s[n + j].b[h], sp = 1, void();
	}
}

struct operation { char t; int i, j; };

int sx[9][9];
void shit (operation o) {
	if (o.t == 'R') {
		shit({'r', 3 * o.i - 2, 3 * o.j - 2});
		shit({'r', 3 * o.i - 1, 3 * o.j - 1});
		shit({'r', 3 * o.i, 3 * o.j});
	}
	if (o.t == 'C') {
		shit({'c', 3 * o.i - 2, 3 * o.j - 2});
		shit({'c', 3 * o.i - 1, 3 * o.j - 1});
		shit({'c', 3 * o.i, 3 * o.j});
	}
	if (o.t == 'r')
		for (int k = 0; k < 9; k ++)
			std::swap(sx[o.i - 1][k], sx[o.j - 1][k]);
	if (o.t == 'c')
		for (int k = 0; k < 9; k ++)
			std::swap(sx[k][o.i - 1], sx[k][o.j - 1]);
	if (o.t == 'F')
		for (int i = 0; i < 9; i ++)
			for (int j = i; j < 9; j ++)
				std::swap(sx[i][j], sx[j][i]);
}

int main () {
	/* int p[9], t = 0; */
	/* for (int i = 0; i < 9; i ++) p[i] = i; */
	/* do { */
	/* 	int at[9], ok = 1; */
	/* 	for (int i = 0; i < 9; i ++) at[p[i]] = i / 3; */
	/* 	for (int i = 0; i < 9; i ++) ok &= i % 3 == 0 or at[i] == at[i - 1]; */
	/* 	if (ok) std::copy(p, p + 9, perm[t ++]); */
	/* } while (std::next_permutation(p, p + 9)); */

	int trans[6][3] = {
		{0, 1, 2},
		{0, 2, 1},
		{1, 0, 2},
		{1, 2, 0},
		{2, 0, 1},
		{2, 1, 0}
	};
	for (int a = 0; a < 6; a ++)
		for (int b = 0; b < 6; b ++)
			for (int c = 0; c < 6; c ++)
				for (int d = 0; d < 6; d ++) {
					int *p = perm[a * 216 + b * 36 + c * 6 + d];
					for (int i = 0; i < 3; i ++)
						p[0 + i] = trans[a][0] * 3 + trans[b][i];
					for (int i = 0; i < 3; i ++)
						p[3 + i] = trans[a][1] * 3 + trans[c][i];
					for (int i = 0; i < 3; i ++)
						p[6 + i] = trans[a][2] * 3 + trans[d][i];
				}

	std::vector<par> op[6];
	op[0] = {};
	op[1] = {par(2, 3)};
	op[2] = {par(1, 2)};
	op[3] = {par(1, 2), par(2, 3)};
	op[4] = {par(1, 2), par(1, 3)};
	op[5] = {par(1, 3)};

	int n = read;
	for (int i = 1; i <= n; i ++) {
		get(s[i], s[n + i]);
		s[i].init();
		s[n + i].init();
	}

	for (int i = 1; i <= n; i ++) {
		for (int j = i + 1; j <= n; j ++) {
			int t1 = 0, t2 = 0, sp = -1;
			check(i, j, n, t1, t2, sp);
			if (sp == -1) puts("No");
			else {
				puts("Yes");
				int a1 = t1 / 216, b1 = t1 / 36 % 6, c1 = t1 / 6 % 6, d1 = t1 % 6;
				int a2 = t2 / 216, b2 = t2 / 36 % 6, c2 = t2 / 6 % 6, d2 = t2 % 6;
				std::vector<operation> ans;
				for (par p : op[a1]) ans.push_back({'R', p.first, p.second});
				for (par p : op[b1]) ans.push_back({'r', 0 + p.first, 0 + p.second});
				for (par p : op[c1]) ans.push_back({'r', 3 + p.first, 3 + p.second});
				for (par p : op[d1]) ans.push_back({'r', 6 + p.first, 6 + p.second});
				int reverse_begin = int(ans.size());
				if (sp) ans.push_back({'F', 0, 0});
				for (par p : op[a2]) ans.push_back({'C', p.first, p.second});
				for (par p : op[b2]) ans.push_back({'c', 0 + p.first, 0 + p.second});
				for (par p : op[c2]) ans.push_back({'c', 3 + p.first, 3 + p.second});
				for (par p : op[d2]) ans.push_back({'c', 6 + p.first, 6 + p.second});
				std::reverse(ans.begin() + reverse_begin, ans.end());
				for (int ii = 0; ii < 9; ii ++)
					for (int jj = 0; jj < 9; jj ++)
						sx[ii][jj] = s[i].x[ii][jj];
				for (auto oper : ans) shit(oper);
				/* for (int ii = 0; ii < 9; ii ++) */
				/* 	for (int jj = 0; jj < 9; jj ++) */
				/* 		debug("%d", sx[ii][jj] + 1); */
				/* debug("\n"); */
				/* for (int ii = 0; ii < 9; ii ++) */
				/* 	for (int jj = 0; jj < 9; jj ++) */
				/* 		debug("%d", s[j].x[ii][jj] + 1); */
				/* debug("\n"); */
				int tr[9];
				for (int k = 0; k < 9; k ++) tr[k] = k;
				for (int ii = 0; ii < 9; ii ++)
					for (int jj = 0; jj < 9; jj ++)
						if (sx[ii][jj] != -1) {
							int &X = tr[sx[ii][jj]], Y = s[j].x[ii][jj];
							if (X != Y) {
								ans.push_back({'D', X + 1, Y + 1});
								for (int k = 0; k < 9; k ++)
									if (tr[k] == Y)
										tr[k] = X;
								X = Y;
							}
						}
				printf("%lu\n", ans.size());
				for (auto oper : ans)
					if (oper.t == 'F')
						puts("F");
					else
						printf("%c %d %d\n", oper.t, oper.i, oper.j);
			}
		}
	}
}
