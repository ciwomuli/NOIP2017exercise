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
const int maxn = 35;
int S[maxn];
int main(){
    int t;
    read(t);
    for(int i=1;i<=9;i++)
        S[i] = i;
    for (int i = 10; i <= 30;i++){
        int sum=0;
        int tmp=i;
        while(tmp){
            sum+=tmp%10;
            tmp /= 10;
        }
        S[i] = S[sum];
        cout << i<<" "<< S[i] << endl;
    }
}