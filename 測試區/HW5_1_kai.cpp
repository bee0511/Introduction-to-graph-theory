#include <bits/stdc++.h>

using namespace std;

struct BFS{
    int v;
    vector<int>path;
    BFS(){}
    BFS(int a,vector<int>vv){
        v=a;path=vv;
    }
};

bool findK5(int n,vector<vector<bool>>mat);
bool checkK5(int a,int b,int c,int d,int e,int n,vector<vector<bool>>&mat);
bool findpath(int a,int b,int n,vector<vector<bool>>&mat,vector<bool>& visited);
bool findK33(int n,vector<vector<bool>>mat);
bool checkK33(int a,int b,int c,int d,int e,int f,int n,vector<vector<bool>>&mat);

int main()
{
    int Q,n,m,u,v;
    cin>>Q;
    while(Q--){
        cin>>n>>m;
        vector<set<int>>edge(n+1);
        for(int i=0;i<m;i++){
            cin>>u>>v;
            edge[u].insert(v);
            edge[v].insert(u);
        }
        set<int>::iterator a,b;
        for(int i=1;i<=n;i++){
            if(edge[i].size()==2){
                b=edge[i].begin();
                a=b++;
                edge[*b].insert(*a);
                edge[*b].erase(i);
                edge[*a].insert(*b);
                edge[*a].erase(i);
                edge[i].clear();
            }
        }
        int N=0,M=0;
        for(int i=1;i<=n;i++){
            if(edge[i].size()){
                N+=1;
                M+=edge[i].size();
            }
        }
        M=M/2;
        vector<vector<bool>>mat(N+1,vector<bool>(N+1,false));
        map<int,int>trans;int temp=1;
        for(int i=1;i<=n;i++){
            if(edge[i].size()){
                trans[i]=temp++;
            }
        }
        for(int i=1;i<=n;i++){
            for(auto j:edge[i]){
                mat[trans[i]][trans[j]]=true;
            }
        }
        /*for(int i=1;i<=N;i++){
            for(int j=1;j<=N;j++){
                cout<<mat[i][j]<<" ";
            }
            cout<<"\n";
        }*/
        if(findK5(N,mat)){
            cout<<"No\n";
            continue;
        }
        if(findK33(N,mat)){
            cout<<"No\n";
            continue;
        }
        cout<<"Yes\n";
    }

    return 0;
}

bool findK5(int n,vector<vector<bool>>mat){
    bool already_find=false;
    for(int i1=1;i1<=n;i1++){
        for(int i2=1;i2<=n;i2++){
            if(i1==i2) continue;
            for(int i3=1;i3<=n;i3++){
                if(i3==i1||i3==i2) continue;
                for(int i4=1;i4<=n;i4++){
                    if(i4==i1||i4==i2||i4==i3) continue;
                    for(int i5=1;i5<=n;i5++){
                        if(i5==i1||i5==i2||i5==i3||i5==i4) continue;
                        //cout<<i1<<i2<<i3<<i4<<i5<<"\n";
                        already_find=checkK5(i1,i2,i3,i4,i5,n,mat);
                        if(already_find) break;
                    }
                    if(already_find) break;
                }
                if(already_find) break;
            }
            if(already_find) break;
        }
        if(already_find) break;
    }
    return already_find;
}

bool checkK5(int a,int b,int c,int d,int e,int n,vector<vector<bool>>&mat){
    vector<bool>visited(n+1,false);
    visited[a]=true;
    visited[b]=true;
    visited[c]=true;
    visited[d]=true;
    visited[e]=true;
    if(findpath(a,b,n,mat,visited)==false) return false;
    if(findpath(a,c,n,mat,visited)==false) return false;
    if(findpath(a,d,n,mat,visited)==false) return false;
    if(findpath(a,e,n,mat,visited)==false) return false;
    if(findpath(b,c,n,mat,visited)==false) return false;
    if(findpath(b,d,n,mat,visited)==false) return false;
    if(findpath(b,e,n,mat,visited)==false) return false;
    if(findpath(c,d,n,mat,visited)==false) return false;
    if(findpath(c,e,n,mat,visited)==false) return false;
    if(findpath(d,e,n,mat,visited)==false) return false;
    return true;
}

bool findpath(int a,int b,int n,vector<vector<bool>>&mat,vector<bool>& visited){
    queue<BFS>q;
    BFS temp;
    temp.v=a;temp.path.push_back(a);
    q.push(temp);
    vector<bool>bfs_visited=visited;
    while(q.size()){
        temp=q.front();q.pop();
        if(mat[temp.v][b]==1) break;
        for(int i=1;i<=n;i++){
            if(mat[temp.v][i]==true&&bfs_visited[i]==false){
                temp.path.push_back(i);
                q.push(BFS(i,temp.path));
                temp.path.pop_back();
                bfs_visited[i]=true;
            }
        }
    }
    if(mat[temp.v][b]==1){
        for(int i=0;i<temp.path.size();i++){
            visited[temp.path[i]]=true;
        }
        return true;
    }
    return false;
}

bool findK33(int n,vector<vector<bool>>mat){
    bool already_find=false;
    for(int i1=1;i1<=n;i1++){
        for(int i2=1;i2<=n;i2++){
            if(i1==i2) continue;
            for(int i3=1;i3<=n;i3++){
                if(i3==i1||i3==i2) continue;
                for(int i4=1;i4<=n;i4++){
                    if(i4==i1||i4==i2||i4==i3) continue;
                    for(int i5=1;i5<=n;i5++){
                        if(i5==i1||i5==i2||i5==i3||i5==i4) continue;
                        for(int i6=1;i6<=n;i6++){
                            if(i6==i1||i6==i2||i6==i3||i6==i4||i6==i5) continue;
                            //cout<<i1<<i2<<i3<<i4<<i5<<"\n";
                            already_find=checkK33(i1,i2,i3,i4,i5,i6,n,mat);
                            if(already_find) break;
                        }
                        if(already_find) break;
                    }
                    if(already_find) break;
                }
                if(already_find) break;
            }
            if(already_find) break;
        }
        if(already_find) break;
    }
    return already_find;
}

bool checkK33(int a,int b,int c,int d,int e,int f,int n,vector<vector<bool>>&mat){
    vector<bool>visited(n+1,false);
    visited[a]=true;
    visited[b]=true;
    visited[c]=true;
    visited[d]=true;
    visited[e]=true;
    visited[f]=true;
    if(findpath(a,d,n,mat,visited)==false) return false;
    if(findpath(a,e,n,mat,visited)==false) return false;
    if(findpath(a,f,n,mat,visited)==false) return false;
    if(findpath(b,d,n,mat,visited)==false) return false;
    if(findpath(b,e,n,mat,visited)==false) return false;
    if(findpath(b,f,n,mat,visited)==false) return false;
    if(findpath(c,d,n,mat,visited)==false) return false;
    if(findpath(c,e,n,mat,visited)==false) return false;
    if(findpath(c,f,n,mat,visited)==false) return false;
    return true;
}