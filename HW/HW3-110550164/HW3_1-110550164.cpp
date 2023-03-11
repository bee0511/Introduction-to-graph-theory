#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <climits>
using namespace std;
#define INF 0x3f3f3f3f

class Edge{
    public:
    int u;
    int v;
    int w;
    Edge(int u, int v, int w){
        this->u = u;
        this->v = v;
        this->w = w;
    }

};

class Graph{
    public:
    int V;
    long long sum;
    vector<int> parent;
    vector<int> cost;
    vector<Edge> special;
    Graph(int V){
        this->V = V;
        for(int i = 0 ; i < V ; i++){
            parent.push_back(i);
        }
        
        cost = vector<int> (V, 0);
        sum = 0;
    }

    int find(int x) {return x == parent[x] ? x : (parent[x] = find(parent[x]));}
    void merge(int x, int y) {parent[find(x)] = find(y);}

    static bool cmp(Edge &a, Edge &b){
        if(a.w != b.w)
            return a.w < b.w;
        else
            return a.u < b.u;
    }

    void Kruskal(){
        sort(special.begin(), special.end(), cmp);
        //cout << "special: " << endl;
        //for(auto&it : special){
        //    cout << it.u << " " << it.v << " " << it.w << endl;
        //}
        for (int i = 0, j = 0; i < V-1 && j < special.size(); ++j){
        if (find(special[j].u) == find(special[j].v)) continue;
        merge(special[j].u, special[j].v);
        sum += special[j].w;
        i++;    
        }
        cout << sum << endl;
    }
};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int Q; cin >> Q;
    while(Q--){
        int n, m; cin >> n >> m;
        Graph g(n);
        int min = INT_MAX;
        int min_index = -1;
        for(int i = 0 ; i < n ; i++){
            int tmp;
            cin >> tmp;
            g.cost[i] = tmp;
            if(min > g.cost[i]) {
                min = g.cost[i];
                min_index = i;
            }
        }
       //cout << "min_value: "  << min << endl;
       //cout << "min_index: " << min_index << endl;
        for(int i = 0 ; i < m ; i++){
            int tmp1, tmp2, val;
            cin >> tmp1 >> tmp2 >> val;
            tmp1--; tmp2--;
            if(val > g.cost[tmp1] + g.cost[tmp2] ) continue;
            g.special.push_back(Edge(tmp1, tmp2, val));
        }
        for(int i = 0 ; i < n ; i++){
            if(min_index == i) continue;
            g.special.push_back(Edge(min_index, i, min + g.cost[i]));
        }
        g.Kruskal();
    }
    return 0;
}