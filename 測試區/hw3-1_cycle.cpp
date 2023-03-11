#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <algorithm>
#include <queue>
#include <functional>
#include <iomanip>
using namespace std;
#define INF 0x3f3f3f3f
class Edge{
    public:
    int u;
    int v;
    int weight;

    Edge();
    Edge(int u, int v, int w){
        this->u = u;
        this->v = v;
        this->weight = w;
    }
    void push_back(int u, int v, int w){
        this->u = u;
        this->v = v;
        this->weight = w;
    }
};

class Graph{
    public:
    int V;
    list<pair<int, int>> *adja;
    vector<Edge> Edge_arr;
    Graph(int V){
        this->V = V;
        adja = new list<pair<int, int>> [V];
    }

    void addEdge(int u, int v, int w){
        
        //cout << "u " << endl;
        adja[u].push_back(pair<int, int>(v, w));
        //cout << "v " << endl;
        adja[v].push_back(pair<int, int>(u, w));
        //cout << "push edge_arr " << endl;
        Edge_arr.push_back(Edge(u, v, w));
        cout <<  "add: " << u << " " << v << " with weight: " << w << endl;
    }

    void removeEdge(int u, int v, int w){
        adja[u].remove(pair<int, int>(v, w));
        adja[v].remove(pair<int, int>(u, w));
    }

    int ShortestPath(int start, int end){
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // Create a vector for distances and initialize all
    // distances as infinite (INF)
        vector<int> dist(V, INF); 
    // Insert source itself in priority queue and initialize
    // its distance as 0.
        pq.push(pair<int, int>(0, start));
        dist[start] = 0;
        int u = pq.top().second;
        list<pair<int, int>>::iterator i;
        cout << u << "'s neighbor: ";
        for(i = adja[u].begin(); i != adja[u].end() ; i++){
            cout << i->second << " ";
        }
        cout << endl;
    /* Looping till priority queue becomes empty (or all distances are not finalized) */
        while (!pq.empty()) {
            // The first vertex in pair is the minimum distance
            // vertex, extract it from priority queue.
            // vertex label is stored in second of pair (it
            // has to be done this way to keep the vertices
            // sorted distance (distance must be first item
            // in pair)
            int u = pq.top().second;
            cout << "u: " << u << endl;
            pq.pop();
    
            // 'i' is used to get all adjacent vertices of a
            // vertex
            list<pair<int, int> >::iterator i;
            for (i = adja[u].begin(); i != adja[u].end(); ++i) {
                // Get vertex label and weight of current
                // adjacent of u.
                int v = (*i).first;
                int weight = (*i).second;
                cout << "v: " << v << ", weight: " << weight << endl;
                // If there is shorted path to v through u.
                if (dist[v] > dist[u] + weight) {
                    // Updating distance of v
                    cout << "dist[" << v << "] = " << dist[v] << " > dist[" << u << "] = " << dist[u] << " + weight = " << weight << endl;
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                    cout << "dist[" << v << "] change to "<< dist[v] << endl;
                }
            }
        }
        
        for(int i = 0 ; i < V ; i++){
            cout << "distance from " << start << " to ";
            cout << i << " is : " << dist[i] << endl;
        }
        system("pause");
        return dist[end];
    }

    int FindMinimumCycle ( )
    {
        int min_cycle = INT_MAX;
        int E = Edge_arr.size();
        for ( int i = 0 ; i < E ; i++ )
        {
            // current Edge information
    
            // get current edge vertices which we currently
            // remove from graph and then find shortest path
            // between these two vertex using Dijkstra’s
            // shortest path algorithm .
            removeEdge( Edge_arr[i].u, Edge_arr[i].v, Edge_arr[i].weight ) ;
    
            // minimum distance between these two vertices
            int distance = ShortestPath( Edge_arr[i].u, Edge_arr[i].v );
            cout << "shortest path from " << Edge_arr[i].u << " to " << Edge_arr[i].v << " is: " << distance << endl;
            // to make a cycle we have to add weight of
            // currently removed edge if this is the shortest
            // cycle then update min_cycle
            min_cycle = min( min_cycle, distance + Edge_arr[i].weight );
    
            // add current edge back to the graph
            addEdge( Edge_arr[i].u, Edge_arr[i].v, Edge_arr[i].weight );
        }
    
        // return shortest cycle
        return min_cycle ;
    }
};

int main(){
    int Q; cin >> Q;
    while(Q--){
        int n, m; cin >> n >> m;
        vector<int> cost(n);
        for(int i = 0 ; i < n ; i++){
            cin >> cost[i];
        }
        vector<vector<bool>> check(n, vector<bool>(n, false));
        vector<queue<int>> special(n);
        for(int i = 0 ; i < m ; i++){
            int tmp1, tmp2, val;
            cin >> tmp1 >> tmp2 >> val;
            tmp1--; tmp2--;
            special[tmp1].push(tmp2);
            special[tmp1].push(val);
            special[tmp2].push(tmp1);
            special[tmp2].push(val);
            check[tmp1][tmp2] = true;
            check[tmp2][tmp1] = true;
        }
        Graph g(n);
        //cout << "=== init success ===" << endl;
        for(int i = 0 ; i < n ; i ++){
            for(int j = 0 ; j < n ; j++){
                if(i == j) continue;
                if(check[i][j]){
                    //cout << "special: " << endl;
                    special[i].pop();
                    g.addEdge(i, j, min(cost[i] + cost[j], special[i].front()));
                    special[i].pop();
                    continue;
                }
                g.addEdge(i, j, cost[i] + cost[j]);
            }
        }
        cout << "=== g.FindMinimumCycle() ===" << endl;
        cout << g.FindMinimumCycle() << endl;
    }
    return 0;
}