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
const int maxn = 2e5 + 5;
int a[maxn];
priority_queue<LL> q;
int main(){
    int n,k;
    read(n, k);
    for (int i = 1;i<=n;i++) read(a[i]);
    LL ans = 0;
    int last = 0;
    for (int i = 1;i<=n;i++) {
        int ch=getchar()-'a';
        if(ch!=last){
            int cnt=k;
            while(cnt>0 && !q.empty()){
                ans+=q.top();
                q.pop();
                cnt--;
            }
            while(!q.empty())
                q.pop();
            last = ch;
        }
        q.push(a[i]);
    }
    int cnt=k;
    while(cnt>0 && !q.empty()){
        ans+=q.top();
        q.pop();
        cnt--;
    }
    while(!q.empty())
        q.pop();
    cout << ans;
}