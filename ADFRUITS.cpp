/**
Author - Shivam Mishra
Problem - Advanced Fruits from SPOJ
Algorithm - Find LCS and SCS
**/


#include <bits/stdc++.h>

using namespace std;


vector<char> vc;

void backtrace(int dp[105][105],char s1[105],char s2[105],int i,int j)
{

if(i==-1 || j==-1) return;

else if(s1[i-1]==s2[j-1]) { backtrace(dp,s1,s2,i-1,j-1); vc.push_back(s1[i-1]); }

else
{ 
	if(dp[i][j-1]>dp[i-1][j]) backtrace(dp,s1,s2,i,j-1);				
	  else  backtrace(dp,s1,s2,i-1,j);
}
}


int main()
{

char s1[1005] , s2[1005];

while(scanf("%s%s",s1,s2)==2)
{

	int len1 = strlen(s1);
	int len2 = strlen(s2);

	int dp[105][105];
	memset(dp,0,sizeof(dp));

	for(int i=0;i<=len1;++i) dp[i][0] = 0;
	for(int i=0;i<=len2;++i) dp[0][i] = 0;

// filling up dp[][] table
	for(int i=1;i<=len1;++i)
	{

		for(int j=1;j<=len2;++j)
		{
			if(s1[i-1]==s2[j-1]) dp[i][j] = 1 + dp[i-1][j-1];		
			else dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
		}

	}

	vc.clear();

	 backtrace(dp,s1,s2,len1,len2); //getting LCS by backtracing
		
	int l1=0,l2=0;	
	int j=0;

	while(!isalpha(vc[j]))
		++j;


	for(int i=j;i<vc.size();++i)
	{
	
		while(l1<len1 && s1[l1]!=vc[i])
		{
			cout<<s1[l1];
			++l1;	
		}
		


		while(l2<len2 && s2[l2]!=vc[i])
		{
			cout<<s2[l2];
			++l2;	
		}
		
		cout<<vc[i];	
		++l2;
		++l1;
	}

	while(l1<len1) 
		cout<<s1[l1++];
	while(l2<len2) cout<<s2[l2++];
	cout<<endl;

}


return 0;
}
