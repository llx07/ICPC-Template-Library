ll solve(ll a, ll b, ll c, ll n) {
    if (a == 0) return (n + 1) * (b / c) % mod;
    if (a >= c || b >= c)
        return (n * (n + 1) % mod * inv2 % mod * (a / c) % mod + (n + 1) * (b / c) % mod + solve(a % c, b % c, c, n)) % mod;
    ll m = (a * n + b) / c;
    return (n * (m % mod) % mod - solve(c, c - b - 1, a, m - 1) + mod) % mod;
}