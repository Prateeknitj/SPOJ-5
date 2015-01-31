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

//Add(x) :- Add x to the dynamic list
//Delete(x) :- Delete one occurence of x from the dynamic list
//ReportKth(k) :- Print the 1-based Kth smallest element in the list
//ReportRank(x):- Report the 1-based rank of x (1 + No. of elements less than x)

//ins = 1 for insert , 0 for delete 

int arr[MAX+5];

struct data
{
	int sum;  //no of elements in the interval
	int uniq; // no of unique elements in the interval
	bool used; //used or not
	
	void assignleaf()
	{	
		used=false;
		sum=0;
		uniq=0;
	}

	void assignleaf(int idx ,int ins)
	{
		if(ins==1)
		{
			if(arr[idx]==0)
			{
				arr[idx] = 1 ;
				sum = 1;
				uniq = 1;	
				used = true;
						
			}
			else if(arr[idx]>0)
			{
				arr[idx] = 1 ;
				sum += 1;
				uniq = 1;	
				used = true;			
			}
		}
		else if(ins==0)
		{
			arr[idx] -= 1;  
			
			if(arr[idx]==0)
				uniq=0 , sum=0 , used=false;

		}
	}

	void combine(data &l, data &r)
	{
		sum = r.sum + l.sum ;
		uniq = l.uniq + r.uniq;
		used = l.used || r.used;

		
	}



};
		

data tree[4*MAX+5];

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

void point_update(int node,int segs,int sege,int index,int ins)
{
	if(segs==sege && segs==index)
	{
		tree[node].assignleaf(index,ins);
		 return;
	}

	int mid = (segs+sege)/2;

	if(index<=mid)
		point_update(2*node,segs,mid,index,ins);
	else 
		point_update(2*node+1,mid+1,sege,index,ins);


	tree[node].combine(tree[2*node],tree[2*node+1]);

}

int Xth_smallest(int node,int segs,int sege,int x)
{

	if(segs==sege && arr[segs]>0)
		return segs;		

	int mid = (segs+sege)/2;
	
	
	if(tree[2*node].sum<x)
	{
		x = x -  tree[2*node].sum;
		return Xth_smallest(2*node+1,mid+1,sege,x);
	}
	else
	{
		return Xth_smallest(2*node,segs,mid,x);
	}
	

}


int ReportRank(int node,int segs,int sege,int qs,int qe)
{

	if(segs>=qs && sege<=qe)
		return tree[node].sum;

	int mid= segs+sege; mid /= 2;

	int ans1 = 0;
	int ans2 = 0;

	ans1 = ReportRank(2*node,segs,mid,qs,qe);

	if(qe>mid)
		ans2 = ReportRank(2*node+1,mid+1,sege,qs,qe);

	
	return ans1+ans2;

}

int main()
{
	
	int test; INT(test);

	while(test>0)
	{
		--test;
		
		CLR(arr);

		int q; INT(q);
			
		while(q>0)
		{
			--q;
			int k,x;
			INT(k); INT(x);

			if(k==1)
			{
				point_update(1,0,MAX,x,1);
			}
			else if(k==2)
			{
				point_update(1,0,MAX,x,0);		
			}
			else if(k==3)
			{	
				int a = Xth_smallest(1,0,MAX,x);
				PINT(a);			
			}
			else if(k==4)
			{
				int a = 1 + ReportRank(1,0,MAX,0,x-1);
				PINT(a);
			}

		}

	}

return 0;
}
