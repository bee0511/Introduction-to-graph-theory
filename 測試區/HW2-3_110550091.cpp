#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

class Graph{
    
public:
    int V;
    int j;
    int l=0;
    list<int> *adj;
    list<int> *joint;
    bool *visited;
    bool *visited_;
    
    Graph(int);
    void addEdge(int, int);
    int DFS(int, int*, int);
    void DFS_(int, int*);
    int** traverse(int*, int);
};

Graph::Graph(int num){
    this->V = num;
    adj = new list<int>[V+1];
    joint = new list<int>[V];
    visited = new bool[V+1];
    for(int i=0; i<=V; i++) visited[i] = false;
    visited_ = new bool[V+1];
    for(int i=0; i<=V; i++) visited_[i] = false;
}

void Graph::addEdge(int x, int y){
    adj[x].push_back(y);
    adj[y].push_back(x);
}

int** Graph::traverse(int *degree, int joint){
    int **length = 0;
    length = new int*[V+1];
    for(int i=0; i<=V; i++)
        length[i] = new int[5];
    
    for(int i=0; i<V; i++){
        int cnt=0;
        if(degree[i] == 1){
            cnt = DFS(i, degree, cnt);
            length[i][0] = j;
            length[i][1] = cnt;
        }
    }
    return length;
}

int Graph::DFS(int x, int *degree, int cnt){
    visited[x] = true;
    
    for(auto it : adj[x]) {
        if(degree[it] == 3) {
            j = it;
            return cnt+1;
        }
        if(!visited[it]) cnt += DFS(it, degree, cnt);
    } cnt++;
    return cnt;
}

void Graph::DFS_(int x, int *degree){
    visited_[x] = true;
    if(degree[x] == 3) joint[l++].push_back(x);
    
    for(auto it : adj[x])
        if(!visited_[it]) DFS_(it, degree);
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie();
    int n, m, a, b, joint=0;
    cin >> n;
    int degree[n+5];
    for(int i=0; i<=n; i++){
        degree[i] = 0;
    }
    Graph g(n+1);
    for(int i=0; i<n-1; i++){
        cin >> a >> b;
        degree[a]++;
        degree[b]++;
        g.addEdge(a, b);
    }
    cin >> m;
    int key[m];
    for(int i=0; i<m; i++)
        cin >> key[i];
    
    for(int i=0; i<n; i++) {
        if(degree[i] == 3) joint++;
    }

    if(joint!=m) {
        cout << "NO\n";
        return 0;
    }
    
    int **length = 0;
    length = new int*[n+1];
    for(int i=0; i<n; i++)
        length[i] = new int[5];
    length = g.traverse(degree, joint);
    
    list<int> startend;
    int track[n+1];
    for(int i=0; i<n; i++){
        track[i] = 0;
        if(!length[i][1]) track[length[i][0]]++;
    }
    
    for(int i=0; i<n; i++){
        if(track[i] == 2) startend.push_front(i);
    }
    
    g.DFS_(startend.front(), degree);
    
    for(int i=0; i<n; i++){
        for(int j=0; j<joint; j++){
            if(length[i][0] == g.joint[j].front()) {
                g.joint[j].push_back(length[i][1]);
                //cout << "length[i][0]: " << length[i][0] << " , length[i][1]: " << length[i][1] << endl;
            }
        }
    }
    
    int keychain[10][joint];
    for(int i=0; i<8; i++){
        for(int j=0; j<joint; j++)
            keychain[i][j] = 0;
    }
    
    list<int>::iterator it_begin = g.joint[0].begin();
    int temp = 0;
    for(int i=0; i<2; i++){
        advance(it_begin, 1);
        for(int j=0; j<2; j++){
            keychain[temp++][0] = *it_begin;
        }
    }
    for(int i=0; i<4; i++){
        for(int j=1; j<joint-1; j++){
            list<int>::iterator it_mid = g.joint[j].begin();
            advance(it_mid, 1);
            keychain[i][j] = *it_mid;
        }
    }
    list<int>::iterator it_end = g.joint[joint-1].begin();
    temp = 0;
    advance(it_end, 1);
    for(int j=0; j<2; j++){
        keychain[temp][joint-1] = *it_end;
        temp +=2;
    }
    temp = 1;
    advance(it_end, 1);
    for(int j=0; j<2; j++){
        keychain[temp][joint-1] = *it_end;
        temp +=2;
    }
    
    bool flag = false;
    for(int i=0; i<4; i++){
        for(int j=0; j<joint; j++){
//            cout << keychain[i][j] << " ";
            if(key[j] != keychain[i][j]) break;
            if(key[j] == keychain[i][j] && j == joint - 1) flag = true;
        } //cout << endl;
    }
    if(!flag){
        for(int i=0; i<4; i++){
            for(int j=0; j<joint; j++){
//                cout << keychain[i][joint-j-1] << " ";
                if(key[joint-j-1] != keychain[i][j]) break;
                if(key[joint-j-1] == keychain[i][j] && j == joint - 1) flag = true;
            } //cout << endl;
        }
    }
    
    if(flag) cout << "YES\n";
    else cout << "NO\n";
    
    return 0;
}
