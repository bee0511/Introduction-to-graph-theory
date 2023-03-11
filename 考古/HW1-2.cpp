#include <bits/stdc++.h>

using namespace std;

vector<int> adj_list[200001];
int color[200001]={0};  
int ans[3] = {0};
int n, m, a, b;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }
    
    queue<int> q;
    //bfs started with node 1
    q.push(1);
    color[1] = 1;
    ans[2]++;
    while (!q.empty())
    {
        int now_node = q.front(), next_color = -color[now_node];
        for (int i = 0; i < adj_list[now_node].size(); i++) //?????��??
        {
            int next_node = adj_list[now_node][i];
            if(color[next_node] && color[next_node] != next_color){//??��??
                cout << "-1\n";
                return 0;
            }
            if(!color[next_node]){
                color[next_node] = next_color;
                ans[next_color + 1]++;// -1, 1 -> 0, 2
                q.push(next_node);
            }
        }
        q.pop();
    }
    cout << ans[2] << " " << ans[0] << "\n";

    return 0;   
}
