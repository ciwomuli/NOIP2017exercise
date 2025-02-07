# include <bits/stdc++.h>
# define RG register
# define IL inline
# define Fill(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int _(1e5 + 5);

IL int Input(){
    RG int x = 0, z = 1; RG char c = getchar();
    for(; c < '0' || c > '9'; c = getchar()) z = c == '-' ? -1 : 1;
    for(; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
    return x * z;
}

int rt[_], a[_], n, tot, q[4], id[_];
struct Mx{
    int lmax, rmax, sum, mx;

    IL void Init(){
        lmax = rmax = -_, sum = 0;
    }
} Ans;
struct HJT{
    int ls, rs;
    Mx v;
} T[_ * 20];

IL Mx Merge(RG Mx A, RG Mx B){
    RG Mx C;
    C.lmax = max(A.lmax, A.sum + B.lmax);
    C.rmax = max(B.rmax, A.rmax + B.sum);
    C.sum = A.sum + B.sum;
    return C;
}

IL void Build(RG int &x, RG int l, RG int r){
    x = ++tot;
    T[x].v.lmax = T[x].v.rmax = T[x].v.sum = r - l + 1;
    cout<<x<<" "<<T[x].v.lmax<<" "<<T[x].v.rmax<<" "<<T[x].v.sum<<endl;
    if(l == r) return;
    RG int mid = (l + r) >> 1;
    Build(T[x].ls, l, mid), Build(T[x].rs, mid + 1, r);
}

IL void Modify(RG int &x, RG int l, RG int r, RG int p){
    T[++tot] = T[x], x = tot;
    if(l == r){
        T[x].v.lmax = T[x].v.rmax = T[x].v.sum = -1;
        return;
    }
    RG int mid = (l + r) >> 1;
    if(p <= mid) Modify(T[x].ls, l, mid, p);
    else Modify(T[x].rs, mid + 1, r, p);
    T[x].v = Merge(T[T[x].ls].v, T[T[x].rs].v);
    cout<<x<<" "<<T[x].v.lmax<<" "<<T[x].v.rmax<<" "<<T[x].v.sum<<endl;
}

IL void Query(RG int x, RG int l, RG int r, RG int L, RG int R){
    if(L <= l && R >= r){
        Ans = Merge(Ans, T[x].v);
        return;
    }
    RG int mid = (l + r) >> 1;
    if(L <= mid) Query(T[x].ls, l, mid, L, R);
    if(R > mid) Query(T[x].rs, mid + 1, r, L, R);
}

IL int Check(RG int mid){
    RG int val = 0;
    if(q[1] + 1 <= q[2] - 1) Ans.Init(), Query(rt[mid], 1, n, q[1] + 1, q[2] - 1), val += Ans.sum;
    Ans.Init(), Query(rt[mid], 1, n, q[0], q[1]), val += Ans.rmax;
    Ans.Init(), Query(rt[mid], 1, n, q[2], q[3]), val += Ans.lmax;
    return val >= 0;
}

IL int Cmp(RG int x, RG int y){
    return a[x] < a[y];
}

int main(RG int argc, RG char* argv[]){
    n = Input(), Build(rt[1], 1, n), T[0].v.Init();
    for(RG int i = 1; i <= n; ++i) a[i] = Input(), id[i] = i;
    sort(id + 1, id + n + 1, Cmp);
    for(RG int i = 2; i <= n; ++i) rt[i] = rt[i - 1], Modify(rt[i], 1, n, id[i - 1]);
    for(RG int Q = Input(), ans = 0; Q; --Q){
        for(RG int i = 0; i < 4; ++i) q[i] = (Input() + ans) % n + 1;
        sort(q, q + 4);
        RG int l = 1, r = n;
        while(l <= r){
            RG int mid = (l + r) >> 1;
            if(Check(mid)) ans = a[id[mid]], l = mid + 1;
            else r = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
