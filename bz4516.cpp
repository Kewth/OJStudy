#if 0
2019.08.07

维护一个后缀自动机，考虑新加一个数增加的答案。
不难发现新增的子串一定是现在串的后缀，而且是之前没有出现过的后缀，
这些后缀对应了后缀自动机里头的 last 状态，数量即 len[last] - len[fa[last]] 。
#endif
#include <cstdio>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

struct SAM {
	std::map<int, SAM *> ch;
	int len;
	SAM *fa;
	SAM *insert(int);
	SAM(int len): len(len), fa(nullptr) {}
};

SAM *SAM::insert(int x) {
	SAM *now = new SAM(len + 1);
	SAM *pre = this, *root = this;
	while(pre and not pre -> ch[x]) {
		root = pre;
		pre -> ch[x] = now;
		pre = pre -> fa;
	}
	if(pre) {
		SAM *preto = pre -> ch[x];
		if(preto -> len == pre -> len + 1) {
			now -> fa = preto;
		} else {
			SAM* sp = new SAM(*preto);
			sp -> len = pre -> len + 1;
			preto -> fa = sp;
			now -> fa = sp;
			while(pre and pre -> ch[x] == preto) {
				pre -> ch[x] = sp;
				pre = pre -> fa;
			}
		}
	} else
		now -> fa = root;
	return now;
}

int main() {
	int n = input();
	SAM *sam = new SAM(0);
	lolong ans = 0;
	for(int i = 1; i <= n; i ++) {
		int a = input();
		sam = sam -> insert(a);
		ans += sam -> len;
		if(sam -> fa) ans -= sam -> fa -> len;
		printf("%lld\n", ans);
	}
}
