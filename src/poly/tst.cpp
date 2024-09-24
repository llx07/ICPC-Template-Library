#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define endl putchar('\n')
const int N=5000005;
const double pi=acos(-1);
using namespace std;

struct comp {
    double x, y;
    comp(double X = 0, double Y = 0) { x = X, y = Y; }
    comp operator + (const comp &rhs) const { return comp(x + rhs.x, y + rhs.y); }
    comp operator - (const comp &rhs) const { return comp(x - rhs.x, y - rhs.y); }
    comp operator * (const comp &rhs) const { return comp(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
    comp operator / (const comp &rhs) const {
        double t = rhs.x * rhs.x + rhs.y * rhs.y;
        return {(x * rhs.x + y * rhs.y) / t, (y * rhs.x - x * rhs.y) / t};
    }
} f[N], g[N];
// const double pi = acos(-1);
int n, m, lim = 1, tr[N];
void adjust(int n) { // n: 多项式的次数。
    lim = 1;
    while (lim <= n) lim <<= 1;
    for (int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? lim >> 1 : 0);
} // 准备蝶形变换。
void fft(comp *f, int op) { // op: 1 为 dft ，-1 为 idft 。
    for (int i = 0; i < lim; i++) if (tr[i] < i) swap(f[tr[i]], f[i]);
    for (int l = 1; l < lim; l <<= 1) {
        comp w1(cos(2 * pi / (l << 1)), sin(2 * pi / (l << 1)) * op);
        for (int i = 0; i < lim; i += l << 1) {
            comp w(1, 0);
            for (int j = i; j < i + l; j++, w = w * w1) {
                comp x = f[j], y = f[j + l] * w;
                f[j] = x + y, f[j + l] = x - y;
            }
        }
    }
    if (op == -1) {
        for (int i = 0; i < lim; i++) f[i].x /= lim;
    }
}

int main() {
	scanf("%d%d",&n,&m);
	rep(i,0,n) scanf("%lf",&f[i].x);
	rep(i,0,m) scanf("%lf",&g[i].x);
	// while(lim<=n+m) lim<<=1;
	// rep(i,0,lim-1) r[i]=(r[i>>1]>>1)|((i&1)?lim>>1:0);
    adjust(n + m);
	fft(f,1),fft(g,1);
    // for (int i = 0; i < lim; i++) cout << f[i].x << ' ';
    // cout << '\n';
    // for (int i = 0; i < lim; i++) cout << g[i].x << ' ';
    // cout << '\n';
	rep(i,0,lim-1) f[i]=f[i]*g[i];
    // for (int i = 0; i < lim; i++) cout << f[i].x << ' ' << f[i].y << ' ';
    // cout << '\n';
	fft(f,-1);
	rep(i,0,n+m) printf("%d ",int(round(f[i].x)));
	return 0;
}