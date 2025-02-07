//by ciwomuli
//AK JSOI 2019
#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#define LL long long
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
LL dp[15][2];
LL x[15];
int main()
{
    char ch;
    ch = getchar();
    int tot = 0;
    while (isdigit(ch))
    {
        x[++tot] = ch - '0';
        ch = getchar();
    }
    LL ans = x[1];
    dp[1][1] = x[1];
    dp[1][0] = max(1ll, x[1] - 1);
    for (int i = 2; i <= tot; i++)
    {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]) * (x[i] - 1);
        dp[i][0] = max(dp[i][0], dp[i - 1][0] * 9);
        dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]) * x[i];
        ans = max(ans, max(dp[i][0], dp[i][1]));
    }
    cout << ans;
}