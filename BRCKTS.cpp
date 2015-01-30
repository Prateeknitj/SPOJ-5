/**
Problem  - BRCKTS from SPOJ
Data structure - Segment tree
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
const int MAX = 30000;
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

/// cp - no of unmatched closed paranthesis
/// op - no of unmatched open paranthesis


struct data 
{ 
	int cp, op;  
	
	void assignleaf(char c)
	{
		if(c=='(')
			cp=0,op=1;
		else cp=1,op=0;
	}

	
	void combine(data &l, data &r)
	{
		int newmatches = min(l.op,r.cp);
		op = l.op + r.op - newmatches;
		cp = l.cp + r.cp - newmatches;
	}


};

char arr[MAX+5];
data tree[4*MAX+5];

void build_tree(int node,int s,int e)
{
	if(s>e) return;

	if(s==e) 
	{	tree[node].assignleaf(arr[s]);
		 return;
	}
	int mid=(s+e)/2;
	build_tree(2*node,s,mid);
	build_tree(2*node+1,mid+1,e);
	tree[node].combine(tree[2*node],tree[2*node+1]);	

}

void update(int node,int segs,int sege,int index)
{
	if(segs==sege && segs==index)
	{	
		arr[index] = ((arr[index]=='(')?')':'(');
		tree[node].assignleaf(arr[index]);
		return;
	}

	int mid = (segs+sege)/2;

	if(index>=segs && index<=mid) 
		update(2*node,segs,mid,index);
	else 
		update(2*node+1,mid+1,sege,index);
	tree[node].combine(tree[2*node],tree[2*node+1]);
}



int main()	
{
int test = 10 ; //INT(test);
FOR(testcase,1,test+1)
{
	CLR(arr);
	CLR(tree);

	int n; INT(n);

	STR(arr);
	build_tree(1,0,n-1);

	int m; INT(m);
	
	bool f=true;

	FOR(i,0,m)
	{
		int k; INT(k);

		if(k)
		{
			update(1,0,n-1,k-1);
		}
		else if(k==0)
		{
			int ans;
		
			if(tree[1].cp==0 && tree[1].op==0)
				ans=0;
			else ans=1;	
	
			if(f)
				f=false, printf("Test %d:\n",testcase);

			if(ans==0)
				printf("YES\n");
			else printf("NO\n");
		}
	}

}

return 0;
}
