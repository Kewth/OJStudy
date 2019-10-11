#if 0
2019.10.11

恢复和攻击是相互独立的，那么只要能在怼死大佬前狗住就行了，
DP 求出狗的过程中最大的能剩下来干的天数，
状态设 f[i][j] 表示狗住前 i 天后恰好剩下 j 点自信值时，这 i 天最多能干多少天。
然后问题就是询问是否能在确定的天数 D 内打出恰好 c 点伤害。
中点考虑怼大佬这个操作，暴力搜出所有可能的怼的操作，
用二元组 (f, d) 表示怼出伤害 f 花费 d 天怼，那么两个怼需要满足以下不等式：
f1 + f2 <= c, f1 + f2 + (D - d1 - d2) >= c 。
设 g = f - d ，用二元组 (f, g) 表示怼，将所有怼按 f 升序排序，
然后每个询问从大到小枚举 f1 ，由于 f1 + f2 <= c ，
随着 f1 的减小，f2 的上界会增大，而要满足的就是 g1 + g2 >= c - D ，
枚举 f1 的时候 g1 也是确定的，那么只需要中途维护 g2 的最大值即可。

然而这题他妈原来是个搜索题，搜怼的方式的时候普通的 dfs 直接爆炸。
首先用 bfs 可以减小常数。
其次是只有 F 乘上 L 的时候再判断是否添加新的怼， L 增加的时候不管。
最主要是要用哈希表对搜索状态 (F, L) 去重，本质上就是记忆化，
但是不需要记忆化深度，因为有多个 (F, L) 时一定是深度最小的 g 最大，
而 bfs 搜到的第一个 (F, L) 一定是所有 (F, L) 中深度最小的。
#endif
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 105;
int dec[maxn], add[maxn];
int f[maxn][maxn];
int c[maxn];
struct Gan {
	int f, g;
} gan[50000000];
int gp;

inline void chkmax(int &x, int y) {
	if(y > x) x = y;
}

bool cmp(Gan x, Gan y) {
	return x.f < y.f;
}

int water;
std::unordered_map<lolong, bool> map;
int MAX;

struct Node {
	int d, x, now;
	Node(int d, int x, int now): d(d), x(x), now(now) { }
};

inline void Add(Node u) {
	if(u.now > u.d) {
		gp ++;
		gan[gp].f = u.now;
		gan[gp].g = u.now - u.d - 1;
	}
}

/* void fuck(int d, int x, int now, bool tryadd = 0) { */
/* 	if(d >= water) return; */
/* 	if(tryadd) */
/* 		Add(Node(d, x, now)); */
/* 	fuck(d + 1, x + 1, now); */
/* 	if(x > 1 and 1ll * now * x <= MAX and */
/* 			!map[1ll * now * 1000000000 + x]) { */
/* 		map[1ll * now * 1000000000 + x] = 1; */
/* 		fuck(d + 1, x, now * x, 1); */
/* 	} */
/* } */

void fuck(int d, int x, int now) {
	std::queue<Node> q;
	q.push(Node(d, x, now));
	while(!q.empty()) {
		Node u = q.front();
		q.pop();
		if(u.d >= water) continue;
		q.push(Node(u.d + 1, u.x + 1, u.now));
		if(u.x > 1 and 1ll * u.now * u.x <= MAX and
				!map[1ll * u.now * 1000000000 + u.x]) {
			map[1ll * u.now * 1000000000 + u.x] = 1;
			Node v(u.d + 1, u.x, u.now * u.x);
			q.push(v);
			Add(v);
		}
	}
}

int main() {
	int n = input(), q = input(), mc = input();

	for(int i = 1; i <= n; i ++)
		dec[i] = input();
	for(int i = 1; i <= n; i ++)
		add[i] = input();
	for(int i = 1; i <= q; i ++)
		chkmax(MAX, c[i] = input());

	for(int i = 0; i <= n; i ++)
		for(int j = 0; j <= mc; j ++)
			f[i][j] = - 100000;
	f[0][mc] = 0;

	for(int i = 1; i <= n; i ++)
		for(int j = dec[i]; j <= mc; j ++) {
			chkmax(f[i][j - dec[i]], f[i - 1][j] + 1);
			chkmax(f[i][std::min(mc, j - dec[i] + add[i])], f[i - 1][j]);
		}

/* 	for(int i = 0; i <= n; i ++) */
/* 		for(int j = 0; j <= mc; j ++) */
/* 			if(f[i][j] >= 0) */
/* 				debug("%d %d : %d\n", i, j, f[i][j]); */

	for(int i = 1; i <= n; i ++)
		for(int j = 0; j <= mc; j ++)
			chkmax(water, f[i][j]);

	fuck(0, 0, 1);
	std::sort(gan + 1, gan + gp + 1, cmp);

	/* for(int i = 1; i <= gp; i ++) */
	/* 	debug("%d %d\n", gan[i].f, gan[i].g); */

	for(int k = 1; k <= q; k ++) {
		int max = 0;
		for(int i = gp, j = 0; i >= 0; i --) {
			if(gan[i].f > c[k]) continue;
			while(j < gp and gan[j + 1].f + gan[i].f <= c[k])
				chkmax(max, gan[++ j].g);
			if(gan[i].g + max + water >= c[k]) {
				puts("1");
				goto GET;
			}
		}
		puts("0");
GET: ;
	}
}
