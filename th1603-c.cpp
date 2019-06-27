#if 0
2019.06.27

第一层二分答案 K ，那么要求用 K 个盒子使 X, Y 尽可能小，
其中 X, Y 分别为两种球的数量。

假设固定 X 求 Y ，不难发现随着 X 增大 Y 一定减小。
当 X = R 时，K 个盒子可行当且仅当 Y <= B 。
将所有 (X, Y) 连线，那么需要判断 (R, B) 是否在该曲线上方。

选两个正数 p, q ，选出 px + qy 最小的 K 个点，
那么这些点的 (X, Y) 一定在该曲线上。
证明：若 (X, Y) 在该曲线下方，与曲线的最优性质矛盾。
若 (X, Y) 在该曲线上方，那么一定存在一个点的 x + y 比选出的点小，
与选出的点的性质矛盾。

那么第二层二分 p, q 的比，对于一对 (p, q) 求出对应的 (X, Y) ，
若 (R, B) 在 (X, Y) 右上方则 K 可行，在左下方则 K 不可行。

考虑如何通过 (p, q) 求 (X, Y) 。
第三层二分 z 统计 px + qy <= z 的点的数量，
若恰好为 K ，那么这些点的 (X, Y) 即为所求。

如何统计 px + qy <= z 的 (x, y) 数量？
枚举 x ，计算合法的 y 的数量。
把式子写出来会发现这其实是类欧几里得算法的模板，
但是暴力跑 + 卡常也能过（我跑不过）。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const lolong PRIME = 10000000019ll;
/* const lolong PRIME = 100000; */
const int M = 2000;

lolong X, Y;

inline void updatexy(lolong p, lolong q, lolong z) {
	X = Y = 0;
	for(int x = 0; p * x <= z; x ++) {
		lolong y = (z - p * x) / q;
		X += x * (y + 1);
		Y += y * (y + 1) >> 1;
	}
}

// 感谢 CYJian 的类欧几里得
inline lolong solve(lolong a, lolong b, lolong c, lolong n){
    if(!b) return 0;
    if(a < 0 || c < 0) return (a / b - 1) * n * (n + 1) / 2 + (c / b - 1) * (n + 1) + solve(a % b + b, b, c % b + b, n);
    if(a >= b || c >= b) return a / b * n * (n + 1) / 2 + c / b * (n + 1) + solve(a % b, b, c % b, n);
    lolong max = (a * n + c) / b;
    return n * max - solve(b, a, b - c - 1, max - 1);
}

inline bool check_z(lolong p, lolong q, int k, lolong z) {
	return z / p + 1 + solve(- p, q, z, z / p) >= k;
	/* // 暴力跑 2.4s */
	/* int tot = 0; */
	/* for(int x = 0; p * x <= z and tot < k; x ++) */
	/* 	tot += (z - p * x) / q + 1; */
	/* return tot >= k; */
}

inline void getxy(lolong p, lolong q, int k) {
	lolong l = 1, r = PRIME * M;
	while(l < r) {
		lolong mid = (l + r) >> 1;
		if(check_z(p, q, k, mid)) r = mid;
		else l = mid + 1;
	}
	updatexy(p, q, l);
}

inline bool check_k(int R, int B, int k) {
	// 固定 p + q 以代替比例
	/* lolong l = 1, r = PRIME; */
	lolong l = 1, r = PRIME;
	lolong lx, ly, rx, ry;
	while(l <= r) {
		lolong mid = (l + r) >> 1;
		getxy(mid, PRIME - mid, k);
		/* debug("getxy (%lld, %lld) in k=%d, p=%lld, q=%lld\n", */
		/* 		X, Y, k, mid, PRIME - mid); */
		if(R >= X and B >= Y) return true;
		if(R <= X and B < Y) return false;
		if(R > X and B < Y) {
			lx = X;
			ly = Y;
			r = mid - 1;
		}
		if(R < X and B >= Y) {
			rx = X;
			ry = Y;
			l = mid + 1;
		}
	}
	// 求两点的直线
	/* debug("FUCK: (%lld, %lld), (%lld, %lld)\n", lx, ly, rx, ry); */
	return 1ll * (rx - lx) * B >= 1ll * (ry - ly) * R
		+ 1ll * ry * (rx - lx) - 1ll * (ry - ly) * rx;
}

int main() {
	int R = input(), B = input();
	int l = 1, r = R + B;
	while(l < r) {
		int mid = (l + r + 1) >> 1;
		if(check_k(R, B, mid + 1)) l = mid;
		else r = mid - 1;
	}
	printf("%d\n", l);
}
