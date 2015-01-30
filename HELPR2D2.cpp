/**
Problem - HELPR2D2 from SPOJ
Data Structure: Segment tree

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
const int MAX = 1000000;
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

//maxrs = maximum remaining space
//wasted = total wasted space
//noofused = total no of used starships
// used = used or not

int k,n; 

struct data 
{ 
	int maxrs, wasted,noofused;  
	bool used;

	void assignleaf()
	{
		maxrs=k;
		used=false;
		noofused=0;
		wasted=0;
	}

	void assignleaf(int v)
	{
		maxrs  = maxrs - v;
		used = true;
		noofused = 1;
		wasted = maxrs;		
	}

	
	void combine(data &l, data &r)
	{
		maxrs = max(l.maxrs,r.maxrs);
		used  = l.used || r.used;
			
		noofused = ((l.used==true)?l.noofused:0) + ((r.used==true)?r.noofused:0) ;

		wasted = ((l.used==true)?l.wasted:0) + ((r.used==true)?r.wasted:0);		
		
	}


};

data tree[4*MAX+5];

void build_tree(int node,int s,int e)
{
	if(s>e) 
		return;

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

void update(int node,int segs,int sege,int volume)
{

	if(segs==sege && tree[node].maxrs>=volume)
	{	
		tree[node].assignleaf(volume);
		return;
	}

	int mid = (segs+sege)/2;

	if(tree[2*node].maxrs>=volume)
		update(2*node,segs,mid,volume);
	else if(tree[2*node+1].maxrs>=volume)
		update(2*node+1,mid+1,sege,volume);

	tree[node].combine(tree[2*node],tree[2*node+1]);
}



int main()	
{
int test; INT(test);
while(test>0)
{
	--test;

	INT(k); INT(n);
	
	build_tree(1,0,n-1);
 
	int n1=n;

	FOR(i,0,n1)
	{
		char s[25];

		STR(s);
		int len=strlen(s);
		if(s[0]=='b')
		{
			
			int r,vi;

			INT(r);
			INT(vi);

			FOR(k,0,r)
				update(1,0,n-1,vi);	

			n1  = n1 - r + 1;		

		}
		else
		{
			int vi=0;

			for(int j=0;s[j]!='\0';++j)
				vi = vi*10 + s[j]-'0';

			update(1,0,n-1,vi);
		}		
		
	}

	printf("%d %d\n",tree[1].noofused,tree[1].wasted);


}

return 0;
}
