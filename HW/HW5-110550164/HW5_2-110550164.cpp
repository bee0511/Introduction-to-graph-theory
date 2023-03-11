#include <iostream>
#include <climits>
#include <vector>

using namespace std;

class Graph{
    public:
    int V;
    vector<vector<int>> adj;
    vector<int> deg;
    Graph(int V){
        this->V = V;
        adj = vector<vector<int>>(V);
        deg = vector<int>(V, 0);
    }
    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    int minDeg(){
        int min = INT_MAX;
        for(int i = 1; i < V; i++){
            if(min > deg[i]) min = deg[i];
        }
        return min;
    }
};

int main(){
    int n, m;
    cin >> n >> m;
    Graph g(n + 1);
    while(m--){
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }
    cout << g.minDeg() << endl;
    return 0;
}