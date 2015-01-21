/**
Author - Shivam Mishra
Task - AOCDE from SPOJ
ALGO - Simple DP
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
#define PINT(x) printf("%d\n",x)
#define PLLD(x) printf("%lld\n",x)
#define CLR(x) memset(x,0,sizeof(x));
#define F first
#define S second
#define PB push_back
#define MOD 1000000007
#define MAX 100005


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


int main()
{

while(true)
{
	char s[5005];
	cin>>s;
	
	
	
	int len = strlen(s);
	
	if(len==1 && s[0]=='0')
		break;
		

	ULL dp[5005];
	
	dp[0] = 1;
	dp[1] = 1;
	int num =0;
	FOR(i,2,len+1)
	{
         dp[i] = ((s[i-1]>48)?dp[i-1]:0) + ((s[i-2]>48 && (10*(s[i-2]-48)+s[i-1]-48)<=26)?dp[i-2]:0 );
				
	}
	
		cout<<dp[len]<<endl;

}

return 0;
}

