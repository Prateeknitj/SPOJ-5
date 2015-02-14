/**
Data Structure: Segment Tree

ref = http://blog.csdn.net/u012965890/article/details/39756503


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
const int MAX = 100000;
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
	LL sumsq;
	LL sum;
	bool lazy;
	LL lazyval;

	void assignleaf()
	{

	}
	
	void combine(data &l, data &r)
	{
		sumsq = l.sumsq + r.sumsq;
		sum = l.sum + r.sum;		
	}



};

data tree[4*MAX+5];

void refresh1(int node,int a,int b)
{



}

void refresh0(int node,int a,int b)
{



}


void build_tree(int node,int s,int e)
{
	if(s>e) return;

	if(s==e)
	{
		tree[node].sumsq = (LL)arr[e]*arr[e];
		tree[node].sum = arr[s];
		tree[node].lazy=false;
		tree[node].lazyval=0;
		return;
	}

	int mid=(s+e)/2;

	build_tree(2*node,s,mid);
	build_tree(2*node+1,mid+1,e);

	tree[node].combine(tree[2*node],tree[2*node+1]);


}

LL query(int node,int segs,int sege,int qs,int qe)
{
	if(segs>sege||segs>qe||sege<qs) 
		return 0;

	if(segs>=qs && sege<=qe)
	{
		return tree[node].sumsq;		
	}


	int mid = segs+sege; mid/=2;

	if(qe<=mid)
		return query(2*node,segs,mid,qs,qe);
	else if(qs>mid)
		return query(2*node+1,mid+1,sege,qs,qe);
	
	else return query(2*node,segs,mid,qs,qe) + query(2*node+1,mid+1,sege,qs,qe);

		
}

void update0(int node,int segs,int sege,int qs,int qe,int val)
{
	if(segs>sege||segs>qe||sege<qs)
	{
	 	return;
	}
	
	if(segs>=qs && sege<=qe)
	{
		
	}
	

	int mid = segs+sege; mid/=2;

	update0(2*node,segs,mid,qs,qe,val);
	update0(2*node+1,mid+1,sege,qs,qe,val);

	tree[node].combine(tree[2*node],tree[2*node+1]);	

}

void update1(int node,int segs,int sege,int qs,int qe,int val)
{
	if(segs>sege||segs>qe||sege<qs)
	{
	 	return;
	}

	if(segs>=qs && sege<=qe)
	{
		
	}

	

	int mid = segs+sege; mid/=2;

	update1(2*node,segs,mid,qs,qe,val);
	update1(2*node+1,mid+1,sege,qs,qe,val);

	tree[node].combine(tree[2*node],tree[2*node+1]);	

}


int main()
{

int test; INT(test);

FOR(tt,1,test+1)
{
	int n,q;
	INT(n); INT(q);

	FOR(i,0,n)
		INT(arr[i]);

	build_tree(1,0,n-1);

	printf("Case %d:\n",tt);

	while(q--)
	{
		int com; 
		int l,r,x;
		INT(com); INT(l); INT(r);
		if(com==2)
		{
			PLLD(query(1,0,n-1,l-1,r-1));			 
		}
		else if(com==1)
		{
			INT(x); //add

			update1(1,0,n-1,l-1,r-1,x,1);

		}
		else if(com==0)
		{
			INT(x); //set
			update0(1,0,n-1,l-1,r-1,x,0);
		}


	}



}

return 0;
}
