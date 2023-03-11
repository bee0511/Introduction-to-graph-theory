#include <iostream>
#include <vector>

using namespace std;
int main(){
    int n; cin >> n;
    long long player[n] = {0};
    int win; cin >> win;
    int lose; cin >> lose;
    int tie; cin >> tie;
    int tmp;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            cin >> tmp;
            if(i != j){
                switch (tmp)
                {
                case 0:
                player[i] += lose;
                    break;
                case 1:
                player[i] += win;
                    break;
                case 2:
                player[i] += tie;
                    break;
                }
            }
        }
    }
    for(int i = 0 ; i < n ; i ++){
        cout << player[i] << " ";
    }
    return 0;
}