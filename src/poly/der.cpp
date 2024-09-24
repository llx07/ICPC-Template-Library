#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define endl putchar('\n')
const int N=5000005;
const long long mod=998244353,G=3,iG=332748118;
#define int long long
using namespace std;

int n,m,f[N],g[N];

namespace poly {
	int tr[N],lim;
	int qpow(int a,int b=mod-2) { int res=1; while(b) { if(b&1) (res*=a)%=mod; (a*=a)%=mod,b>>=1; } return res; }
	void adjust(int n) {
		lim=1; while(lim<=n) lim<<=1;
		rep(i,0,lim-1) tr[i]=(tr[i>>1]>>1)|((i&1)?lim>>1:0);
	}
	void copy(int *f,int *g,int n) { rep(i,0,n) f[i]=g[i]; }
	void clear(int *f,int n) { rep(i,0,n) f[i]=0; }
	void erase(int *f,int l,int r) { rep(i,l,r) f[i]=0; }
	void integral(int *f,int n) {
		for(int i=n+1;i>=1;i--) f[i]=f[i-1]*qpow(i)%mod; f[0]=0;
	}
	void dif(int *f,int n) {
		rep(i,0,n-1) f[i]=f[i+1]*(i+1)%mod; f[n]=0;
	}
	void ntt(int *f,int op) {
		rep(i,0,lim-1) if(tr[i]<i) swap(f[tr[i]],f[i]);
		for(int l=1;l<lim;l<<=1) {
			int w1=qpow(op?G:iG,(mod-1)/(l<<1));
			for(int i=0;i<lim;i+=l<<1) {
				for(int j=i,w=1;j<i+l;j++,(w*=w1)%=mod) {
					int x=f[j],y=f[j+l]*w%mod;
					f[j]=(x+y)%mod,f[j+l]=(x-y)%mod;
				}
			}
		}
		if(!op) {
			int iv=qpow(lim);
			rep(i,0,lim-1) (f[i]*=iv)%=mod;
		}
	}
	void inverse(int *f,int *g,int n) {
		static int t[N];
		if(!n) return f[0]=qpow(g[0]),void();
		inverse(f,g,n>>1);
		adjust(2*n),copy(t,g,n);//ѭ������ 
		ntt(t,1),ntt(f,1);
		rep(i,0,lim-1) f[i]=f[i]*(2-f[i]*t[i]%mod)%mod;
		ntt(f,0),erase(f,n+1,lim-1),clear(t,lim-1);
	}
	void ln(int *f,int *g,int n) {
		static int t[N];
		copy(t,g,n),inverse(f,g,n),dif(t,n);
		adjust(n*2),ntt(t,1),ntt(f,1);
		rep(i,0,lim-1) (f[i]*=t[i])%=mod;
		ntt(f,0),integral(f,n);
		erase(f,n+1,lim-1),clear(t,lim-1);
	}
	void exp(int *f,int *g,int n) {
		static int t[N];
		if(!n) return f[0]=1,void();
		exp(f,g,n>>1),ln(t,f,n);
		rep(i,0,n) t[i]=(g[i]-t[i])%mod; t[0]++;
		adjust(n*2),ntt(f,1),ntt(t,1);
		rep(i,0,lim-1) (f[i]*=t[i])%=mod;
		ntt(f,0),clear(t,lim-1),erase(f,n+1,lim-1);
	}
}
using namespace poly;

signed main() {
	scanf("%lld%lld", &n, &m);
    for (int i = 0; i <= n; i++) scanf("%lld", &f[i]);
    for (int i = 0; i <= m; i++) scanf("%lld", &g[i]);
    adjust(n + m);
    ntt(f, 1), ntt(g, 1);
    for (int i = 0; i <= lim; i++) f[i] = f[i] * g[i] % mod;
    ntt(f, 0);
    for (int i = 0; i <= n + m; i++) printf("%lld ", (f[i] + mod) % mod);
	return 0;
}
