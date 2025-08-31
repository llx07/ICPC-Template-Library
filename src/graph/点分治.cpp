void Find1(int x,int fa)
{
	 siz[x]=1,subsiz++;
	 for(int i=hea[x];i;i=nex[i]) if(!used[ver[i]] && ver[i]!=fa)
	 	 Find1(ver[i],x),siz[x]+=siz[ver[i]];
}
void Find2(int x,int fa)
{
	 bool isrt=true;
	 for(int i=hea[x];i;i=nex[i]) if(!used[ver[i]] && ver[i]!=fa)
	 {
	 	 Find2(ver[i],x);
	 	 if((siz[ver[i]]<<1)>subsiz) isrt=false;
	 }
	 if(((subsiz-siz[x])<<1)>subsiz) isrt=false;
	 if(isrt) rt=x;
}
void solve(int x)
{
	 subsiz=0,Find1(x,0),Find2(x,0);
	 // 处理和 rt 有关的答案
	 used[rt]=true;
	 for(int i=hea[rt];i;i=nex[i]) if(!used[ver[i]]) solve(ver[i]);
}