#include <bits/stdc++.h>
using namespace std;
int input()
{
    int res ;
    scanf("%d",&res);
    return res;
}
struct Splay
{
    int id , size;
    bool lazy;
    Splay *son[2] , *fa;
    inline int ssize(int r) { return son[r] ? son[r]->size : 0 ; }
    void debug()
    {
        printf("%d:%d,%d\n",id,son[0]?son[0]->id:0,son[1]?son[1]->id:0);
        if(son[0]) son[0]->debug();
        if(son[1]) son[1]->debug();
    }
    void Ans(int n)
    {
        turn();
        if(son[0]) son[0]->Ans(n);
        if(2 <= id && id <= n+1) printf("%d ",id-1);
        if(son[1]) son[1]->Ans(n);
    }
    Splay * Kth(int k)
    {
        //printf("Kth:%d,%d(%d)\n",k,ssize(0),id);
        turn();
        if(k <= ssize(0)) return son[0]->Kth(k);
        if(k == ssize(0)+1) return this;
        if(son[1]) return son[1]->Kth(k-ssize(0)-1);
    }
    void turn()
    {
        if(!lazy) return ;
        swap(son[0] , son[1]);
        lazy = 0;
        if(son[0]) son[0]->lazy^=1;
        if(son[1]) son[1]->lazy^=1;
    }
    void rotate()
    {
        //printf("r%d\n",id);
        //fa->turn();
        bool which = (fa->son[0] == this);
        Splay * pr = fa->fa , * f = fa;
        if(son[which]) son[which]->fa = f;
        fa->son[which^1] = son[which];
        son[which] = f , fa->fa = this;
        if(pr) pr->son[pr->son[1]==f] = this;
        fa = pr;
        size = ssize(0) + ssize(1) + 1;
        f->size = f->ssize(0) + f->ssize(1) + 1;
    }
    void splay(Splay * to)
    {
        //turn();
        while(fa != to)
        {
            if(fa->fa == to) rotate();
            else if((fa->son[0]==this)==(fa->fa->son[0]==fa))
            {
                fa->rotate();
                rotate();
            } else
            {
                rotate();
                rotate();
            }
        }
    }
    Splay(int l,int r):id(l+r>>1),size(1),lazy(0)
    {
        if(l <= id-1) son[0] = new Splay(l,id-1) , son[0]->fa = this , size+=son[0]->size;
        if(id+1 <= r) son[1] = new Splay(id+1,r) , son[1]->fa = this , size+=son[1]->size;
    }
};
int n;
Splay *S = new Splay(1,n = input()+2);
int main()
{
    int q = input();
    while(q--)
    {
        int l = input()+1 , r = input()+1;
        Splay * L = S->Kth(l-1) , * R = S->Kth(r+1);
        L->splay(NULL);
        R->splay(L);
        R->son[0]->lazy ^= 1;
        S = L;
        //S->debug();
    }
    S->Ans(n-2);
}
