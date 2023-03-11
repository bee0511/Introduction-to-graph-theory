#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class node{
    public:
    int key;
    node* parent;
    vector<node*> child;
    node(int x,int d) {
        parent = nullptr;
        key = x;
        depth = d;
        height = -1;
    }
    int depth;
    int height;
};

class tree{
    public:
    node* root;
    vector<vector<int>> adj;
    vector<node*> leaf;
    int height;
    vector<int> parent_arr;
    vector<int> depth_arr;
    vector<int> height_arr;
    tree();
    tree(int n ){
        adj.resize(n);
        parent_arr.resize(n);
        depth_arr.resize(n, 0);
        height_arr.resize(n, 0);
        height = 0;
        return;
    }
    void dfs(node* root, node* parent){
        if(root->depth > height) height = root->depth; 
        for(int i = 0 ; i < adj[root->key].size() ; i++){
            node *child = new node(adj[root->key][i], root->depth);
            if(child->key != parent->key){
                //cout << "root: " << root->key;
                child->parent = root;
                parent_arr[child->key] = root->key;
                //cout << " parent: " << parent->key << endl;
                child->depth ++;
                depth_arr[child->key] = child->depth;
                //cout << "child: " << child->key << " depth: " << child->depth << endl;
                dfs(child, root);
            }
        }
        if(adj[root->key].size() == 1) {
            //cout << "leaf is " << root->key << endl;
            leaf.push_back(root);
        }
    }

    
    void leafDfs(node *leaf){
        int height = 0;
        while(leaf != root){
            if(height > leaf->height) {
                leaf->height = height;
                height_arr[leaf->key] = height;
            }
            height++;
            leaf = leaf->parent;
        }
    }

    void buildHeight(){
        for(int i = 0 ; i < leaf.size() ; i++){
            leafDfs(leaf[i]);
        }
    }

    void print(){
        for(int i = 1 ; i < parent_arr.size() ; i++){
            if(i == 1) cout << height << " " << -1 << endl;
            else cout << height_arr[i] << " " << parent_arr[i] << endl;
        }
        //cout << "tree height: " << height << endl;
    }

};



int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    tree t(n + 1);
    for(int i = 0 ; i < n - 1 ; i++){
        int tmp1, tmp2;
        cin >> tmp1 >> tmp2;
        t.adj[tmp1].push_back(tmp2);
        t.adj[tmp2].push_back(tmp1);
    }
    
    //for(int j = 0 ; j < t.adj[1].size() ; j++){
    //    t.pb(1, t.adj[1][j]);
    //}
    //cout << "==test==" << endl;
    t.root = new node(1, 0);
    t.dfs(t.root, new node(-1, 0));
    //cout << "==test==" << endl;
    t.buildHeight();
    t.print();
    return 0;
}