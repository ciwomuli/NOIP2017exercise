#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
char s1[1000005],s2[1000005];
int f[1000005],n,m;
void getFail(){
    f[0]=0;
    f[1]=0;
    for (int i=1;i<m;i++){
      int j=f[i];
      while (j && s2[j]!=s2[i])
          j=f[j];
      f[i+1]=(s2[i]==s2[j]?j+1:0);
    }
}
void find(){
    int q;
    int j=0; 
    for (int i=0;i<n;i++){
        while (j>0 && s2[j]!=s1[i]) j=f[j];
        if (s2[j]==s1[i]) j++;
        if( j==m ) {
            printf("%d\n",i-m+2);
            j=f[j];
        }
    }
}  
int main(){
    scanf("%s%s",s1,s2);
    n=strlen(s1);
    m=strlen(s2);
    getFail();
    find();
    for (int i=1;i<=m;i++) printf("%d ",f[i]);
}  
