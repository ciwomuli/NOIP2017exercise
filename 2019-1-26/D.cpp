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
#include <bitset>
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
const int maxn = 5220;
bitset<maxn> b[maxn];
int main(){
    int n;
    read(n);
    for(int i=1;i<=n;i++){
        for (int j = 1; j < n;j+=4){
            char ch=getchar();
            while(isspace(ch))
                ch = getchar();
            if(ch=='8' || ch=='9' || ch=='A' || ch=='B' || ch=='C' || ch=='D' || ch=='E' || ch=='F')
                b[i][j] = 1;
            if(ch=='4' || ch=='5' || ch=='6' || ch=='7' || ch=='C' || ch=='D' || ch=='E' || ch=='F')
                b[i][j+1] = 1;
            if(ch=='2' || ch=='3' || ch=='6' || ch=='7' || ch=='A' || ch=='B' || ch=='E' || ch=='F')
                b[i][j+2] = 1;
            if(ch=='1' || ch=='3' || ch=='5' || ch=='7' || ch=='9' || ch=='B' || ch=='D' || ch=='F')
                b[i][j+3] = 1;
        }
    }
    for (int ans = n; ans >= 2;ans--){
        if (n % ans != 0)
            continue;
        bool ok=true;
        for (int i = 1; i < n;i+=ans){
            for (int j = i+1; j < i + ans;j++){
                ok &= (b[j] == b[i]);
            }
            if(!ok)
                break;
            for (int j = 1; j < n;j+=ans){
                for (int k = j+1; k < j + ans;k++)
                    ok &= (b[i][k] == b[i][k - 1]);
                if(!ok)
                    break;
            }
        }
        if(ok){
            cout << ans << endl;
            return 0;
        }
    }
    puts("1");
}