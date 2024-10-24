struct Euclid {
    ll f, g, h;
};
Euclid solve(ll a, ll b, ll c, ll n) {
    Euclid ans, tmp;
    if (a == 0) {
        ans.f = (n + 1) * (b / c) % mod;
        ans.g = n * (n + 1) % mod * (b / c) % mod * inv2 % mod;
        ans.h = (n + 1) * (b / c) % mod * (b / c) % mod;
        return ans;
    }
    if (a >= c || b >= c) {
        tmp = solve(a % c, b % c, c, n);
        ans.f = (n * (n + 1) % mod * inv2 % mod * (a / c) % mod + (n + 1) * (b / c) % mod + tmp.f) % mod;
        ans.g = (n * (n + 1) % mod * (2 * n + 1) % mod * (a / c) % mod * inv6 % mod + n * (n + 1) % mod * (b / c) % mod * inv2 % mod + tmp.g) % mod;
        ans.h = ((a / c) * (a / c) % mod * n % mod * (n + 1) % mod * (n * 2 + 1) % mod * inv6 % mod +
                 (b / c) * (b / c) % mod * (n + 1) % mod + (a / c) * (b / c) % mod * n % mod * (n + 1) % mod +
                 2 * (b / c) % mod * tmp.f % mod + 2 * (a / c) % mod * tmp.g % mod + tmp.h) %
                mod;
        return ans;
    }
    ll m = (a * n + b) / c;
    tmp = solve(c, c - b - 1, a, m - 1);
    ans.f = (n * (m % mod) % mod + mod - tmp.f) % mod;
    ans.g = (n * (m % mod) % mod * (n + 1) % mod - tmp.h - tmp.f) % mod * inv2 % mod;
    ans.h = (n * (m % mod) % mod * (m + 1) % mod - 2 * tmp.g - 2 * tmp.f - ans.f) % mod;
    return ans;
}

ans.f = (ans.f % mod + mod) % mod;
ans.g = (ans.g % mod + mod) % mod;
ans.h = (ans.h % mod + mod) % mod;