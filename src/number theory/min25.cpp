#include<bits/stdc++.h>
using namespace std;

using ll=long long;

const ll mod = 1e9+7;
constexpr ll ksm(ll a,ll b){
    ll r = 1;
    while(b){
        if(b&1)r=r*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return r;
}
constexpr ll inv2 = ksm(2, mod-2);
constexpr ll inv6 = ksm(6, mod-2);

constexpr ll sq(ll n){n%=mod;return n*n%mod;}
constexpr ll sum(ll n){n%=mod;return n*(n+1)%mod*inv2%mod;}
constexpr ll sum_sq(ll n){n%=mod;return n*(n+1)%mod*(2*n+1)%mod*inv6%mod;}

const int N = 2e5+5;


ll p[N],tot; bool vis[N];
void init_sieve(){
    for(int i=2;i<N;i++){
        if(!vis[i])p[++tot]=i;
        for(int j=1;j<=tot && i*p[j]<N;j++){
            vis[i*p[j]]=1;
            if(i%p[j]==0)break;
        }
    }
}

ll v[N],m;
int id1[N],id2[N];
ll g1[N],g2[N];
ll n;
ll get(ll x){
    return x<N?id1[x]:id2[n/x];
}
void init_sqrt(){
    for(ll l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        v[++m]=n/l;
        if(v[m]<N)id1[v[m]]=m;
        else id2[n/v[m]]=m;
        g1[m]=(sum_sq(v[m])+mod-1)%mod, g2[m]=(sum(v[m])+mod-1)%mod;
    }
}

void calc_g(){
    for(int j=1;j<=tot;j++){
        for(int i=1;i<=m && p[j]<=v[i]/p[j];i++){
            g1[i] = (g1[i] - sq(p[j])*g1[get(v[i]/p[j])]%mod + sq(p[j])*g1[get(p[j-1])] + mod) % mod;
            g2[i] = (g2[i] - p[j]*g2[get(v[i]/p[j])]%mod + p[j]*g2[get(p[j-1])] + mod) % mod;
        }
    }
}

ll f(ll x){x%=mod;return (x*x%mod-x+mod)%mod;}

/* 做法一部分 */
ll S(ll x,int j){
    if(p[j] >= x) return 0;
    ll res = (g1[get(x)] - g2[get(x)] - g1[get(p[j])] + g2[get(p[j])]+ mod + mod) % mod;
    for(int k=j+1;k<=tot && p[k]<=x/p[k];k++){
        ll w = p[k];
        for(;w<=x/p[k];w*=p[k]){
            res = (res + f(w) * S(x/w, k)%mod + f(w*p[k]))%mod;
        }
    }
    return res;
}  
/* 做法一部分 */ 

/* 做法二部分 */
ll g[N],S[N];
/* 做法二部分 */

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    init_sieve();
    init_sqrt();
    calc_g();

/* 做法一部分 */ 
    cout << ((S(n, 0) + 1)%mod+mod)%mod << '\n';
/* 做法一部分 */ 

/* 做法二部分 */
    for(int i=1;i<=m;i++)S[i]=g[i]=(g1[i]-g2[i]+mod)%mod;
    for(int j=tot-1;j>=0;j--){
        for(int i=1;i<=m && p[j+1]<=v[i]/p[j+1];i++){
            for(ll w=p[j+1];w<=v[i]/p[j+1];w*=p[j+1]){
                S[i] = (S[i] + f(w) * (S[get(v[i]/w)] - g[get(p[j+1])] + mod) % mod + f(w*p[j+1]))%mod;
            }
        }
    }
    cout << S[get(n)]+1 << '\n';
/* 做法二部分 */
    return 0;
}