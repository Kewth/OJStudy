#if 0
2019.08.23

逐位贪心即可，特判 0 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline unsigned input() { unsigned x; scanf("%u", &x); return x; }

int main() {
	int T = int(input());

	while(T --) {
		unsigned a = input(), b = input(), c = 0, min;

		for(int k = 31; k >= 0; k --)
			if((a >> k & 1) and (b >> k & 1))
				c |= 1u << k;
			else if((a >> k & 1) ^ (b >> k & 1))
				min = 1u << k;

		if(not c)
			c |= min;

		printf("%u\n", c);
	}
}
