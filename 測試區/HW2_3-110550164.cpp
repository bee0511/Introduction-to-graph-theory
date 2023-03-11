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
    bool flag = false;
    vector<vector<int>> adj;
    vector<int> joint;
    vector<int> deg;
    vector<pair<int, int>> leaf;
    vector<int> start_length;
    vector<int> end_length;
    deque<int> bone;
    vector<deque<int>> possible_key;
    
    Graph(int);
    void add_edge(int, int);
    void branch();
    pair<int, int> leaf_length(int, int);
    void start_end();
    void find_bone();
    void keychain(vector<int>);
    void execute(vector<int>);
};

Graph::Graph(int n){
    this->V = n;
    adj.resize(V+1);
    deg.resize(V+1, 0);
    possible_key.resize(4);
}

void Graph::add_edge(int a, int b){
    adj[a].push_back(b);
    deg[a]++;
    if(adj[a].size() == 3) joint.push_back(a);
    
    adj[b].push_back(a);
    deg[b]++;
    if(adj[b].size() == 3) joint.push_back(b);
}

void Graph::branch(){
    //first = length
    //second = the joint that the leaf is attached to
    for(int i=0; i<deg.size(); i++){
        if(deg[i] == 1) leaf.push_back(leaf_length(i, 0));
    }
}

pair<int, int> Graph::leaf_length(int cur, int length){
    int pre = -1;
    while(deg[cur] != 3){
        int next;
        for(int i=0; i<adj[cur].size(); i++){
            if(adj[cur][i] == pre) continue;
            next = adj[cur][i];
        }
        pre = cur;
        cur = next;
        
        length++;
    }
    for(int i=0; i<adj[cur].size(); i++){
        if(adj[cur][i] == pre){
            adj[cur].erase(adj[cur].begin() + i);
        }
    }
    return make_pair(length, cur);
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

void Graph::find_bone(){
    int cur = start;
    int pre = -1;
    while(cur != end){
        int next;
        for(int i=0; i<adj[cur].size(); i++){
            if(adj[cur][i] == pre) continue;
            next= adj[cur][i];
        }
        for(int i=0; i<leaf.size(); i++){
            if(leaf[i].second == cur && cur != start)
                bone.push_back(leaf[i].first);
        }
        pre = cur;
        cur = next;
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<bone.size(); j++)
            possible_key[i][j] = bone[j];
    }
}

void Graph::keychain(vector<int> key){
    possible_key[0].push_front(start_length[0]);
    possible_key[0].push_back(end_length[0]);
    possible_key[1].push_front(start_length[0]);
    possible_key[1].push_back(end_length[1]);
    possible_key[2].push_front(start_length[1]);
    possible_key[2].push_back(end_length[0]);
    possible_key[3].push_front(start_length[1]);
    possible_key[3].push_back(end_length[1]);
    
    for(int i=0; i<4; i++){
        if(possible_key[i].size() != key.size()) break;
        for(int j=0; j<possible_key[i].size(); j++){
            if(possible_key[i][j] != key[j]) break;
            if(j == possible_key[i].size()-1)
                flag = true;
        }
    }
    for(int i=0; i<4; i++){
        reverse(possible_key[i].begin(), possible_key[i].end());
        if(possible_key[i].size() != key.size()) break;
        for(int j=0; j<possible_key[i].size(); j++){
            if(possible_key[i][j] != key[j]) break;
            if(j == possible_key[i].size() - 1)
                flag = true;
        }
    }
}

void Graph::execute(vector<int> key){
    branch();
    start_end();
    find_bone();
    keychain(key);
    
    if(flag == true) cout << "YES" << endl;
    else cout << "NO" << endl;
}

int main(){
    int n; cin >> n;
    n -= 1;
    Graph g(n);
    
    while(n--){
        int a, b;
        cin >> a >> b;
        g.add_edge(a, b);
    }
    
    int m;
    cin >> m;
    vector<int> key;
    while(m--){
        int x;
        cin >> x;
        key.push_back(x);
    }

    g.execute(key);
    
    return 0;
}
