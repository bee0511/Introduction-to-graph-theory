#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;

class Graph{
    int V;
    int l;
    list<int> *adj;
    vector<int> dist;
    bool *visited;
    bool *flag;
    int timer;
    vector<int> tin, tout;
    vector<vector<int>> up;
    
public:
    Graph(int);
    void dfs(int, int);
    bool is_ancestor(int, int);
    int lca(int, int);
    int calculate(int, int);
    void addEdge(int, int);
    void Dijkstra(int);
};

Graph::Graph(int num){
    this->V = num;
    adj = new list<int>[V];
    visited = new bool[V];
    for(int i=0; i<V; i++) visited[i] = false;
    flag = new bool[V];
    for(int i=0; i<V; i++) flag[i] = true;
    
    tin.resize(V);
    tout.resize(V);
    timer = 0;
    l = ceil(log2(V));
    up.assign(V, vector<int>(l + 1));
}

void Graph::addEdge(int x, int y){
    adj[x].push_back(y);
    adj[y].push_back(x);
}

void Graph::Dijkstra(int x){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, x));
    
    dist.resize(V+1, INT_MAX);
    dist[x] = 0;

    while(!pq.empty() && flag[x]){
        pair<int, int> edge = pq.top();
        pq.pop();
        int u = edge.second;

        for(auto i : adj[u]){
            int v = i;
            int alt = dist[u] + 1;
            if(alt < dist[v]){
                dist[v] = alt;
                pq.push(make_pair(alt, v));
            }
        }
    }
}

void Graph::dfs(int v, int p){
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }
    tout[v] = ++timer;
}

bool Graph::is_ancestor(int u, int v){
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int Graph::lca(int u, int v){
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

int Graph::calculate(int u, int v){
    int anc = lca(u, v);
    return (dist[u] + dist[v] - 2*dist[anc]);
}


int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, a, b, q, x, y;
    cin >> n;
    Graph g(n+1);
    
    for(int i=0; i<n-1; i++){
        cin >> a >> b;
        g.addEdge(a, b);
    }
    
    g.dfs(1, 1);
    g.Dijkstra(1);
    cin >> q;
    for(int i=0; i<q; i++){
        cin >> x >> y;
        cout << g.calculate(x, y) << "\n";
    }

    return 0;
}
