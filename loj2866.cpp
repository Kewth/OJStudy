/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.10

 * Solution:
    注意到除了开关其他的点的出度都唯一，只能用开关来创造分支。一个朴素的想法是把开关建
一个满二叉树，把所有非开关元件都连向树根，然后把序列按顺序放在对应的叶子即可。
    但是最坏情况下二叉树的非叶子节点数可能会达到 2n ，注意到可能会有许多节点的子树内没
有关键的叶子节点，那么连向这样的点实际上等价于连向树根，直接把序列放在最右边的一段连续
的叶子上，这样一来二叉树的点数就不会超过 n + logn 了。
    稍加观察不难发现第 i 个访问的叶子编号是 Rev[i] ，从 0 开始编号，Rev[i] 是 i 的二进
制翻转。

 * Digression:
  不知道为啥要做成交互题，完全没有任何所谓的交互，就是获取输入返回输出。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

#ifdef ONLINE_JUDGE
#include "doll.h"
#else
void create_circuit(int M, std::vector<int> A);
void answer(std::vector<int> C, std::vector<int> X, std::vector<int> Y);
#endif

typedef size_t si;
typedef std::vector<int> vec;
const int maxn = 1 << 18;
int a[maxn];
int X[maxn], Y[maxn];

int N, S, E;
int build (int L, int R) {
	if (R < E - N) return -1;
	int M = (L + R) >> 1;
	if (L == R) return a[L];
	int id = -- S;
	X[-id - 1] = build(L, M);
	Y[-id - 1] = build(M + 1, R);
	return id;
}

bool state[maxn];
void test () {
	int x = -1;
	while (x) {
		debug("%d\n", x);
		if (x < 0) {
			state[-x - 1] ^= 1;
			x = state[-x - 1] ? X[-x - 1] : Y[-x - 1];
		} else
			x = -1;
	}
}

int R[maxn];
void create_circuit (int M, vec A) {
	A.push_back(0);
	N = int(A.size());
	E = 1;
	while (E < N) E <<= 1;
	for (int i = 1; i < E; i ++)
		R[i] = R[i >> 1] >> 1 | (i & 1) * (E >> 1);
	vec::iterator it = A.begin();
	for (int i = 0; i < E; i ++)
		if (R[i] >= E - N)
			a[R[i]] = *(it ++);
	int root = build(0, E - 1); // root == -1
	/* test(); */
	answer(vec(si(M + 1), root), vec(X, X - S), vec(Y, Y - S));
}
