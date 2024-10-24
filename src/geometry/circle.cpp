struct C {
    P c;
    LD r;

    C(cp c, const LD &r = 0) : c(c), r(r) {}
    C(cc a) : c(a.c), r(a.r) {};
    C(cp a, cp b) {
        c = (a + b) / 2;
        r = (a - c).len();
    }
    C(cp x, cp y, cp z) {
        P p(y - x), q(z - x);
        P s(p * p / 2, q * q / 2);
        LD d = p ^ q;
        p = P(s ^ P(p.y, q.y), P(p.x, q.x) ^ s) / d;
        c = x + p, r = p.len();
    }
};

bool in_circle(cp a, cc b) { return sgn((b.c - a).len() - b.r) <= 0; }
C min_circle(vp p) // O(n)
{
    shuffle(p.begin(), p.end(), rnd);
    int n = p.size(), i, j, k;
    C ret(p[0], 0);
    for (i = 1; i < n; ++i)
        if (!in_circle(p[i], ret))
            for (ret = C(p[i], p[0]), j = 1; j < i; ++j)
                if (!in_circle(p[j], ret))
                    for (ret = C(p[i], p[j]), k = 0; k < j; ++k)
                        if (!in_circle(p[k], ret))
                            ret = C(p[i], p[j], p[k]);
    return ret;
}

vp lc_intersection(cl l, cc c) {
    LD x = point_to_line(c.c, l);
    if (sgn(x - c.r) > 0) return vp();
    x = sqrtl(c.r * c.r - x * x);
    P p(project_to_line(c.c, l));
    if (sgn(x) == 0) return vp({p});
    return vp({p + x * (l.t - l.s).unit(), p - x * (l.t - l.s).unit()});
}

LD cc_intersection_area(cc a, cc b) {
    LD d = (a.c - b.c).len();
    if (sgn(d - (a.r + b.r)) >= 0) return 0;
    if (sgn(d - fabs(a.r - b.r)) <= 0) {
        LD r = min(a.r, b.r);
        return pi * r * r;
    }
    LD x = (d * d + a.r * a.r - b.r * b.r) / (2 * d), t1 = acosl(min((LD)1, max((LD)-1, x / a.r))), t2 = acosl(min((LD)1, max((LD)-1, (d - x) / b.r)));
    return a.r * a.r * t1 + b.r * b.r * t2 - d * a.r * sinl(t1);
}

vp cc_intersection(cc a, cc b) {
    LD d = (a.c - b.c).len();
    if (a.c == b.c || sgn(d - a.r - b.r) > 0 || sgn(d - fabs(a.r - b.r)) < 0) return vp();
    P r = (b.c - a.c).unit();
    LD x = (d * d + a.r * a.r - b.r * b.r) / (d * 2);
    LD h = sqrtl(a.r * a.r - x * x);
    if (sgn(h) == 0) return vp({a.c + r * x});
    return vp({a.c + r * x + r.rot90() * h, a.c + r * x - r.rot90() * h});
}

vp tangent(cp a, cc b) { return cc_intersection(b, C(a, b.c)); } // 点到圆的切点

vector<L> tangent(cc a, cc b, int f) // f = 1 extangent;f = -1 intangent
{
    D d = (b.c - a.c).len();
    int sg = sgn(fabs((b.r - f * a.r) / d) - 1);
    if (sg == 1)
        return {};
    else if (sg == 0) {
        P p = a.c - sgn(b.r - f * a.r) * f * a.r * (b.c - a.c).unit();
        return {{p, p + (b.c - a.c).rot90()}};
    } // 内切/外切
    D theta = asin(min((D)1, max((D)-1, f * (b.r - f * a.r) / d)));
    P du = (b.c - a.c).unit(), du1 = du.rot(theta + pi / 2), du2 = du.rot(-theta - pi / 2);
    return {{a.c + a.r * du1, b.c + f * b.r * du1}, {a.c + a.r * du2, b.c + f * b.r * du2}};
}