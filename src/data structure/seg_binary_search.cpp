// 找到从 ql 开始，第一个区间 [ql, x] 满足条件的 x
// cur 是累计的信息
int findr(int o,int l,int r,int ql,S& cur){
    if(r<ql)return -1;
    if(l>=ql){
        if(/*合并(cur, t[o])仍然不满足条件*/){
            /* cur = 合并(cur, t[o])*/
            return -1;
        }
        if(l==r){
            return l;
        }
    }   
    int lch=o<<1,rch=o<<1|1;
    int mid = (l+r)>>1;
    int ans = findr(lch,l,mid,ql,cur);
    if(ans != -1)return ans;
    return findr(rch, mid+1, r, ql, cur);
}