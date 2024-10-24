struct Dinic_cost {
#define Maxn ?
#define Maxm ?
    int tot = 1;
    int tmphea[Maxn], hea[Maxn], nex[Maxm << 1], ver[Maxm << 1];
    ll sumflow, sumcost, edg[Maxm << 1], Cost[Maxm << 1];
    bool inq[Maxn];
    ll dis[Maxn];
    inline void init() { tot = 1, memset(hea, 0, sizeof(hea)); }
    inline void add_edge(int x, int y, ll d, ll c) {
        ver[++tot] = y, nex[tot] = hea[x], hea[x] = tot, edg[tot] = d, Cost[tot] = c;
        ver[++tot] = x, nex[tot] = hea[y], hea[y] = tot, edg[tot] = 0, Cost[tot] = -c;
    }
    inline bool spfa(int s, int t) {
        memset(dis, 0x3f, sizeof(dis)), dis[s] = 0;
        memcpy(tmphea, hea, sizeof(hea));
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int cur = q.front();
            q.pop(), inq[cur] = false;
            for (int i = hea[cur]; i; i = nex[i])
                if (edg[i] && dis[ver[i]] > dis[cur] + Cost[i]) {
                    dis[ver[i]] = dis[cur] + Cost[i];
                    if (!inq[ver[i]])
                        q.push(ver[i]), inq[ver[i]] = true;
                }
        }
        return dis[t] != infll;
    }
    ll dfs(int x, ll flow, int t) {
        if (x == t || !flow) return flow;
        ll rest = flow, tmp;
        inq[x] = true;
        for (int i = tmphea[x]; i && rest; i = nex[i]) {
            tmphea[x] = i;
            if (!inq[ver[i]] && edg[i] && dis[ver[i]] == dis[x] + Cost[i]) {
                if (!(tmp = dfs(ver[i], min(edg[i], rest), t))) dis[ver[i]] = infll;
                sumcost += Cost[i] * tmp, edg[i] -= tmp, edg[i ^ 1] += tmp, rest -= tmp;
            }
        }
        inq[x] = false;
        return flow - rest;
    }
    inline pll solve(int s, int t) {
        sumflow = sumcost = 0;
        while (spfa(s, t))
            sumflow += dfs(s, infll, t);
        return pll(sumflow, sumcost);
    }
#undef Maxn
#undef Maxm
} G;