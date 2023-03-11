#include <bits/stdc++.h>
#define tiii tuple<int,int,int>


using namespace std;

const int inf=0x3f3f3f3f;

struct cmp{
    bool operator()(pair<int,int>a,pair<int,int>b){
        return a.second>b.second;
    }
};

struct Edge4Tarjan{
    int v;
    tiii edge;
    Edge4Tarjan(int _v,tiii _e){
        v=_v;edge=_e;
    }
};

void dijkstra(int& n,int start,vector<vector<pair<int,int>>>& edge,vector<set<tiii>>& path,vector<int>& dist){
    dist=vector<int>(n+1,inf);
    dist[start]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,cmp>pq;
    int u,d;
    pq.push(make_pair(start,0));
    if(start==1){
        while(pq.size()){
            tie(u,d)=pq.top();pq.pop();
            if(d>dist[u]) continue;
            for(auto i:edge[u]){
                if(dist[i.first]>dist[u]+i.second){
                    dist[i.first]=dist[u]+i.second;
                    path[i.first].clear();
                    path[i.first].insert(make_tuple(u,i.first,i.second));
                    pq.push(make_pair(i.first,dist[i.first]));
                }else if(dist[i.first]==dist[u]+i.second){
                    path[i.first].insert(make_tuple(u,i.first,i.second));
                }
            }
        }
    }else if(start==2){
        while(pq.size()){
            tie(u,d)=pq.top();pq.pop();
            if(d>dist[u]) continue;
            for(auto i:edge[u]){
                if(dist[i.first]>dist[u]+i.second){
                    dist[i.first]=dist[u]+i.second;
                    pq.push(make_pair(i.first,dist[i.first]));
                }
            }
        }
    }
}

void tarjan(int u,vector<vector<Edge4Tarjan>>& edge, vector<bool>& visited, vector<int>& parent, vector<int>& disc, vector<int>& low, set<tiii>& bridge, int& t){
    t++;
    visited[u]=1;
    disc[u]=t;low[u]=t;
    for(int i=0;i<edge[u].size();i++){
        int v=edge[u][i].v;
        if(!visited[v]){
            parent[v]=u;
            tarjan(v,edge,visited,parent,disc,low,bridge,t);
            if(low[v]<low[u]) low[u]=low[v];
            if(disc[u]<low[v]) bridge.insert(edge[u][i].edge);
        }else if(v!=parent[u]){
            if(disc[v]<low[u]) low[u]=disc[v];
        }
    }
}


void findbridge(int n,vector<vector<pair<int,int>>>& edge,set<tiii>& bridge){
    vector<bool>visited(n+1,false);
    vector<int>disc(n+1,0);  //discovery time
    vector<int>low(n+1,0);   //low time
    vector<int>parent(n+1,0);
    int t=0;
    vector<vector<Edge4Tarjan>>edge_temp(n+1);
    for(int i=1;i<=n;i++){
        for(pair<int,int> j:edge[i]){
            edge_temp[i].push_back(Edge4Tarjan(j.first,make_tuple(i,j.first,j.second)));
            edge_temp[j.first].push_back(Edge4Tarjan(i,make_tuple(i,j.first,j.second)));
        }
    }
    tarjan(1,edge_temp,visited,parent,disc,low,bridge,t);
}


void build_short_edge(int& n,vector<set<tiii>>&path,vector<vector<pair<int,int>>>&short_edge,set<int>&pass){
    queue<int>q;
    vector<bool>visited(n+1,false);
    int u,v,w,temp;
    q.push(2);
    visited[2]=1;
    while(q.size()){
        pass.insert(q.front());
        for(auto i:path[q.front()]){
            tie(u,v,w)=i;
            short_edge[u].push_back(make_pair(v,w));
            if(visited[u]==0){
                q.push(u);
                visited[u]=1;
            }
        }
        q.pop();
    }
}

int main()
{
    cin.tie(0);ios::sync_with_stdio(0);
    int n,m,u,v,w;
    cin>>n>>m;
    vector<tiii>all_edge;
    vector<vector<pair<int,int>>>edge(n+1);
    vector<vector<pair<int,int>>>edge_rev(n+1);
    vector<set<tiii>>path(n+1);
    vector<int>dist1; //dist from 1
    vector<int>dist2; //dist to 2
    for(int i=0;i<m;i++){
        cin>>u>>v>>w;
        all_edge.push_back(make_tuple(u,v,w));
        edge[u].push_back(make_pair(v,w));
        edge_rev[v].push_back(make_pair(u,w));
    }
    //cout<<"build edge finish\n";
    dijkstra(n,1,edge,path,dist1);
    dijkstra(n,2,edge_rev,path,dist2);
    //cout<<"Dijkstra finish\n";
    vector<vector<pair<int,int>>>short_edge(n+1);
    set<int>pass;
    //for(auto i:path[2]){
    //    tie(u,v,w)=i;
    //    short_edge[u].push_back(make_pair(v,w));
    //}
    build_short_edge(n,path,short_edge,pass);
    set<tiii>bridge;
    findbridge(n,short_edge,bridge);
    //cout<<"SHORTEST PATH: "<<dist1[2]<<"\n";
    //for(int i=1;i<=n;i++){
    //    for(int j=0;j<short_edge[i].size();j++){
    //        cout<<i<<" "<<short_edge[i][j].first<<" "<<short_edge[i][j].second<<"\n";
    //    }
    //}
    //cout<<"\n\n";
    //cout<<"BRIDGE:\n";
    //for(auto i:bridge){
    //    cout<<get<0>(i)<<" "<<get<1>(i)<<" "<<get<2>(i)<<"\n";
    //}
    //cout<<"PASSED:\n";
    //for(auto i:pass) cout<<i<<" ";
    //cout<<"\n\n";
    for(auto i:all_edge){
        tie(u,v,w)=i;
        if(path[v].find(i)!=path[v].end()&&pass.find(v)!=pass.end()){   //edge is in the short path
            cout<<(bridge.find(i)==bridge.end()?"SOSO\n":"SAD\n");
        }else{                                 //edge is out of the short path
            cout<<(dist1[v]+w+dist2[u]<dist1[2]?"HAPPY\n":"SOSO\n");
        }
    }
    return 0;
}
