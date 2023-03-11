#include <iostream>

using namespace std;

int arr[100005] = {0};
int main(){
    int n; cin >> n;
    int largest = 0, target = 0;
    for(int i = 0 ; i < n ; i++){
        int tmp; cin >> tmp;
        arr[tmp]++;
        if(largest < arr[tmp]){
            largest = arr[tmp];
            target = tmp;
        }
        if((largest == arr[tmp] && target < tmp)){
            target = tmp;
        }
    }
    cout << target << " " << arr[target] << endl;
    return 0;
}