#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define endl putchar('\n')
const int N=5000005;
const double pi=acos(-1);
using namespace std;

struct CP {
	double x,y;
	CP(double X=0,double Y=0) {x=X,y=Y;}
	friend CP operator + (CP a,CP b) {return (CP){a.x+b.x,a.y+b.y};}
	friend CP operator - (CP a,CP b) {return (CP){a.x-b.x,a.y-b.y};}
	friend CP operator * (CP a,CP b) {return (CP){a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x};}
	friend CP operator / (CP a,CP b) {
		double t=b.x*b.x+b.y*b.y;
		return (CP){(a.x*b.x+a.y*b.y)/t,(a.y*b.x-a.x*b.y)/t};
	}
} f[N],g[N];
int n,m,lim=1,r[N];

void fft(CP *f,int tp) {
	rep(i,0,lim-1) if(i<r[i]) swap(f[i],f[r[i]]);
	for(int l=1;l<lim;l<<=1) {
		CP w1(cos(2*pi/(l<<1)),sin(2*pi/(l<<1))*(tp?1:-1));
		for(int i=0;i<lim;i+=l<<1) {
			CP w(1,0);
			for(int j=i;j<i+l;j++,w=w*w1) {
				CP x=f[j],y=w*f[j+l];
				f[j]=x+y,f[j+l]=x-y;
			}
		}
	}
}

int main() {
	scanf("%d%d",&n,&m);
	rep(i,0,n) scanf("%lf",&f[i].x);
	rep(i,0,m) scanf("%lf",&g[i].x);
	while(lim<=n+m) lim<<=1;
	rep(i,0,lim-1) r[i]=(r[i>>1]>>1)|((i&1)?lim>>1:0);
	fft(f,1),fft(g,1);
    for (int i = 0; i < lim; i++) cout << f[i].x << ' ';
    cout << '\n';
    for (int i = 0; i < lim; i++) cout << g[i].x << ' ';
    cout << '\n';
	rep(i,0,lim-1) f[i]=f[i]*g[i];
    for (int i = 0; i < lim; i++) cout << f[i].x << ' ' << f[i].y << ' ';
    cout << '\n';
	fft(f,0);
	rep(i,0,n+m) printf("%d ",int(round(f[i].x/lim)));
	return 0;
}