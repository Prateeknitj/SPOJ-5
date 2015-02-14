/**
Segment Tree with lazy propagation
**/
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <set>
#include <assert.h>
#include <cstring>
#include <string>
#include <string.h>
#include <queue>
#include <stack>
#include <vector>
#include <map>
#include <time.h>
#include <climits>

using namespace std;

#define FOR(i,a,b) for(int i=a;i<b;++i)
#define FORR(i,a,b) for(int i=a;i>=b;--i)
#define FORC(it,container) for(typeof(container.begin()) it=container.begin();it!=container.end();++it)
#define INT(x) scanf("%d",&x)
#define LLD(x) scanf("%lld",&x)
#define STR(x) scanf("%s",x)
#define CHAR(x) scanf("%c",&x)
#define PINT(x) printf("%d\n",x)
#define PLLD(x) printf("%lld\n",x)
#define CLR(x) memset(x,0,sizeof(x));
#define F first
#define S second
#define PB push_back

const int INF = INT_MAX;
const int MAX = 100001;
const int MOD = 1e9 + 7;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;
typedef map<int,int> MII;
typedef vector<pair<int,int> > VPII;
typedef vector<int> VI;
typedef vector<char> VC;
typedef vector<LL> VLL;
typedef vector<VI> VVI;
typedef vector<VLL> VVL;
typedef set<int> SI;
typedef set<char> SC;

int arr[MAX+5];
struct data
{
	int countoff,counton,lazy;
	
	void assignleaf()
	{
		countoff=1;
		counton=0;
		lazy=0;
	}
	
	void combine(data &l, data &r)
	{
		countoff  = l.countoff + r.countoff;
		counton = l.counton + r.counton;		
	}



};

data tree[4*MAX+5];


void refresh(int node,int a,int b)
{

	    if(tree[node].lazy)
		{	
			swap(tree[node].countoff,tree[node].counton);
		
			tree[2*node].lazy = 1 - tree[2*node].lazy ;
			tree[2*node+1].lazy = 1 - tree[2*node+1].lazy;
			
			tree[node].lazy = 0;
		}

}




void build_tree(int node,int s,int e)
{
	if(s>e) return;

	if(s==e)
	{
		tree[node].assignleaf();
		return;
	}

	int mid=(s+e)/2;

	build_tree(2*node,s,mid);
	build_tree(2*node+1,mid+1,e);

	tree[node].combine(tree[2*node],tree[2*node+1]);


}

int query(int node,int segs,int sege,int qs,int qe)
{

	//cout<<" q = node = " <<node<< " segs = "<<segs<< " sege = "<<sege<< " qs = "<<qs<<" qe = "<<qe<<endl;

		if(segs>sege||segs>qe||sege<qs) return 0;

		refresh(node,segs,sege);

		if(segs>=qs && sege<= qe)
		{
			return tree[node].counton;
		}
		
		int mid = segs+sege;  mid /= 2;
		
		return query(2*node,segs,mid,qs,qe) + query(2*node+1,mid+1,sege,qs,qe);

}

void update(int node,int segs,int sege,int qs,int qe)
{
	//cout<<" update -  node = " <<node<< " segs = "<<segs<< " sege = "<<sege<< " qs = "<<qs<<" qe = "<<qe<<endl;


	if(segs>sege||segs>qe||sege<qs)
	{	
		refresh(node,segs,sege);
		return;
	}
	if(segs>=qs && sege<= qe)		
	{
		tree[node].lazy = 1 - tree[node].lazy;
		refresh(node,segs,sege);
		return;
	}
	
	
	refresh(node,segs,sege);

	int mid = segs+sege;  mid /= 2;
	
	update(2*node,segs,mid,qs,qe);
	update(2*node+1,mid+1,sege,qs,qe);
	
	tree[node].combine(tree[2*node],tree[2*node+1]);
		

}



int main()
{

int n,m; 

INT(n); INT(m);

build_tree(1,0,n-1);



while(m--)
{

	int op,L,R;
	INT(op); INT(L); INT(R);

	if(op)
	{		
		PINT(query(1,0,n-1,L-1,R-1));
	}
	else 
	{
		update(1,0,n-1,L-1,R-1);
	}

}


return 0;
}

