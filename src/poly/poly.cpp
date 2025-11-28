const int N=5000005;
const long long mod=998244353;
#define int long long
namespace poly{

const long long G=3, iG=332748118;
int tr[N], lim;
int qpow(int a, int b=mod-2){
  int res=1;
  while (b){
    if (b & 1) (res*=a)%=mod;
    (a*=a)%=mod, b >>= 1;
  }
  return res;
}
void adjust(int n){
  lim=1;
  while (lim <= n) lim <<= 1;
  for(int i=0; i<lim; i++)
   tr[i]=(tr[i >> 1] >> 1) | ((i & 1) ? lim >> 1 : 0);
} // 准备蝶形变换
void copy(int *f, int *g, int n){
  for(int i=0; i <= n; i++) f[i]=g[i]; }
void clear(int *f, int n){ 
  for(int i=0; i <= n; i++) f[i]=0; }
void erase(int *f, int l, int r){
  for(int i=l; i <= r; i++) f[i]=0; }
void reverse(int *f, int n){
  for(int i=0; i <= n/2; i++) swap(f[i], f[n-i]); }
void integral(int *f, int n){
  for(int i=n+1; i >= 1; i--) f[i]=f[i-1]*qpow(i) % mod;
  f[0]=0;
} // 对 n 次多项式 f 求积分，默认常数项为 0 。
void dif(int *f, int n){
  for(int i=0; i<n; i++) f[i]=f[i+1]*(i+1) % mod;
  f[n]=0;
} // 对 n 次多项式 f 求导。
void ntt(int *f, int op){ // op: 1 为 dft ，-1 为 idft 。
  for(int i=0; i<lim; i++)
    if (tr[i]<i) swap(f[tr[i]], f[i]);
  for(int l=1; l<lim; l <<= 1){
    int w1=qpow(op == 1 ? G : iG, (mod-1)/(l << 1));
    for(int i=0; i<lim; i += l << 1){
      for(int j=i, w=1; j<i+l; j++, (w*=w1)%=mod){
        int x=f[j], y=f[j+l]*w % mod;
        f[j]=(x+y) % mod, f[j+l]=(x-y) % mod;
      }
    }
  }
  if (op == -1){
    int iv=qpow(lim); // 算逆元。
    for(int i=0; i<lim; i++) (f[i]*=iv)%=mod;
  }
}
void multiply(int *h, int *f, int n, int *g, int m){
  static int a[N], b[N];
  copy(a, f, n), copy(b, g, m);
  adjust(n+m);
  ntt(a, 1), ntt(b, 1);
  for(int i=0; i<lim; i++) h[i]=a[i]*b[i] % mod;
  ntt(h, -1);
  clear(a, lim-1), clear(b, lim-1);
} // 计算 f 与 g 的积，存放在 h 中，f 与 g 不变。
void inverse(int *f, int *g, int n){
  static int t[N];
  if (!n) return f[0]=qpow(g[0]), void();
  inverse(f, g, n >> 1);
  adjust(2*n), copy(t, g, n);
  ntt(t, 1), ntt(f, 1);
  for(int i=0; i<lim; i++)
    f[i]=f[i]*(2-f[i]*t[i] % mod) % mod;
  ntt(f, -1), erase(f, n+1, lim-1), clear(t, lim-1);
} // 计算 g 的 n 次逆，存放在 f 中，g 不变。不要让 f 和 g 为同一个数组。
void ln(int *f, int *g, int n){
  static int t[N];
  copy(t, g, n), inverse(f, g, n), dif(t, n);
  adjust(n*2), ntt(t, 1), ntt(f, 1);
  for(int i=0; i<lim; i++) (f[i]*=t[i])%=mod;
  ntt(f, -1), integral(f, n);
  erase(f, n+1, lim-1), clear(t, lim-1);
} // 要求 g[0]=1 。
void exp(int *f, int *g, int n){
  static int t[N];
  if (!n) return f[0]=1, void();
  exp(f, g, n >> 1), ln(t, f, n);
  for(int i=0; i <= n; i++) t[i]=(g[i]-t[i]) % mod;
  t[0]++;
  adjust(n*2), ntt(f, 1), ntt(t, 1);
  for(int i=0; i<lim; i++) (f[i]*=t[i])%=mod;
  ntt(f, -1), clear(t, lim-1), erase(f, n+1, lim-1);
} // 要求 g[0]=0 。
void pow(int *f, int *g, int n, int k){
  static int t[N];
  ln(t, g, n);
  for(int i=0; i <= n; i++) (t[i]*=k) % mod;
  exp(f, t, n);
} // 要求 g[0]=1 。
void divide(int *q, int *r, int *f, int n, int *g, int m){
  static int a[N], b[N], c[N];
  copy(a, f, n), copy(b, g, m);
  reverse(a, n), reverse(b, m);
  inverse(c, b, n-m);
  multiply(q, a, n-m, c, n-m);
  reverse(q, n-m);
  multiply(a, g, m, q, n-m);
  for(int i=0; i<m; i++) r[i]=(f[i]-a[i]+mod) % mod;
} // 多项式带余除法，其中 q 为商，r 为余数。
}
using namespace poly;