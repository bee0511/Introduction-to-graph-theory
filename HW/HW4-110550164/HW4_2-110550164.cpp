#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph{
    public:
    vector<vector<int>> adja;
    vector<int> low, in, vis;
    vector<int> cut_index;
    vector<bool> status;
    int timer;
    Graph(int n){
        adja = vector<vector<int>>(n);
        low = vector<int>(n);
        in = vector<int>(n);
        vis = vector<int>(n);
        status = vector<bool>(n, false);
        timer = 0;
    }
    void dfs(int node, int par){
        int nchild = 0;
        vis[node] = 1;
        in[node] = low[node] = timer;
        timer++;

        for(int child : adja[node]){

            if(child == par) continue;

            if(vis[child] == 1) low[node] = min(low[node], in[child]);
            else{
                dfs(child, node);
                low[node] = min(low[node], low[child]);
                if(low[child] >= in[node] && par != -1){
                    if(status[node] == false){
                        status[node] = true;
                        cut_index.push_back(node); 
                        //cout<<" Cross edge between "<<child<<" and "<<node<<" "<<endl;
                    }
                    
                }
                nchild++;
            }
        }
        if(par == -1 && nchild > 1){
            if(status[node] == false){
                status[node] = true;
                cut_index.push_back(node);
            }
        }
    }
};

int main(){
    int n, m;
    cin >> n >> m;
    Graph g(n + 1);
    while(m--){
        int u, v;
        cin >> u >> v;
        g.adja[u].push_back(v);
        g.adja[v].push_back(u);
    }
    g.dfs(1, -1);
    cout << g.cut_index.size() << endl;
    sort(g.cut_index.begin(), g.cut_index.end());
    for(auto &it : g.cut_index){
        cout << it << " ";
    }
    return 0;
}