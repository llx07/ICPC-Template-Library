int ql,qr;
struct QUE
{
    int num,val;
}que[Maxv];
void many_pack(int c,int w,int m)
{
    if(!c) { add+=m*w; return; }
    m=min(m,V/c);
    for(int pos=0,s;pos<c;pos++)
    {
        ql=1,qr=0,s=(V-pos)/c;
        for(int j=0;j<=s;j++)
        {
            while(ql<=qr && que[qr].val<=(dp[pos+j*c]-j*w)) qr--;
            que[++qr]=(QUE){j,dp[pos+j*c]-j*w};
            while(ql<=qr && (j-que[ql].num)>m) ql++;
            dp[pos+j*c]=max(dp[pos+j*c],que[ql].val+j*w);
        }
    }
}