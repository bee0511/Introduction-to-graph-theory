#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct DisjointSets
{
    vector<int> parent, rnk;
    int n;
  
    DisjointSets(int n)
    {
        this->n = n;
        parent = vector<int>(n+1);
        rnk = vector<int>(n+1);
  
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;
  
            parent[i] = i;
        }
    }
  
    int find(int u)
    {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
  
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else
            parent[x] = y;
  
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int Q,q;
    cin>>Q;
    q=Q;
    vector<long> ans(Q,0);
    int id=0;
    while(Q--)
    {
        int n,m;
        cin>>n>>m;
        vector<int> costs(n);
        vector<pair<int,pair<int,int> > > offers;
        int minCost,minCostIdx=0;
        for(int i=0;i<n;i++)
        {
            cin>>costs[i];
            if(i==0) minCost=costs[i];
            if(costs[i]<minCost)
            {
                minCost=costs[i];
                minCostIdx=i;
            }
        }
        for(int i=0;i<m;i++)
        {
            int x,y,z;
            cin>>x>>y>>z;
            if(minCost+costs[x-1]>z||minCost+costs[y-1]>z)
            {
                offers.push_back({z,{x-1,y-1}});
            }
        }
        for(int i=0;i<n;i++)
        {
            if(i!=minCostIdx)
            {
                offers.push_back({costs[minCostIdx]+costs[i],{minCostIdx,i}});
            }
        }
        sort(offers.begin(),offers.end());
        DisjointSets ds(n);
        long curCost=0;
        int toucher=0;
        for(int i=0;i<offers.size();i++)
        {
            int u=offers[i].second.first;
            int v=offers[i].second.second;
            int set_u = ds.find(u);
            int set_v = ds.find(v);
            if (set_u != set_v)
            {
                curCost+= offers[i].first;
                ds.merge(set_u, set_v);
                toucher+=1;
                if(toucher>=n) break;
            }
        }
        ans[id]=curCost;
        id+=1;
    }
    for(int i=0;i<q;i++)
    {
        cout<<ans[i]<<"\n";
    }
}