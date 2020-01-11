#if 0
2020.01.10
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

char s[5][5];

bool check(char x) {
	for(int i = 0; i < 3; i ++)
		if(s[i][0] == x and s[i][1] == x and s[i][2] == x)
			return 1;
	for(int i = 0; i < 3; i ++)
		if(s[0][i] == x and s[1][i] == x and s[2][i] == x)
			return 1;
	if(s[0][0] == x and s[1][1] == x and s[2][2] == x)
		return 1;
	if(s[0][2] == x and s[1][1] == x and s[2][0] == x)
		return 1;
	return 0;
}

int main() {
	int T = read;
	while(T --) {
		scanf("%s", s[0]);
		scanf("%s", s[1]);
		scanf("%s", s[2]);
		if(check('A') and check('B')) puts("invalid");
		else if(check('A')) puts("Yes");
		else if(check('B')) puts("No");
		else puts("draw");
	}
}
