#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> weight_matrix(n, vector<int>(n,0));
    vector<int> indegree(n, 0), outdegree(n ,0);

    for(int i = 0 ; i < m ; i++){
        int u, v, w;
        cin >> u >> v >> w;
        weight_matrix[u - 1][v - 1] += w;
        indegree[u - 1] += 1;
        outdegree[v - 1] += 1;
    }

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            cout << weight_matrix[i][j] << " ";
        }
        cout << endl;
    }
    for(int i = 0 ; i < n ; i++){
        cout << outdegree[i] << " " << indegree[i] << endl;
    }

    return 0;
}