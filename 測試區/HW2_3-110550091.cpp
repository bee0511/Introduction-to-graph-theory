#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;

pair<int, int> leaf_length(int cur, vector<int> deg, int length){
    int pre = -1;
    while(deg[cur] != 3){
        int next;
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

int main(){
    int n;
    cin >> n;
    adj.resize(n);
    vector<int> joint;
    vector<int> deg(n, 0);
    
    for(int i=0; i<n-1; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        deg[a]++;
        if(adj[a].size() == 3) joint.push_back(a);
        adj[b].push_back(a);
        deg[b]++;
        if(adj[b].size() == 3) joint.push_back(b);
    }
    
    int m;
    cin >> m;
    vector<int> key;
    for(int i=0; i<m; i++){
        int x;
        cin >> x;
        key.push_back(x);
    }
    
    // first = length
    // second = the join that the leaf is attached to
    vector<pair<int, int>> leaf;
    for(int i=0; i<deg.size() ; i++)
        if(deg[i] == 1) leaf.push_back(leaf_length(i, deg, 0));

    int start = -1, end = -1;
    vector<int> start_length;
    vector<int> end_length;

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
    
    deque<int> bone;
    int cur = start;
    int pre = -1;
    
    while(cur != end){
        int next;
        for(int i = 0 ; i < adj[cur].size() ; i++){
            if(adj[cur][i] == pre) continue;
            next = adj[cur][i];
        }
        for(int i = 0 ; i < leaf.size() ; i++){
            if(leaf[i].second == cur && cur != start)
                bone.push_back(leaf[i].first);
        }
        pre = cur;
        cur = next;
    }
    
    // 8 keys
    bool flag = false;
    vector<deque<int>> keychain(4, bone);
    keychain[0].push_front(start_length[0]);
    keychain[0].push_back(end_length[0]);
    keychain[1].push_front(start_length[0]);
    keychain[1].push_back(end_length[1]);
    keychain[2].push_front(start_length[1]);
    keychain[2].push_back(end_length[0]);
    keychain[3].push_front(start_length[1]);
    keychain[3].push_back(end_length[1]);
    
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

    return 0;
}
