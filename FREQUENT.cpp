/**
Data Structure: Segment Tree
ref - http://discuss.codechef.com/questions/38944/frequent-values-spoj

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
	int lfreq,rfreq,mfreq;  //max freq in left and right tree. 
	// mfreq = max freq in the current interval
	
	void assignleaf()
	{
		lfreq=rfreq=mfreq=1;
	}
	void assignleaf(int idx ,int val)
	{
		
	}

	void combine(data &l, data &r,int s,int e,int mid)
	{
		if(arr[mid]==arr[mid+1]) /// if array element is same where the interval divides
		{
			lfreq = l.lfreq + r.lfreq*(arr[s]==arr[mid]);
			rfreq = r.rfreq + l.rfreq*(arr[e]==arr[mid]); 
			mfreq = max(max(l.mfreq,r.mfreq),l.rfreq+r.lfreq);
		}
		else
		{
			lfreq = l.lfreq;
			rfreq = r.rfreq;
			mfreq = max(l.mfreq,r.mfreq);	

		}
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

	tree[node].combine(tree[2*node],tree[2*node+1],s,e,mid);


}

int query(int node,int segs,int sege,int qs,int qe)
{

	if(segs>=qs && sege<=qe)
		return tree[node].mfreq;
		

	int mid= segs+sege; mid /= 2;
	
	if(qe<=mid)
		return query(2*node,segs,mid,qs,qe);
	
	 if(qs>mid)
		return query(2*node+1,mid+1,sege,qs,qe);

	
	int leftf = query(2*node,segs,mid,qs,qe);
	int rightf= query(2*node+1,mid+1,sege,qs,qe);

	if(arr[mid]==arr[mid+1])  /// if array element is same where the interval divides
	{
		int temp = min(tree[2*node].rfreq,mid-qs+1) + min(tree[2*node+1].lfreq,qe-mid);

		return max(temp,max(leftf,rightf));
	}
	else 
		return max(leftf,rightf);

}


int main()
{

int n,q;

while(scanf("%d%d",&n,&q)==2)
{
	FOR(i,0,n)
		INT(arr[i]);

	build_tree(1,0,n-1);


	while(q--)
	{
		int a,b;
		INT(a); INT(b);
		--a; --b;
		PINT(query(1,0,n-1,a,b));	
	}

}

return 0;
}
