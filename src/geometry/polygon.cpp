vp Poly_cut(vp p, cl l) // 直线切多边形，返回一侧的图形端点，O(n)
{
    if (p.empty()) return vp();
    vp ret;
    int n = p.size();
    p = push_back(p[0]);
    for (int i = 0; i < n; ++i) {
        if (((p[i] - l.s) ^ (l.t - l.s)) <= 0)
            ret.push_back(p[i]);
        if (two_size(p[i], p[i + 1], l))
            ret.push_back(ll_intersection(l, L(p[i], p[i + 1])));
    } // p.pop_back();
    return ret;
}

LD Poly_area(vp p) {
    LD ar = 0;
    int n = p.size();
    for (int i = 0, j = n - 1; i < n; j = i++)
        ar += p[i] ^ p[j];
    return fabs(ar) / 2;
}

// Below is from Nemesis

// 多边形与圆交
LD angle(cp u, cp v) {
    return 2 * asin(dis(u.unit(), v.unit()) / 2);
}
LD area(cp s, cp t, LD r) { // 2 * area
    LD theta = angle(s, t);
    LD dis = p2s({0, 0}, {s, t});
    if (sgn(dis - r) >= 0) return theta * r * r;
    auto [u, v] = line_circle_inter({s, t}, {{0, 0}, r});
    point lo = sgn(det(s, u)) >= 0 ? u : s;
    point hi = sgn(det(v, t)) >= 0 ? v : t;
    return det(lo, hi) + (theta - angle(lo, hi)) * r * r;
}
LD solve(vector<point> &p, cc c) {
    LD ret = 0;
    for (int i = 0; i < (int)p.size(); ++i) {
        auto u = p[i] - c.c;
        auto v = p[(i + 1) % p.size()] - c.c;
        int s = sgn(det(u, v));
        if (s > 0)
            ret += area(u, v, c.r);
        else if (s < 0)
            ret -= area(v, u, c.r);
    }
    return abs(ret) / 2;
} // ret在p逆时针时为正