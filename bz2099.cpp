#if 0
2019.12.27

乍一看像匹配，然而并不是。
对 S 建 SAM ，然后对 T 一个一个扔到 SAM 里面，如果扔不进去说明当前这个 S 已经没用了，
此时必须换个新的 S ，SAM 的指针重新回到开头。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 50005, maxk = 26;
/* int s[maxn], t[maxn]; */
int ch[maxn << 1][maxk], fa[maxn << 1], len[maxn << 1];

int main() {
	int n = read, m = read;

	int cp = 1, last = 1;
	for(int need = n, c = getchar(); need; c = getchar())
		if('A' <= c and c <= 'Z') {
			-- need;
			c -= 'A';

			int now = ++ cp;
			len[now] = len[last] + 1;

			int pre = last;
			while(pre and !ch[pre][c]) {
				ch[pre][c] = now;
				pre = fa[pre];
			}

			if(pre) {
				int preto = ch[pre][c];
				if(len[preto] == len[pre] + 1)
					fa[now] = preto;
				else {
					int sp = ++ cp;
					len[sp] = len[pre] + 1;
					for(int i = 0; i < maxk; i ++)
						ch[sp][i] = ch[preto][i];
					fa[sp] = fa[preto];
					fa[preto] = sp;
					fa[now] = sp;
					while(pre and ch[pre][c] == preto) {
						ch[pre][c] = sp;
						pre = fa[pre];
					}
				}
			}
			else
				fa[now] = 1;

			last = now;
		}

	int pos = 1, ans = 0;
	for(int need = m, c = getchar(); need; c = getchar())
		if('A' <= c and c <= 'Z') {
			-- need;
			c -= 'A';
			pos = ch[pos][c];
			if(!pos) {
				++ ans;
				pos = ch[1][c];
			}
		}

	if(pos != 1) ++ ans;
	printf("%d\n", ans);
}
