struct FHQ_number
{
	#define Maxn 点数
	#define ls tree[p].pl
	#define rs tree[p].pr
	private:
		int All=0,root=0;
		struct NODE { int pl,pr,siz,cnt,rnd; ll val; };
		NODE tree[Maxn];
		inline int Dot() { return ++All; }
		inline int New(ll Val)
		{
			int p=Dot();
			tree[p].rnd=rand(),tree[p].val=Val;
			tree[p].siz=tree[p].cnt=1;
			tree[p].pl=tree[p].pr=0;
			return p;
		}
		inline void pushdown(int p) { p--; }
		inline void pushup(int p)
			{ tree[p].siz=tree[ls].siz+tree[rs].siz+tree[p].cnt; }
		void split(int p,int k,int &x,int &y)
		{
			if(!p) { x=y=0; return; }
			pushdown(p);
			if(tree[p].val<=k) x=p,split(rs,k,rs,y);
			else y=p,split(ls,k,x,ls);
			pushup(p);
		}
		int merge(int x,int y)
		{
			if(!x || !y) return x+y;
			if(tree[x].rnd<tree[y].rnd)
			{
				pushdown(x),tree[x].pr=merge(tree[x].pr,y),pushup(x);
				return x;
			}
			else
			{
				pushdown(y),tree[y].pl=merge(x,tree[y].pl),pushup(y);
				return y;
			}
		}
		inline int kth(int p,int Rank)
		{
			while(p)
			{
				if(tree[ls].siz>=Rank) p=ls;
				else if(tree[ls].siz+tree[p].cnt>=Rank) return p;
				else Rank-=tree[ls].siz+tree[p].cnt,p=rs;
			}
			return p;
		}
		int x,y,z;
	public:
		inline void Insert(ll Val)
			{ split(root,Val,x,y),root=merge(merge(x,New(Val)),y); }
		inline void Delete_one(int Val)
		{
			split(root,Val,x,z),split(x,Val-1,x,y);
			y=merge(tree[y].pl,tree[y].pr);
			root=merge(merge(x,y),z);
		}
		inline ll Rank_to_Value(int Rank)
			{ return tree[kth(root,Rank)].val; }
		inline int Value_to_Rank(ll Value)
		{
			split(root,Value-1,x,y);
			int ret=tree[x].siz+1;
			root=merge(x,y);
			return ret;
		}
		inline ll Findpre(ll Value)
		{
			split(root,Value-1,x,y);
			ll ret=tree[kth(x,tree[x].siz)].val;
			root=merge(x,y);
			return ret;
		}
		inline ll Findnex(ll Value)
		{
			split(root,Value,x,y);
			ll ret=tree[kth(y,1)].val;
			root=merge(x,y);
			return ret;
		}
}T;
struct FHQ_sequence
{
	#define Maxn 点数
	#define ls tree[p].pl
	#define rs tree[p].pr
	int All=0,root=0;
	struct NODE { int pl,pr,siz,cnt,rnd,val; bool tag; };
	NODE tree[Maxn];
	inline int Dot() { return ++All; }
	inline int New(int Val)
	{
		int p=Dot();
		tree[p].rnd=rand(),tree[p].val=Val;
		tree[p].cnt=tree[p].siz=1;
		tree[p].pl=tree[p].pr=0;
		return p;
	}
	inline void pushdown(int p)
	{
		if(!tree[p].tag) return;
		swap(tree[ls].pl,tree[ls].pr);
		swap(tree[rs].pl,tree[rs].pr);
		tree[ls].tag^=1,tree[rs].tag^=1;
		tree[p].tag=false;
	}
	inline void pushup(int p)
		{ tree[p].siz=tree[ls].siz+tree[p].cnt+tree[rs].siz; }
	void split(int p,int k,int &x,int &y)
	{
		if(!p) { x=y=0; return; }
		pushdown(p);
		if(tree[ls].siz<k) x=p,split(rs,k-tree[ls].siz-1,rs,y);
		else y=p,split(ls,k,x,ls);
		pushup(p);
	}
	int merge(int x,int y)
	{
		if(!x || !y) return x+y;
		if(tree[x].rnd<tree[y].rnd)
		{
			pushdown(x),tree[x].pr=merge(tree[x].pr,y),pushup(x);
			return x;
		}
		else
		{
			pushdown(y),tree[y].pl=merge(x,tree[y].pl),pushup(y);
			return y;
		}
	}
	int kth(int p,int Rank)
	{
		while(p)
		{
			if(tree[ls].siz>=Rank) p=ls;
			else if(tree[ls].siz+tree[p].cnt>=Rank) return p;
			else Rank-=tree[ls].siz+tree[p].cnt,p=ls;
		}
		return p;
	}
	void Insert(int Val) // 插到末尾 
		{ root=merge(root,New(Val)); }
	int x,y,z;
	inline void Reverse(int l,int r)
	{
		split(root,r,x,z),split(x,l-1,x,y);
		swap(tree[y].pl,tree[y].pr),tree[y].tag^=1;
		root=merge(merge(x,y),z);
	}
	void print(int p)
	{
		pushdown(p);
		if(ls) print(ls);
		printf("%d ",tree[p].val);
		if(rs) print(rs);
	}
}T;