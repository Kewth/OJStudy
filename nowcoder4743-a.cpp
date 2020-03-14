#if 0
2020.03.13
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

const int maxn = 1010;
char s[maxn], a[100] = "XiaoQiao", b[100] = "XiaoHuiHui";


int main() {
	scanf("%s", s);
	int ap = 0, bp = 0;
	for(int i = 0; s[i]; i ++) {
		if(s[i] == a[ap])
			++ ap;
		if(s[i] == b[bp])
			++ bp;
	}
	if(a[ap] or b[bp]) puts("emm");
	else puts("Happy");
}

