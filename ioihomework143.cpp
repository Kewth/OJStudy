/*
 * Author: Kewth

 * Date:
  2020.11.25

 * Solution:
  In blog.

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
#include <random>
#ifdef LOCAL
# include "my.hpp"
#else
# include "jump.h"
#endif
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

const int maxn = 1000;
int N;
bool qs[maxn], ks[maxn];
bool RET;

bool Q (int n) {
	int get = query(std::vector<int>(qs, qs + n));
	RET = get == n;
	return get == n / 2;
}

void solve (int n) {
	std::mt19937 e;
	std::uniform_int_distribution<int> rand(0, 1);
	do {
		for (int i = 1; i < n; i ++)
			qs[i] = rand(e);
	} while (!Q(n));
	/* for (int i = 0; i < n; i ++) */
	/* 	debug("%d", qs[i]); */
	/* debug("\n"); */
	int tot = 0;
	qs[0] ^= 1;
	for (int i = 1; i < n; i ++) {
		qs[i] ^= 1;
		ks[i] = qs[i] ^ Q(n);
		qs[i] ^= 1;
		tot += qs[i] ^ ks[i];
	}
	ks[0] = tot == n / 2 - 1;
	std::copy(ks, ks + n, qs);
	/* for (int i = 0; i < n; i ++) */
	/* 	debug("%d", qs[i]); */
	/* debug("\n"); */
	if (Q(n), RET) return;
	for (int i = 0; i < n; i ++)
		qs[i] ^= 1;
	if (Q(n), RET) return;
	debug("FAIL\n");
	exit(1);
}
