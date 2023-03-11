#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<int> parent;
vector<vector<int>> tree;
vector<bool> visited;

void getParent(int node, int par){
    for(int i = 0 ; i < tree[node].size(); i++){
        if(tree[node][i] != par){
            parent[tree[node][i]] = node;
            getParent(tree[node][i], node);
        }
    }
}

int LCA(int u, int v, int n){
    int ans;
    vector<int> u_to_root(n);//first is distance, second is node
    int count = 0;
    while(true){
        visited[u] = true; //mark the route from u to the root
        if(u == 1) {//if u tranverse to the root, the loop break.
            u_to_root[u] = count;
            //cout << "u_to_root[" << u << "]: " << count << endl;
            break;
        }
        u_to_root[u] = count;
        //cout << "u_to_root[" << u << "]: " << count << endl;
        u = parent[u];//traverse from u to the root
        count++;
    }
    int v_to_u_lca = 0;
    while(true){
        if(visited[v] == true){//if v is visited by u, then v is the lca of u and v.
            break;
        }
        v = parent[v];//traverse from v to the root
        v_to_u_lca++;
    }
    //cout << "v_to_u_lca: " << v_to_u_lca << endl;
    //cout << "u_to_root[v]: "<< u_to_root[v] << endl;
    ans = v_to_u_lca + u_to_root[v];
    visited.clear();
    visited.resize(n + 1, 0);
    return ans;
}

int main(){
    std :: ios :: sync_with_stdio ( false );
    std :: cin . tie ( 0 );
    int n; cin >> n;
    parent.resize(n + 1);
    tree.resize(n + 1);
    visited.resize(n + 1);
    for(int i = 0 ; i < n - 1 ; i++){
        int tmp1, tmp2;
        cin >> tmp1 >> tmp2;
        tree[tmp1].push_back(tmp2);
        tree[tmp2].push_back(tmp1);
    }
    getParent(1, -1);//1 is the root, -1 means no parent
    int Q; cin >> Q;
    while(Q--){
        int p, q;
        cin >> p >> q;
        cout << LCA(p, q, n) << endl;
    }
    return 0;
}