#define cp const P&
#define cl const L&
#define cc const C&
#define vp vector<P>
#define cvp const vector<P>&
#define D double
#define LD long double
std::mt19937 rnd(time(0));
const LD eps = 1e-12;
const LD pi = std::numbers::pi;
const LD INF = 1e9;
int sgn(LD x) {
    return x > eps ? 1 : (x < -eps ? -1 : 0);
}