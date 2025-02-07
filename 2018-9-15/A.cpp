#include<iostream>
#include <cmath>
#include <map>
#define LL long long
using namespace std;
LL mul_mod(LL a,LL b,int n){
    return a * b % n;
}
LL pow_mod(LL a,LL p,int n){
    if(p==0) return 1;
    LL ans=(pow_mod(a,p/2,n));
    ans = ans * ans % n;
    if(p%2==1) ans=ans*a%n;
    return ans;
}
void exgcd(LL a,LL b,LL &d,LL &x,LL &y){
	d=a;
	if(b!=0){
		exgcd(b,a%b,d,y,x);
		y-=(a/b)*x;
	}else{
		x=1;
		y=0;
	}
}
LL inv(LL a,LL n){
    LL d,x,y;
    exgcd(a,n,d,x,y);
    return d == 1 ? (x + n) % n : -1;
}
int log_mod(int a,int b,int n){
    int m,v,e=1,i;
    m = (int)sqrt(n + 0.5);
    v=inv(pow_mod(a,m,n),n);
    map<int, int> x;
    x[1]=0;
    for(int i=1;i<m;i++){
        e=mul_mod(e,a,n);
        if(!x.count(e))
            x[e] = i;
    }
    for(int i=0;i<m;i++){
        if(x.count(b)) return i*m+x[b];
        b = mul_mod(b, v, n);
    }
    return -1;
}
int main(){
    int k,m;
    cin>>k>>m;
    cout << log_mod(10, (9 * k + 1) % m, m);
    return 0;
}