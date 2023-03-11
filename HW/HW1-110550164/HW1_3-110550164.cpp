#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool valid;

void print(const vector<long long> &arr){
    for(auto &it : arr){
        cout << it << " ";
    }
    cout << endl;
}

int binary_search(int L, int R, int key, vector<int> &arr){
    int target = L - 1;
    while (L <= R) {
        int mid = (L + R) / 2;
        if (arr[mid] >= key) {
            target = mid;
            L = mid + 1;
        }
        else R = mid - 1;
    }
    return target;  
}

bool cmp(int a, int b){
    return a > b;
}

bool is_even(vector<int> &arr){
    long long sum = 0;
    for(auto &it : arr){
        sum += it;
        sum %= 2;
    }
    if(sum % 2 == 0) return true;
    else return false;

}

bool graph_constructable(vector<int> &arr, int n){
    if(!valid) return false;
    /*if(!is_even(arr)) {
        //cout << "not even" << endl;
        return false;
    }*/
    vector<long long> right_sum(n + 2, 0);    // Erdős-Gallai theorem
    
    for(int i = 0 ; i < n ; i++){// use dp to get the sigma from i to n of degree i.
        right_sum[n - i] = right_sum[n - i + 1] + arr[n - i];
    }
    //reverse(right_sum.begin(), right_sum.end());
    //cout << "right_sum: ";
    //print(right_sum);
    long long L = 0, R = 0; //L is the sum of degree from 1 to k, R is k * (k - 1) + sigma (from k + 1 to n), min(degree i, k)
    for(int k = 1 ; k <= n ; k++){ //
        L += arr[k]; // L is the sum of degree from 1 to k
        long long border = binary_search(k + 1, n, k, arr);// border is rightmost value that makes min(degree i, k) = k.
        //cout << "p: " << p << endl;
        R = k * (border - 1); // k * (k - 1) + sigma of min(degree i , k) = k, which the amount is (border - k). k * (k - 1) + k * (border - k) = k * (border - 1).
        //cout << "R: " << R << endl;
        R += right_sum[border + 1];// sum sigma of min(degree i , k) = degree i.
        //cout << "L: " << L << " R: " << R << endl;
        if(L > R) return false;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int Q, n, m;
    cin >> Q;
    while(Q--){
        valid = true;
        cin >> n >> m;
        vector<int> arr;
        arr.push_back(0);
        for(int i = 1 ; i <= n ; i++){
            int tmp; cin >> tmp;
            arr.push_back(tmp);
            if(arr[i] >= n || arr[i] < 0) valid = false;//
        }
        int u, v;
        while(m--){
            cin >> u >> v;
            arr[u]--;
            arr[v]--;
            
            if(arr[u] < 0 || arr[v] < 0) valid = false;
        
        }
        std::sort(arr.begin() + 1, arr.end(), cmp);
        //cout << "arr: ";
        //print(arr);
        if(!is_even(arr)) valid = false;
        if(graph_constructable(arr, n)){
            cout << "Yes" << endl;
        }
        else cout << "No" << endl;
    }
    return 0;
}