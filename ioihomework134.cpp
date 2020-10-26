/*
 * Author: Kewth

 * Date:
  2020.10.17

 * Solution:
  显然不能直接模拟向量运算，但是注意到表达式中出现的向量仅有 X ，并且折叠操作对加法有
分配率，那么总可以用一个关于 X 的多项式来表示一个表达式的值，并且题目中的限制保证了这
个多项式的指数不超过 10 。

 * Digression:
  BNF 真是个好东西。

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 100005, LIM = 10, mod = 1000000000;
int f[LIM + 1];
char s[maxn];
int stack[maxn], sp;
int match[maxn];

struct expression {
	int x[LIM + 1];
	int fold () {
		ll sum = 0;
		for (int k = 0; k <= LIM; k ++)
			sum += 1ll * x[k] * f[k];
		return sum % mod;
	}
	expression (int x0) {
		for (int k = 0; k <= LIM; k ++)
			x[k] = 0;
		x[0] = x0;
	}
} X = 0;

expression operator - (expression a) {
	for (int k = 0; k <= LIM; k ++)
		a.x[k] = mod - a.x[k];
	return a;
}

expression operator + (expression a, expression b) {
	for (int k = 0; k <= LIM; k ++)
		(a.x[k] += b.x[k]) %= mod;
	return a;
}

expression operator * (expression a, expression b) {
	expression c = 0;
	for (int i = 0; i <= LIM; i ++)
		for (int j = 0; i + j <= LIM; j ++)
			c.x[i + j] = (c.x[i + j] + 1ll * a.x[i] * b.x[j]) % mod;
	return c;
}

int n;
expression solve (int l, int r) {
	// operation + expression
	if (s[l] == '-') return - solve(l + 1, r);
	if (s[l] == '*') {
		expression tmp = solve(l + 2, r);
		return tmp * tmp;
	}
	if (s[l] == '+') return solve(l + 2, r).fold();

	// term | term + operation + expression
	expression term = 0;
	int p = 0;
	if (s[l] == '(') term = solve(l + 1, match[l] - 1), p = match[l] + 1;
	if (s[l] == 'X') term = X, p = l + 1;
	if (s[l] == 'N') term = n, p = l + 1;
	if (isdigit(s[l])) {
		int number = s[l] - '0';
		p = l + 1;
		while (isdigit(s[p]))
			number = number * 10 + s[p ++] - '0';
		term = number;
	}

	// term
	if (p == r + 1) return term;

	// term + operation + expression
	if (s[p] == '+') return term + solve(p + 1, r);
	if (s[p] == '-') return term + - solve(p + 1, r);
	if (s[p] == '*') return term * solve(p + 1, r);

	debug("ERROR\n");
	return 0;
}

int main () {
	read(n);
	for (int i = 1; i <= n; i ++) {
		int x = 1, y = read;
		for (int k = 0; k <= LIM; k ++) {
			(f[k] += x) %= mod;
			x = 1ll * x * y % mod;
		}
	}
	X.x[1] = 1;

	scanf("%s", s + 1);
	int m = int(strlen(s + 1));
	for (int i = 1; i <= m; i ++)
		if (s[i] == '(')
			stack[++ sp] = i;
		else if (s[i] == ')') {
			int j = stack[sp --];
			match[i] = j;
			match[j] = i;
		}

	printf("%d\n", solve(1, m).x[0]);
}
