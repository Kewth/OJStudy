#if 0
2019.06.16

定义个数大于 1 的堆为大堆。
若不存在大堆，胜负即 1 的奇偶性，此时 SG 。
否则所有堆的异或和即是整个游戏的 SG 。
虽然不满足 SG 定理的条件，但是仍可证明 SG = 0 状态只能转移到 SG > 0 的状态，
SG > 0 的状态总能转移到 SG = 0 的状态。
终止状态是没有大堆的情况。
证明：
SG = 0 -> SG > 0 ，随便取都会改变 SG 值。
SG > 0 -> SG = 0 ：
若只有一个大堆，取成 0/1 即可。
否则每种取法取完后一定还有大堆，此时取式子前后 SG 就和普通的取石子游戏一样。
因为普通的取石子游戏中有 SG > 0 -> SG = 0 ，此时亦然。
#endif
#include <cstdio>

int input() { int x; scanf("%d", &x); return x; }

int main() {
	int T = input();
	while(T --) {
		int n = input(), sg = 0, big = 0;
		for(int i = 1; i <= n; i ++) {
			int x = input();
			sg ^= x;
			if(x > 1) big ++;
		}
		if(big == 0) sg ^= 1;
		if(sg) puts("John");
		else puts("Brother");
	}
}
