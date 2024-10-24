#include <bits/stdc++.h>
#define rep(i, a, b) for (R int i = a; i <= b; i++)
#define R register
#define endl putchar('\n')
#define puts putchar(' ')
const int maxn = 5000005;
const long long mod = 1e9 + 7, inv3 = 333333336;
#define int long long
using namespace std;

int n, sqr, vis[maxn], pri[maxn], cnt;
int sp1[maxn], sp2[maxn], w[maxn], tot;
int id1[maxn], id2[maxn], g1[maxn], g2[maxn];

void get_prime(int n) {
    vis[1] = 1;
    rep(i, 2, n) {
        if (!vis[i]) {
            pri[++cnt] = i;
            sp1[cnt] = (sp1[cnt - 1] + i) % mod;
            sp2[cnt] = (sp2[cnt - 1] + 1ll * i * i) % mod;
        }
        for (R int j = 1; j <= cnt && i * pri[j] <= n; j++) {
            vis[i * pri[j]] = 1;
            if (!(i % pri[j])) break;
        }
    }
}

void get_g() {
    for (int i = 1; i <= n;) {
        int j = n / (n / i);
        w[++tot] = n / i;
        g1[tot] = w[tot] % mod;
        g2[tot] = g1[tot] * (g1[tot] + 1) / 2 % mod * (2 * g1[tot] + 1) % mod * inv3 % mod - 1;
        g1[tot] = g1[tot] * (g1[tot] + 1) / 2 % mod - 1;
        if (n / i <= sqr)
            id1[n / i] = tot;
        else
            id2[n / (n / i)] = tot;
        i = j + 1;
    }
    rep(i, 1, cnt) {
        for (int j = 1; j <= tot && pri[i] * pri[i] <= w[j]; j++) {
            int k = w[j] / pri[i] <= sqr ? id1[w[j] / pri[i]] : id2[n / (w[j] / pri[i])];
            g1[j] = (g1[j] - pri[i] * (g1[k] - sp1[i - 1] + mod)) % mod;
            g2[j] = (g2[j] - pri[i] * pri[i] * (g2[k] - sp2[i - 1] + mod)) % mod;
        }
    }
}

int S(int x, int y) {
    if (pri[y] >= x) return 0;
    int k = x <= sqr ? id1[x] : id2[n / x];
    int res = (g2[k] - g1[k] - (sp2[y] - sp1[y]) + mod) % mod;
    for (R int i = y + 1; i <= cnt && pri[i] * pri[i] <= x; i++) {
        int now = pri[i];
        for (R int e = 1; now <= x; e++, now = now * pri[i]) {
            res = (res + now % mod * ((now - 1) % mod) % mod * (S(x / now, i) + (e > 1))) % mod;
        }
    }
    return res;
}

signed main() {
    scanf("%lld", &n);
    sqr = sqrt(n);
    get_prime(sqr);
    get_g();
    printf("%lld", (S(n, 0) + 1) % mod);
    return 0;
}