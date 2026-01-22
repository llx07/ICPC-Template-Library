// 0-下标，h[i]表示后缀sa[i]和sa[i+1]的LCP长度
struct SuffixArray {
    int n;
    vector<int> sa, rk, h;
    SuffixArray(const string &s) {
        n = s.length();
        sa.resize(n);
        h.resize(n - 1);
        rk.resize(n);
        iota(sa.begin(), sa.end(), 0);
        sort(sa.begin(), sa.end(), [&](int a, int b) {return s[a] < s[b];});
        rk[sa[0]] = 0;
        for (int i=1;i<n;++i) rk[sa[i]]=rk[sa[i-1]]+(s[sa[i]]!=s[sa[i-1]]);
        int k = 1;
        vector<int> tmp, cnt(n);
        tmp.reserve(n);
        while (rk[sa[n - 1]] < n - 1) {
            tmp.clear();
            for (int i=0;i<k;i++) tmp.push_back(n-k+i);
            for (auto i:sa)if(i>=k) tmp.push_back(i-k);
            fill(cnt.begin(), cnt.end(), 0);
            for (int i=0;i<n;i++) cnt[rk[i]]++;
            for (int i=1;i<n;i++) cnt[i]+=cnt[i-1];
            for (int i=n-1;i>=0;i--) sa[--cnt[rk[tmp[i]]]]=tmp[i];
            swap(rk, tmp);
            rk[sa[0]] = 0;
            for (int i=1;i<n;i++){
                rk[sa[i]]=rk[sa[i-1]];
                if(tmp[sa[i-1]]<tmp[sa[i]] || sa[i-1]+k==n || tmp[sa[i-1]+k]<tmp[sa[i]+k]) rk[sa[i]]++;
            }
            k *= 2;
        }
        for(int i=0,j=0;i<n;i++){
            if(rk[i]==0) j=0;
            else{
                if(j) j--;
                while(i+j<n && sa[rk[i]-1]+j<n && s[i+j]==s[sa[rk[i]-1]+j])++j;
                h[rk[i]-1] = j;
            }
        }
    }
};

// 用 ST 表 O(1) 求 LCP
vector<vector<int>> st(n-1, vector<int>(20));
for(int i=0;i<n-1;i++)st[i][0]=t.h[i];
for(int j=1;j<20;j++){
    for(int i=0;i+(1<<(j))-1<n-1;i++){
        st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
    }
}
auto query = [&](int l,int r){
    if(l==r)return n-r+1;
    if(l>r)swap(l,r);
    --r;
    int o = __lg(r-l+1);
    return min(st[l][o], st[r-(1<<o)+1][o]);
};
auto lcp = [&](int l1,int r1,int l2,int r2)->int {
    int x = query(t.rk[l1], t.rk[l2]);
    return min(x, min(r1-l1+1, r2-l2+1));
};