#if 0
2019.08.10

发现我又学了个假的 AC 自动机。
原来 AC 自动机是离线构造的啊。
原来 AC 自动机 get_fail 是 bfs 啊。
#endif
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

struct Ac {
	Ac *ch[26];
	Ac *fail;
	int val;
	std::vector<Ac *> G;
	inline void get_fail() {
		std::queue<Ac *> q;
		q.push(this);
		while(not q.empty()) {
			Ac *now = q.front();
			q.pop();
			for(int x = 0; x < 26; x ++)
				if(now -> ch[x]) {
					Ac *pre = now -> fail ? now -> fail -> trans(x) : this;
					now -> ch[x] -> fail = pre;
					pre -> G.push_back(now -> ch[x]);
					q.push(now -> ch[x]);
				}
		}
	}
	inline Ac *trans(int x) {
		Ac* now = this;
		while(not now -> ch[x]) {
			if(not now -> fail) return now;
			now = now -> fail;
		}
		return now -> ch[x];
	}
	inline void dfs() {
		// debug("%p: %p, %p, f=%p %d\n", this, ch[0], ch[1], fail, val); fflush(stderr);
		for(Ac *v : G) {
			v -> dfs();
			val += v -> val; 
		}
	}
	inline Ac(): fail(nullptr), val(0), G() {
		for(int i = 0; i < 26; i ++)
			ch[i] = nullptr;
	}
};
const int maxn = 2000005;
char s[maxn], t[maxn];
bool begin[maxn];

int main() {
	int n;
	scanf("%d", &n);
	Ac *root = new Ac();
	int l = 0;
	while(n --) {
		scanf("%s", s + l);
		int r = l + strlen(s + l);
		begin[l] = true;
		Ac *last = root;
		for(int i = l; i < r; i ++) {
			if(not last -> ch[s[i] - 'a'])
				last -> ch[s[i] - 'a'] = new Ac();
			last = last -> ch[s[i] - 'a'];
		}
		l = r;
	}
	root -> get_fail();
	begin[l] = true;
	scanf("%s", t);
	int len = strlen(t);
	Ac *now = root;
	for(int i = 0; i < len; i ++) {
		now = now -> trans(t[i] - 'a');
		// debug("%p: %p, %p, f=%p\n", now, now -> ch[0], now -> ch[1], now -> fail); fflush(stderr);
		now -> val ++;
	}
	// debug("\n");
	root -> dfs();
	for(int i = 0; i < l; i ++)
		if(begin[i]) {
			now = root -> trans(s[i] - 'a');
			for(int j = i + 1; not begin[j]; j ++)
				now = now -> trans(s[j] - 'a');
			printf("%d\n", now -> val);
		}
}

