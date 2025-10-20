struct P {
    LD x, y;

    P(const LD &x = 0, const LD &y = 0) : x(x), y(y) {}
    P(cp a) : x(a.x), y(a.y) {}

    P operator=(cp a) {
        x = a.x, y = a.y;
        return *this;
    }
    P rot(LD t) const {
        LD c = cos(t), s = sin(t);
        return P(x * c - y * s, x * s + y * c);
    } // counterclockwise
    P rot90() const { return P(-y, x); } // counterclockwise
    P _rot90() const { return P(y, -x); } // clockwise
    LD len() const { return sqrtl(x * x + y * y); }
    LD len2() const { return x * x + y * y; }
    P unit() const {
        LD d = len();
        return P(x / d, y / d);
    }
    void read() { scanf("%Lf%Lf", &x, &y); }
    void print() const { printf("(%.9Lf,%.9Lf)", x, y); }
};

bool operator<(cp a, cp b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
bool operator>(cp a, cp b) { return a.x == b.x ? a.y > b.y : a.x > b.x; }
bool operator==(cp a, cp b) { return !sgn(a.x - b.x) && !sgn(a.y - b.y); }
P operator+(cp a, cp b) { return P(a.x + b.x, a.y + b.y); }
P operator-(cp a, cp b) { return P(a.x - b.x, a.y - b.y); }
P operator*(const LD &a, cp b) { return P(a * b.x, a * b.y); }
P operator*(cp b, const LD &a) { return P(a * b.x, a * b.y); }
P operator/(cp b, const LD &a) { return P(b.x / a, b.y / a); }
LD operator*(cp a, cp b) { return a.x * b.x + a.y * b.y; }                                                             // 点积
LD operator^(cp a, cp b) { return a.x * b.y - a.y * b.x; }                                                             // 叉积
LD rad(cp a, cp b) { return acosl((a.x == 0 && a.y == 0 || b.x == 0 && b.y == 0) ? 0 : (a * b / a.len() / b.len())); } // 夹角 其中有零向量时返回0
bool left(cp a, cp b) { return sgn(a ^ b) > 0; }                                                                       // 没什么用