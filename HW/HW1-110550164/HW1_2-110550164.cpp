#include <iostream>
#include <vector>
#include <map>
#include <deque>

using namespace std;

int main(){

    std :: ios :: sync_with_stdio ( false );
    std :: cin . tie ( 0 );

    int n, m, k, t;
    cin >> n >> m >> k >> t;
    vector<int> bf;
    vector<vector<int>> relation(n, bf);
    deque<int> infected;
    //vector<vector<bool>> device_mat(n, vector<bool>(n, 0));
    vector<bool> check_infected(n, false);

    for(int i = 0 ; i < m ; i++){ // setup the relationship
        int a, b;
        cin >> a >> b;
        relation[a - 1].push_back(b - 1);
        //device_mat[a - 1][b - 1] = true; 
    }

    //debug
    /*for(int i = 0 ; i < relation.size() ; i++){
        for(int j = 0 ; j < relation[i].size() ; j++){
            cout << "relation[" << i << "][" << j << "]: " << relation[i][j] << " ";
        }
        cout << endl;
    }*/
    

    for(int i = 0 ; i < k ; i++){ // setup the initial infect status
        int tmp; cin >> tmp;
        check_infected[tmp - 1] = true;
        infected.push_back(tmp - 1);
    }

    for(int i = 0 ; i < t - 1 ; i++){
        int cur_infected = infected.size();
        if(cur_infected == 0 ) break;
        for(int j = 0 ; j < cur_infected ; j++){ //bfs method
            for(int k = 0 ; k < relation[infected[0]].size() ; k++){

                if(check_infected[relation[infected[0]][k]] == false){
                    //cout << "infect " << relation[infected[0]][k] << endl;
                    check_infected[relation[infected[0]][k]] = true;
                    infected.push_back(relation[infected[0]][k]);
                }  
            }
            infected.pop_front();
        }
    }

    int count = 0;
    for(int i = 0 ; i < n ; i++){
        if(check_infected[i] == true) {
            //cout << i + 1 << " is infected." << endl;
            count++;
        }

    }
    cout << count;
    return 0;
}
