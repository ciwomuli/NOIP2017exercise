#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#define INF 0x7fffffff
using namespace std;

const int Maxt = 32;
const int Maxn = 3610;
const int Maxm = Maxn * 5;
int n,m,p;
bool a[Maxt][Maxt],vis[Maxn];
int dx[4] = {-1,0,1, 0},
    dy[4] = { 0,1,0,-1};
int predis[Maxt][Maxt],dis[Maxn];

struct game {
    int next,to,w;
}e[Maxm];
int top,head[Maxn];
void add(int u,int v,int val) {
    cout << u << " " << v << " " << val << endl;
    top++;
    e[top].to=v;
    e[top].w=val;
    e[top].next=head[u];
    head[u]=top;
}

struct start {
    int x,y;
} nxt,cur;
queue<start>q;
queue<int>que;

int numbers(int i,int j) {
    /*
    因为固定一个指定块之后的状态对应着5种状态,
    都是不同的状态,所以要开5倍,即必须编号多编 
    */
    j--; ///从0开始编号 
    return (i-1)*m+j<<2;
//  return (i-1)*m+j<<2;
    ///如果像这样从1开始编号的话,我们的存图的struct game e数组就需要多开5个空间!!!所以还是最好从0编号好 
}

void bfs(int ex,int ey,int px,int py,int d) {
    int cx,cy,nx,ny; 
    memset(predis,-1,sizeof(predis));
    /*
        predis数组表示啥呢??? 
        其实简单来说就是:
        固定指定块,空白块在指定块的其中一个方向
        然后再由这个状态到其他状态的最短路
        没错!储存的就是最短路的距离!!! 
        其他状态是指:
        固定了指定块之后,空白块在指定块的另外三个方向
    */
    ///指定格  
    predis[px][py]=1;
    ///空白格
    predis[ex][ey]=0;
    ///bfs当前空白格移动到每个点所需要的步数 
    cur.x=ex,cur.y=ey;
    q.push(cur);
    while(!q.empty()) {
        cur=q.front();
        q.pop();
        cx=cur.x,cy=cur.y;
        for(int i=0; i<4; ++i) {
            nx=cur.x+dx[i],ny=cur.y+dy[i];
            if(a[nx][ny] && predis[nx][ny]==-1) {
                predis[nx][ny]=predis[cx][cy]+1;
                nxt.x=nx,nxt.y=ny;
                q.push(nxt);
            }
        }
    }
    ///如刚才所述 
    if(d==8) return;
    int tmp=numbers(px,py);
    for(int i=0; i<4; ++i) {
        int x=px+dx[i],y=py+dy[i];
        if(predis[x][y]>0)
        /*
        因为在之前已经把predis[ex][ey]赋值为0,
        所以这个条件就是相当于当前枚举的这个指定块与空白块的状态,
        与它的后继状态进行连边 
        */
            /*----------这里重要----------*/ 
            add(tmp+d,tmp+i,predis[x][y]);
            /*----------真的重要----------*/
    }
    /*
    最后一种后继状态是指定格与空白格交换位置
    因为规定的0123是上右下左,所以(d+2)%4可以直接转化为对面的方向
    交换相当于走一步,所以边权为1 
    */
    add(tmp+d,numbers(ex,ey)+(d+2)%4,1);
}

void spfa(int sx,int sy) {
    int tmp;
    memset(dis,-1,sizeof(dis));
    for(int i=0; i<4; ++i) {
        int x=sx+dx[i],y=sy+dy[i];
        if(predis[x][y]!=-1) {
            tmp=numbers(sx,sy)+i;
            dis[tmp]=predis[x][y];
            que.push(tmp);
        }
    }
    int u;
    while(!que.empty()) {
        u=que.front();
        que.pop();
        vis[u]=false;
        for(int i=head[u]; i; i=e[i].next) {
            int v=e[i].to;
            if(dis[v]==-1 || dis[v]>dis[u]+e[i].w) {
                dis[v]=dis[u]+e[i].w;
                if(!vis[v]) {
                    vis[v]=true;
                    que.push(v);
                }
            }
        }
    }
} 

int main() {
    scanf("%d%d%d",&n,&m,&p);
    ///枚举并固定指定格 
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=m; ++j)
            scanf("%d",&a[i][j]);
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=m; ++j)
            if(a[i][j]) {
                ///枚举固定空白格,上,右,下,左(顺时针旋转,方便进行转换) 
                ///bfs在固定指定格与空白格的5种状态 
                if(a[i-1][j]) bfs(i-1,j,i,j,0); 
                if(a[i][j+1]) bfs(i,j+1,i,j,1);
                if(a[i+1][j]) bfs(i+1,j,i,j,2);
                if(a[i][j-1]) bfs(i,j-1,i,j,3);
            }
    /*
    空白格：ex,ey 
    指定格的初始位置：sx,sy 
    目标位置：tx,ty 
    */
    int ex,ey,sx,sy,tx,ty,ans;
    while(p--) {
        scanf("%d%d%d%d%d%d",&ex,&ey,&sx,&sy,&tx,&ty);
        if(sx==tx && sy==ty) {
            printf("0\n");
            continue;
        }
        /*-----------最后一次bfs-----------*/
        /*
        因为我们是直接枚举空白快与指定块连接在一起的状态,
        但是他们其实有可能初始状态并没有连接,
        所以强行将她们进行连接,
        但是不在图中进行连边,
        所以随便弄个d,如果bfd之后要建边了,
        若是胡乱搞的这个d,直接return即可 
        */ 
        bfs(ex,ey,sx,sy,8);
        ///普♂通♀的spfa,跑最短路 
        spfa(sx,sy);
        ans=INF;
        ///将目标位置进行编号 
        int tmp=numbers(tx,ty);
        for(int i=0; i<4; ++i)
            ///+i是空白块的状态方向
            if(dis[tmp+i]!=-1) 
                ///往小里面更新 
                ans=min(ans,dis[tmp+i]);
        if(ans==INF)
            ans=-1;
        printf("%d\n",ans); 
    }
    return 0;
}