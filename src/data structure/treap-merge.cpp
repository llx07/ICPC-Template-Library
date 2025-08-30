// ls,rs 为 tree[p].pl 和 tree[p].pr
void mergetree(int p,int &rt) // rt = (rt+p)
{
    if(!p) return;
    mergetree(ls,rt);
    mergetree(rs,rt);
    int x,y;
    split(rt,tree[p].val,x,y);
    ls=rs=0,rt=merge(merge(x,p),y);
}