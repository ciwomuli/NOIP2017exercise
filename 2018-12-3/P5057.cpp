#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#define LL long long
#define P pair<int,int>
using namespace std;
template <typename T>
inline void read(T &t)
{
    int f = 0, c = getchar();
    t = 0;
    while (!isdigit(c))
        f |= c == '-', c = getchar();
    while (isdigit(c))
        t = t * 10 + c - 48, c = getchar();
    if (f)
        t = -t;
}
template <typename T, typename... Args>
inline void read(T &t, Args &... args)
{
    read(t);
    read(args...);
}
const int maxn=500005;
int lch[maxn<<2],rch[maxn<<2];
bool rev[maxn];
int tot;
void pushdown(int cur){
    if(rev[cur]){
    	rev[lch[cur]]^=1;
    	rev[rch[cur]]^=1;
		rev[cur]=0;
	}
}
void build(int &cur,int l,int r){
    cur=++tot;
    if(l==r){
    	rev[cur]=0;
        return;
    }
    int mid=(l+r)>>1;
    build(lch[cur],l,mid);
    build(rch[cur],mid+1,r);
}
void modify(int cur,int l,int r,int ml,int mr){
    if(ml<=l && r<=mr){
        rev[cur]^=1;
        return;
    }
    int mid=(l+r)>>1;
    pushdown(cur);
    if(ml<=mid) modify(lch[cur],l,mid,ml,mr);
    if(mr>=mid+1) modify(rch[cur],mid+1,r,ml,mr);
}
bool qurry(int cur,int l,int r,int a){
    LL ans=0;
    if(l==r) return rev[cur]; 
    int mid=(l+r)>>1;
    pushdown(cur);
    if(a<=mid) return qurry(lch[cur],l,mid,a);
    if(a>=mid+1) return qurry(rch[cur],mid+1,r,a);
}
int n,m;
int root;
int main(){
    read(n,m);
    build(root,1,n);
    for(int i=1;i<=m;i++){
        int t,x,y;
        read(t);
        if(t==1){
        	read(x,y);
            modify(root,1,n,x,y);
        }else{
        	read(x);
            printf("%d\n",(int)qurry(root,1,n,x));
        }
    }
}
