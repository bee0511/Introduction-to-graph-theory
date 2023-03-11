#include <iostream>
#include <queue>
#include <vector>
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
    void print(){
        for(int i = 1 ; i < V ; i++){
            if(dist[i] == LLONG_MAX) cout << i << ":-1 ";
            else cout << i << ": " << dist[i] << " ";
        }
        cout << endl;
    }
    void modifyAllWeight(int w){
        for(int i = 1 ; i < V ; i++){
            if(dist[i] != LLONG_MAX) dist[i] += w;
        }
    }
    void removeEdge(long long v){
        adj[v].clear();
    }

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
    std :: ios :: sync_with_stdio ( false );
    std :: cin . tie ( 0 );
    int n, m, p, q, t, T;
    cin >> n >> m >> p >> q >> t >> T;
    Graph virus(n + 1), antivirus(n + 1);

    for(int i = 0 ; i < m ;i++){
        int a, b, w;
        cin >> a >> b >> w;

        virus.addEdge(a, b, w);
        antivirus.addEdge(a, b, 1);
    }

    queue<int> cur_virus;
    for(int i = 0 ; i < p ; i++){
        int v; cin >> v;
        cur_virus.push(v);
    }
    queue<int> cur_antivirus;
    for(int i = 0 ; i < q; i++){
        int u; cin >> u;
        cur_antivirus.push(u);
    }
    while(cur_antivirus.size()){
        antivirus.shortestPath(cur_antivirus.front());
        cur_antivirus.pop();
    }
    while(cur_virus.size()){
        virus.shortestPath(cur_virus.front());
        cur_virus.pop();
    }
    //virus.print();
    antivirus.modifyAllWeight(t);
    //antivirus.print();
    int count = 0;
    for(int i = 1 ; i <= n ; i++){
        if(virus.dist[i] < antivirus.dist[i] && virus.dist[i] < T) count++;
    }
    cout << count;
    return 0;
}