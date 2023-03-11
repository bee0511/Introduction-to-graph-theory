#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std;

class Graph{
public:
    int V;
    int start = -1;
    int end = -1;
    vector<vector<int>> adj;
    vector<int> joint;
    vector<int> deg;
    vector<pair<int, int>> leaf;
    vector<int> start_length;
    vector<int> end_length;
    deque<int> mid;
    
    Graph(int);
    void add_edge(int, int);
    pair<int, int> leaf_length(int, int);
    void create_leaf();
    void start_end();
    void create_middle();
    void keychain(vector<deque<int>>&);
    void check(vector<deque<int>>, vector<int>);
};

Graph::Graph(int num){
    this->V = num;
    adj.resize(V);
    deg.resize(V);
    for(int i=0; i<V; i++)
        deg[i] = 0;
}

void Graph::add_edge(int a, int b){
    adj[a].push_back(b);
    deg[a]++;
    if(adj[a].size() == 3) joint.push_back(a);
    adj[b].push_back(a);
    deg[b]++;
    if(adj[b].size() == 3) joint.push_back(b);
}

pair<int, int> Graph::leaf_length(int cur, int length){
    int pre = -1;
    while(deg[cur] != 3){
        int next=0;
        for(int i = 0 ; i < adj[cur].size(); i++){
            if(adj[cur][i] == pre) continue;
            next = adj[cur][i];
        }
        pre = cur;
        cur = next;
        length++;
    }
    for(int i = 0 ; i < adj[cur].size() ; i++){
        if(adj[cur][i] == pre){
            adj[cur].erase(adj[cur].begin() + i);
        }
    }
    return make_pair(length, cur);
}

void Graph::create_leaf(){
    // first = length
    // second = the join that the leaf is attached to
    for(int i=0; i<deg.size() ; i++)
        if(deg[i] == 1) leaf.push_back(leaf_length(i, 0));
}

void Graph::start_end(){
    for(int i=0; i<leaf.size(); i++){
        for(int j=i+1; j<leaf.size(); j++){
            if(leaf[i].second == leaf[j].second) {
                if (start == -1) {
                    start = leaf[i].second;
                    start_length.push_back(leaf[i].first);
                    start_length.push_back(leaf[j].first);
                }
                else {
                    end = leaf[i].second;
                    end_length.push_back(leaf[i].first);
                    end_length.push_back(leaf[j].first);
                }
            }
        }
    }
}

void Graph::create_middle(){
    int cur = start;
    int pre = -1;
    
    while(cur != end){
        int next = 0;
        for(int i = 0 ; i < adj[cur].size() ; i++){
            if(adj[cur][i] == pre) continue;
            next = adj[cur][i];
        }
        for(int i = 0 ; i < leaf.size() ; i++){
            if(leaf[i].second == cur && cur != start)
                mid.push_back(leaf[i].first);
        }
        pre = cur;
        cur = next;
    }
}

void Graph::keychain(vector<deque<int>> &keychain){
    // 8 keys
    keychain[0].push_front(start_length[0]);
    keychain[0].push_back(end_length[0]);
    keychain[1].push_front(start_length[0]);
    keychain[1].push_back(end_length[1]);
    keychain[2].push_front(start_length[1]);
    keychain[2].push_back(end_length[0]);
    keychain[3].push_front(start_length[1]);
    keychain[3].push_back(end_length[1]);
    
}

void Graph::check(vector<deque<int>> keychain, vector<int> key){
    bool flag = false;
    for(int i=0; i<4; i++){
        if(keychain[i].size() != key.size())
            break;
        for(int j=0; j<keychain[i].size(); j++){
            if(keychain[i][j] != key[j])
                break;
            if(j == keychain[i].size()-1)
                flag = true;
        }
    }
    for(int i=0; i<4; i++){
        reverse(keychain[i].begin(), keychain[i].end());
        if(keychain[i].size() != key.size())
            break;
        for(int j=0; j<keychain[i].size(); j++){
            if(keychain[i][j] != key[j])
                break;
            if(j == keychain[i].size()-1)
                flag = true;
        }
    }

    if(flag) cout << "YES" << endl;
    else cout << "NO" << endl;
}

int main(){
    int n;
    cin >> n;
    Graph g(n);
    
    for(int i=0; i<n-1; i++){
        int a, b;
        cin >> a >> b;
        g.add_edge(a, b);
    }
    
    int m;
    cin >> m;
    vector<int> key;
    for(int i=0; i<m; i++){
        int x;
        cin >> x;
        key.push_back(x);
    }
    
    g.create_leaf();
    g.start_end();
    g.create_middle();
    
    vector<deque<int>> keychain(4, g.mid);
    g.keychain(keychain);
    g.check(keychain, key);
    
    return 0;
}
