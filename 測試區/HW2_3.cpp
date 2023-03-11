#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

void solve() {
    int n, m;
    cin >> n; 
    vector<vector<int>> G(n);
    vector<int> deg(n), vis(n), cnt(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
        deg[v]++; deg[u]++;
    }
    queue<int> que;
    for(int i = 0; i < n; i++) {
        if(deg[i] == 1) {
            que.push(i); cnt[i] = 1; vis[i] = 1;
        }
        if(deg[i] == 3) vis[i] = 2;
    }
    while(que.size()) {
        int x = que.front();
        que.pop();
        for(int y : G[x]) {
            if(vis[y] != 1) {
                deg[y]--; deg[x]--;
                if(vis[y] == 0 && deg[y] == 1) {
                    vis[y] = 1; cnt[y] = cnt[x] + 1; que.push(y);
                }
            }
        }
    }
    vector<int> pos;
    for(int i = 0; i < n; i++) {
        if(deg[i] <= 1 && vis[i] == 2) {
            pos.push_back(i);
        }
    }
    cin >> m;
    vector<int> key(m);
    for(int i = 0; i < m; i++) cin >> key[i];
    if((int)pos.size() == 1) {
        if(m != 1) {
            cout << "NO\n"; return;
        }
        // cout << "cool\n";
        set<int> st;
        for(int y : G[pos[0]]) {
            if(vis[y] == 1) {
                st.insert(cnt[y]);
            }
        }
        if(st.count(key[0])) {
            cout << "YES\n";
            return;
        }
    }
    else {
        for(int i = 0; i < 2; i++) {
            int pre = -1;
            vector<int> tmp;
            que.push(pos[i]);
            while(que.size()) {
                int x = que.front(); 
                // cout << x << '\n';
                que.pop();
                for(int y : G[x]) {
                    if(vis[y] == 1) {
                        tmp.push_back(cnt[y]);
                    }
                    if(y == pre || vis[y] == 1) continue;
                    que.push(y); 
                }
                pre = x;
            }
            // for(int y : tmp) cout << y << ' '; cout << '\n';
            bool flag = false;
            if((int)tmp.size() == m + 2) {
                if(tmp[0] == key[0] || tmp[1] == key[0]) {
                    if(tmp[m + 1] == key[m - 1] || tmp[m] == key[m - 1]) {
                        flag = true;
                        for(int i = 1; i < m - 1; i++) {
                            if(key[i] != tmp[i + 1]) {
                                flag = false; break;
                            }
                        }
                    }
                } 
            }
            if(flag) {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
}


signed main() {
    solve();
    return 0;
}