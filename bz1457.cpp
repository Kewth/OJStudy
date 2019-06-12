#if 0
2019.06.12

看似每个皇后是相互独立的子游戏，实际不是，
因为只要有一个皇后走进 (0, 0) 其他所有皇后都无法移动。

皇后一旦到了可以一步走到 (0, 0) 的位置那么对手就赢了。
所以两者不会把皇后往那移，把这种点去掉。
那么失败条件为无法操作，此时每个皇后是独立的子游戏。
SG 定理 + 特判有没有一步到 (0, 0) 的皇后即可。
#endif
#include <cstdio>
#include <set>

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 101;
int sg[maxn][maxn];

int main() {
	for(int i = 1; i < maxn; i ++)
		for(int j = 1; j < maxn; j ++)
			if(i != j) {
				std::set<int> trans;
				for(int k = 1; k < i; k ++)
					if(k != j)
						trans.insert(sg[k][j]);
				for(int k = 1; k < j; k ++)
					if(k != i)
						trans.insert(sg[i][k]);
				for(int k = 1; k < i and k < j; k ++)
					trans.insert(sg[i - k][j - k]);
				while(trans.count(sg[i][j]))
					sg[i][j] ++;
			}
	/* for(int i = 1; i <= 4; i ++) { */
	/* 	for(int j = 1; j <= 4; j ++) */
	/* 		printf("%d ", sg[i][j]); */
	/* 	puts(""); */
	/* } */
	int T = input();
	while(T --) {
		int n = input(), sgsum = 0;
		bool one_step = false;
		for(int i = 1; i <= n; i ++) {
			int x = input(), y = input();
			if(x == y or not x or not y)
				one_step = true;
			else
				sgsum ^= sg[x][y];
		}
		if(one_step or sgsum)
			puts("^o^");
		else
			puts("T_T");
	}
}
