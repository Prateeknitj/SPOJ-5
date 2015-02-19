/**

Data Structure: Segment tree
Author: Shivam Mishra
handle: shivam217

There will be T (T <= 25) test cases in the input file. 
 First line of the input contains two positive integers, N (N <= 100,000) and Q (Q <= 100,000). 
 The next line contains N integers, each at most 1000.  Each of the next Q lines starts with a number, which indicates the type of operation:

2 st nd  -- return the sum of the squares of the numbers with indices in [st, nd] {i.e., from st to nd inclusive} (1 <= st <= nd <= N).

1 st nd x -- add "x" to all numbers with indices in [st, nd] (1 <= st <= nd <= N, and -1,000 <= x <= 1,000).

0 st nd x -- set all numbers with indices in [st, nd] to "x" (1 <= st <= nd <= N, and -1,000 <= x <= 1,000).


For each test case output the “Case <caseno>:” in the first line and from the second line output the sum of squares 
for each operation of type 2.  Intermediate overflow will not occur with proper use of 64-bit signed integer. 

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
	int lazyset;
	int setval;
	int addval;
	
	void assignleaf()
	{
		
	}
	void assignleaf(int idx ,int val)
	{
		
	}

	void combine(data &l, data &r)
	{
		sumsq = l.sumsq + r.sumsq;
		sum = l.sum + r.sum;
	}
};

data tree[4*MAX+5];

void pushdown(int node,int segs,int sege)
{
	int mid = segs+sege; mid /= 2;
	
	if(tree[node].lazyset==1)
	{
		       tree[node].lazyset=0;
	
			tree[2*node].lazyset=1;
			tree[2*node+1].lazyset=1;
		
			tree[2*node].setval = tree[node].setval; 
			tree[2*node+1].setval = tree[node].setval;
				
			tree[2*node].sum = (mid-segs+1)*tree[node].setval;
			tree[2*node+1].sum = (sege-mid)*tree[node].setval;
		
			tree[2*node].addval=0;
			tree[2*node+1].addval=0;
		
			tree[2*node].sumsq = (mid-segs+1)*tree[node].setval*tree[node].setval;
			tree[2*node+1].sumsq =(sege-mid)*tree[node].setval*tree[node].setval;;
		
			
	}
	
	
	if(tree[node].addval)
	{

			tree[2*node].addval += tree[node].addval;
			tree[2*node+1].addval += tree[node].addval; 
		
			tree[2*node].sumsq += (mid-segs+1)*tree[node].addval*tree[node].addval + 2*tree[node].addval*tree[2*node].sum;
			tree[2*node+1].sumsq += (sege-mid)*tree[node].addval*tree[node].addval + 2*tree[node].addval*tree[2*node+1].sum;
		
			tree[2*node].sum += (mid-segs+1)*tree[node].addval;
			tree[2*node+1].sum += (sege-mid)*tree[node].addval;

			tree[node].addval = 0;
		
	}	
		

}

void build_tree(int node,int s,int e)
{
	tree[node].addval=0;
	tree[node].lazyset=0;
	
	if(s>e) return;

	if(s==e)
	{
		tree[node].sum = arr[s];
		tree[node].sumsq = arr[s]*arr[s];
		return;
	}

	int mid=(s+e)/2;

	build_tree(2*node,s,mid);
	build_tree(2*node+1,mid+1,e);

	tree[node].combine(tree[2*node],tree[2*node+1]);

}

LL query(int node,int segs,int sege,int qs,int qe)
{

//cout<<" q -- node = "<<node<<" segs = "<<segs<<" sege = "<<sege<<" qs = "<<qs<<" qe =  "<<qe<<endl;
	

	if(segs>sege || segs>qe || sege < qs) 
	{
		if(tree[node].lazyset||tree[node].addval)
		     pushdown(node,segs,sege);

		return 0;

	}

	if(tree[node].lazyset || tree[node].addval)
		pushdown(node,segs,sege);

	if(segs>=qs && sege<=qe)
	{

	//cout<<"q1 node = "<<node<<" segs = "<<segs<<" sege = "<<sege<<" sumsq  = "<<tree[node].sumsq<<endl;
		return tree[node].sumsq;

	}

	int mid= segs+sege; mid /= 2;
			

	return query(2*node,segs,mid,qs,qe) + query(2*node+1,mid+1,sege,qs,qe);

}

//comm=1
void update_add(int node,int segs,int sege,int qs,int qe,int x)
{

//cout<<" ua -  node = "<<node<<" segs = "<<segs<<" sege = "<<sege<<" qs = "<<qs<<" qe =  "<<qe<<" x = "<<x<<endl;
	
	
	if(segs>sege||segs>qe||sege<qs)	return;
	
	if(segs>=qs && sege<=qe)
	{
		tree[node].addval += x;
		tree[node].sumsq += (LL)(sege-segs+1)*x*x +  (LL)2*x*(tree[node].sum); 	
		tree[node].sum   += (LL)(sege-segs+1)*x;
		return;
	}

	int mid= segs+sege; mid /= 2;
	
	if(tree[node].lazyset || tree[node].addval)
		pushdown(node,segs,sege);

	update_add(2*node,segs,mid,qs,qe,x);
        update_add(2*node+1,mid+1,sege,qs,qe,x);
			
	tree[node].combine(tree[2*node],tree[2*node+1]); 

	
}

//comm=0
void update_set(int node,int segs,int sege,int qs,int qe,int x)
{

	//cout<<" node = "<<node<<" segs = "<<segs<<" sege = "<<sege<<" qs = "<<qs<<" qe =  "<<qe<<" x = "<<x<<endl;
	
	if(segs>sege||segs>qe||sege<qs)
		return;
	

	if(segs>=qs && sege<=qe)
	{
		tree[node].lazyset= 1;
		tree[node].setval=x;
		tree[node].sumsq = (LL)(sege-segs+1)*x*x;	
		tree[node].sum   = (LL)(sege-segs+1)*x;
		tree[node].addval = 0;
		return;
	}

	if(tree[node].lazyset || tree[node].addval)
		pushdown(node,segs,sege);

  
	  int mid= segs+sege; 
	  mid /= 2;
	  
	
	 update_set(2*node,segs,mid,qs,qe,x);
   	 update_set(2*node+1,mid+1,sege,qs,qe,x);
			
	tree[node].combine(tree[2*node],tree[2*node+1]);
	
	
}





int main()
{

	int test; INT(test);
	
	FOR(tt,1,test+1)
	{
		int n,q; INT(n); INT(q);
		
		
		CLR(arr);
		CLR(tree);
		
		FOR(i,0,n)
			INT(arr[i]);
			
		build_tree(1,0,n-1);
		
		
		
			
		printf("Case %d:\n",tt);
		while(q--)
		{

	//FOR(i,1,16)
	//cout<<" node = "<<i<<" sumsq = "<<tree[i].sumsq<<" sum = "<<tree[i].sum<<" lazyset = "<<tree[i].lazyset<<" addval = "<<tree[i].addval<<" setval = "<<tree[i].setval<<endl;
			

			int comm; int l,r; 
			
			INT(comm); INT(l); INT(r);
		
			
			if(comm==0)
			{
				//set x	
				int x; INT(x);		
				update_set(1,0,n-1,l-1,r-1,x);		
			
			}
			else if(comm==1)
			{
				//add x
				int x; INT(x);				
				update_add(1,0,n-1,l-1,r-1,x);
					
			}
			else if(comm==2)
			{
				LL ans = query(1,0,n-1,l-1,r-1);
			
				PLLD(ans);
						
			}
		
		}

	}

return 0;
}
