#include <bits/stdc++.h>

using namespace std;


int rows,col;
char M[205][205];
bool vis[205][205][2];
int memo[205][205][2];

bool inrange(int x,int y)
{
    return (x>=0 && x<rows && y>=0 && y<col);
}



int dfs(int i,int j,int face)
{

if(i==rows-1 && j==col-1 && face==0)
    return (M[i][j]=='T')?1:0;

if(i==rows-1 && j==0 && face==1)
    return (M[i][j]=='T')?1:0;

    if(vis[i][j][face])
        return memo[i][j][face];

    vis[i][j][face] = true;

    int ans = 0;

     if(M[i][j]=='T')
     {
         ans = 1;
     }
     else if(M[i][j]=='#')
     {
         ans=0;
         return 0;
     }


    if(face==0)
    {
        ans += max((M[i][j+1]!='#' && inrange(i,j+1))?dfs(i,j+1,face):0 , (M[i+1][j]!='#' && inrange(i+1,j))?dfs(i+1,j,1):0 );

       memo[i][j][face] = ans;

    }

     else if(face==1)
    {
        ans += max((M[i][j-1]!='#' && inrange(i,j-1))?dfs(i,j-1,face):0 , (M[i+1][j]!='#' && inrange(i+1,j))?dfs(i+1,j,0):0 );

       memo[i][j][face] = ans;

    }

     return ans;

}

int main()
{
  ///freopen("C:\\in.txt", "r", stdin);

    int test;
    cin>>test;
    while(test>0)
    {
        --test;
        cin>>rows>>col;

        memset(M,0,sizeof(M));

        for(int i=0;i<rows;++i)
        {
            scanf("%s",&M[i]);
        }

        memset(memo,0,sizeof(memo));
        memset(vis,false,sizeof(vis));

       cout<<dfs(0,0,0)<<endl;

    }

 return 0;
}

