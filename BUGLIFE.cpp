/**
Author - Shivam Mishra
Task - BUGLIFE from SPOJ
Algorithm - Find bipartite partition of graph using BFS

**/

#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <cstring>
#include <set>
#include <math.h>
#include <queue>
#include <stack>

using namespace std;


typedef long long LL;
typedef unsigned long long ULL;
typedef map<int,int> MII;
typedef pair<int,int> PII;
typedef map<PII,int> MPI;

#define MOD 1000000007
#define MAX 100005

vector<int> adj_list[2005];
bool cycle_found= false;
int color[2005];


void bfs(int x,int c)   ///exploring node x and c is the current color which will be assigned to other nodes.
{
    for(int i=0;i<adj_list[x].size();++i)
    {
        int node =  adj_list[x][i];
        if(!color[node]) /// if node is not colored
        {
             color[node] = c;  /// assign c color to node

             /// if current color is 1 then do bfs with color 2 and vice versa.
             if(c==1)
                 bfs(node,2);
             else
                 bfs(node,1);
        }
       else if(color[node]!=c)   // if node is already colored and color of node is not equal to the current color
        {
            cycle_found=true;
            return;
        }

    }
}


int main()
{
    int test;
    scanf("%d",&test);

    for(int testno=1;testno<=test;++testno)
    {
        int bugs,I;
        scanf("%d%d",&bugs,&I);

        memset(adj_list,0,sizeof(adj_list));

        for(int i=0;i<I;++i)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            adj_list[a].push_back(b);
            adj_list[b].push_back(a);
        }

        cycle_found = false;
        memset(color,0,sizeof(color));

        for(int i=1;i<=bugs;++i)
        {
            if(!color[i])  /// if we have not colored  ith node
            {
                color[i] = 1;  /// set the color of ith node to 1
                bfs(i,2);       ///explore the ith node with color 2
            }

             if(cycle_found) /// If we find any odd cycle , then break
                break;
        }

        if(cycle_found)
            printf("Scenario #%d:\nSuspicious bugs found!\n",testno);
        else
             printf("Scenario #%d:\nNo suspicious bugs found!\n",testno);

    }
  return 0;
}

