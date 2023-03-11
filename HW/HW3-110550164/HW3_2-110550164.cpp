#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <climits>

using namespace std;

#define INF 0x3f3f3f3f

typedef pair<long long, long long> iPair;

class Graph {
    public:
    int V;
    list<pair<long long, long long> >* adj;
    vector<long long> dist;
public:
    Graph(int V); 
    void addEdge(long long u, long long v, long long w);
    void shortestPath(int s);
};
Graph::Graph(int V){
    this->V = V;
    adj = new list<iPair>[V];
    dist = vector<long long>(V, LLONG_MAX);
}
 
void Graph::addEdge(long long u, long long v, long long w){
    adj[u].push_back(make_pair(v, w));
}
void Graph::shortestPath(int src){
    priority_queue<iPair, vector<iPair>, greater<iPair> > pq;
    pq.push(make_pair(0, src));
    dist[src] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        list<pair<long long, long long> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {

            int v = (*i).first;
            long long weight = (*i).second;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int T, sub;
    cin >> T >> sub;
    while(T--){
        
        int n, m, k;
        cin >> n >> m >> k;
        Graph g_from_1(n + 5);
        Graph g_from_n(n + 5);
        Graph g_from_N(n + 5);
        for(int i = 0 ; i < m ; i++){
            int u, v, w;
            cin >> u >> v >> w;
            g_from_1.addEdge(v, u, w); //invert the edge set
            g_from_n.addEdge(v, u, w); 
            g_from_N.addEdge(v, u, w);
        }
        g_from_1.shortestPath(1);
        g_from_n.shortestPath(n);
        for(int i = 1; i <= n; i++){
            if(g_from_1.dist[i] >= LLONG_MAX || g_from_n.dist[i] >= LLONG_MAX){
                //g_from_N.addEdge(n + 1, i, LLONG_MAX);
                continue;
            }
            g_from_N.addEdge(n + 1, i, g_from_1.dist[i] + g_from_n.dist[i]);
        }
        g_from_N.shortestPath(n + 1);
        if(k == 1){
            for(int i = 1 ; i <= n ; i++){
                if(g_from_1.dist[i] >= LLONG_MAX) cout << "-1 ";
                else cout << g_from_1.dist[i] << " ";
            }
            cout << endl;
        }
        else{
            for(int i = 1 ; i <= n ; i++){
                if(g_from_1.dist[i] == LLONG_MAX || g_from_n.dist[i] == LLONG_MAX || g_from_N.dist[i] >= LLONG_MAX) cout << "-1 ";
                else cout << g_from_N.dist[i] << " ";
            }
            cout << endl;
        }
    }
    return 0 ;
}