#if 0
2019.09.09

突然发现 Treap 做以权值为键的平衡树时候巨好写写起来巨舒服。
获得成就：平衡树一遍过
虽然还是写了 40min+ 。

然后发现 IO 是真的耗时，
源程序 470ms -> IO 优化 -> 270 ms 。
我去 IO 一个数顶的上 Treap 一个 O(log) 的操作。。。。
#endif
#include <cstdio>
#include <cstdlib>

const int _I_Buffer_Size(1 << 23);
char _I_Buffer[_I_Buffer_Size];
char *_I_pos = _I_Buffer;

const int _O_Buffer_Size(1 << 23);
char _O_Buffer[_O_Buffer_Size];
char *_O_pos = _O_Buffer;

inline bool is_digit(const char ch) { return '0' <= ch && ch <= '9'; }

inline int getint() {
    int res(0);
    static char ch;
    bool neg(false);
    while (ch = *_I_pos++, !is_digit(ch)) neg = ch == '-';
    do
        (res *= 10) += ch & 15;
    while (ch = *_I_pos++, is_digit(ch));
    return neg ? -res : res;
}

inline char getop() {
    static char ch;
    while (ch = *_I_pos++, !is_digit(ch))
        ;
    return ch & 15;
}

inline void putint(int n) {
    char _buf[10];
    char *_pos(_buf);
    if (n < 0)
        *_O_pos++ = '-', n = -n;
    do
        *_pos++ = '0' | n % 10;
    while (n /= 10);
    while (_pos != _buf) *_O_pos++ = *--_pos;
	*_O_pos++ = '\n';
}

#define input getint

struct Treap;
Treap *null;

struct Treap {
    int val, times, size, weight;
    Treap *lt, *rt;

    inline void update() { size = times + lt->size + rt->size; }

    void split(int v, Treap *&a, Treap *&b) {
        if (this == null)
            a = b = null;

        else {
            if (v < val) {
                lt->split(v, a, lt);
                b = this;
            } else {
                rt->split(v, rt, b);
                a = this;
            }
            update();
        }
    }

    int kth(int k) {
        if (k <= lt->size)
            return lt->kth(k);
        if (k <= lt->size + times)
            return val;
        return rt->kth(k - lt->size - times);
    }

    Treap(int val, int times) : val(val), times(times), size(times), weight(rand()), lt(null), rt(null) {}
};

Treap *merge(Treap *a, Treap *b) {
    if (a == null)
        return b;
    if (b == null)
        return a;

    if (a->weight > b->weight) {
        a->rt = merge(a->rt, b);
        a->update();
        return a;
    } else {
        b->lt = merge(a, b->lt);
        b->update();
        return b;
    }
}

int main() {
    fread(_I_Buffer, 1, _I_Buffer_Size, stdin);
    null = new Treap(0, 0);

    int q = input();
    Treap *T = new Treap(0, 0);

    while (q--) {
        int t = input(), x = input();

        if (t == 1 or t == 2) {
            Treap *a, *b, *c;
            T->split(x - 1, a, b);
            b->split(x, b, c);

            if (t == 1) {
                if (b == null)
                    b = new Treap(x, 1);
                else
                    b->times++;
            } else {
                if (b->times == 1)
                    b = null;
                else
                    b->times--;
            }

            T = merge(a, merge(b, c));
        }

        else if (t == 3) {
            Treap *a, *b;
            T->split(x - 1, a, b);
            putint(a->size + 1);
            T = merge(a, b);
        }

        else if (t == 4)
            putint(T->kth(x));

        else if (t == 5) {
            Treap *a, *b;
            T->split(x - 1, a, b);
            putint(a->kth(a->size));
            T = merge(a, b);
        }

        else if (t == 6) {
            Treap *a, *b;
            T->split(x, a, b);
            putint(b->kth(1));
            T = merge(a, b);
        }
    }

    fwrite(_O_Buffer, 1, _O_pos - _O_Buffer, stdout);
}
