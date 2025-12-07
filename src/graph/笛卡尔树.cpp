for(int i=1;i<=n;i++){
    int k = tp;
    // 大根堆
    while(k && a[stk[k]]<a[i])ls[i]=stk[k],--k;
    if(k)rs[stk[k]]=i;
    stk[++k]=i;
    tp=k;
}